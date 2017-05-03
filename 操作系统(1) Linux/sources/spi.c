/******************************
spi的读写请求通过：spi_transfer->spi_message->spi_bitbang添加都bitbang->queue中，被bitbang->work反方向提取出来执行。
通过queue_work(bitbang->workqueue, &bitbang->work)把bitbang-work加入bitbang->workqueue后，在某个合适的时间，bitbang->work将被调度运行，bitbang_work函数将被调用：
***************************/

// spi_write_then_read
static int s3c24xx_spi_setupxfer(struct spi_device *spi, struct spi_transfer *t)
{

    /*设置了每字长的位数，发送速度*/
    bpw = t ? t->bits_per_word : spi->bits_per_word;
    hz  = t ? t->speed_hz : spi->max_speed_hz;
    /*分频值*/
    div = clk_get_rate(hw->clk) / hz;

}

int spi_write_then_read(struct spi_device *spi, const u8 *txbuf, unsigned n_tx, u8 *rxbuf, unsigned n_rx)
{
    static DECLARE_MUTEX(lock);
    int                     status;
    struct spi_message      message;
    struct spi_transfer     x[2];
    u8                      *local_buf;

	/* 这里初始化message结构里面用于存放struct spi_transfer指针的链表头 */
    spi_message_init(&message);		//INIT_LIST_HEAD(&message->transfers);
    memset(x, 0, sizeof x);

	/* 留意到没有：tx和rx个占一个工作添加到message的struct spi_transfer链表里，稍后被bitbang_work从链表里提出来处理*/
    if (n_tx)
	{
		x[0].len = n_tx;
		spi_message_add_tail(&x[0], &message);//list_add_tail(&t->transfer_list, &m->transfers);
    }

    if (n_rx)
	{
        x[1].len = n_rx;
        spi_message_add_tail(&x[1], &message);
    }

    /* ... unless someone else is using the pre-allocated buffer */
    local_buf = buf;	//采用预分配的缓存吧

    /* local_buf的前部分用来存放要发送的数据，后部分用来存放接收到的数据 */
    memcpy(local_buf, txbuf, n_tx);
    x[0].tx_buf = local_buf;
    x[1].rx_buf = local_buf + n_tx;

    /* do the i/o */
    status = spi_sync(spi, &message);//同步io，等待spi传输完成，然后返回用户所接收的数据和状态
}

int spi_sync(struct spi_device *spi, struct spi_message *message)
{

        DECLARE_COMPLETION_ONSTACK(done);//声明一个完成变量
        int status;

        message->complete = spi_complete;//spi传输完成后的回调函数
        message->context = &done;
        status = spi_async(spi, message);
        if (status == 0)
        	wait_for_completion(&done);//等待spi传输，调用spi_complete后返回
}

static inline int spi_async(struct spi_device *spi, struct spi_message *message)
{
        message->spi = spi;
        return spi->master->transfer(spi, message);//调用spi_bitbang_transfer传输数据
}

int spi_bitbang_transfer(struct spi_device *spi, struct spi_message *m)
{

        struct spi_bitbang      *bitbang;
        unsigned long           flags;
        int                     status = 0;

        m->actual_length = 0;
        m->status = -EINPROGRESS;
        bitbang = spi_master_get_devdata(spi->master);

     /* 还记得spi_alloc_master函数中调用spi_master_set_devdata把struct s3c24xx_spi结构存放起来吧?
      * 而struct spi_bitbang结构正是struct s3c24xx_spi结构所包含的第一个结构  */
        list_add_tail(&m->queue, &bitbang->queue);//把message加入到bitang的等待队列中
        queue_work(bitbang->workqueue, &bitbang->work);//把bitbang-work加入bitbang->workqueue中，调度运行
}

static void bitbang_work(void *_bitbang)
{
        struct spi_bitbang      *bitbang = _bitbang;
        unsigned long           flags;

		spin_lock_irqsave(&bitbang->lock, flags);

        bitbang->busy = 1;//置忙标志
        while (!list_empty(&bitbang->queue)) {    //遍历bitbang->queue链表

                m = container_of(bitbang->queue.next, struct spi_message, queue);//获取spi_message结构

                list_del_init(&m->queue);//把spi_messae从queue里删除

                nsecs = 100;

                spi = m->spi;

                tmp = 0;

                cs_change = 1;

                status = 0;

                list_for_each_entry (t, &m->transfers, transfer_list) {//从spi_message结构的transfers链表中获取spi_transfer结构

                /* 本messae传输中，需要重设条件，调用setup_transfer函数 */

                    status = setup_transfer(spi, t);

                      if (cs_change) {    //片选激活spi

                                bitbang->chipselect(spi, BITBANG_CS_ACTIVE);

                                ndelay(nsecs);

                         }

                      cs_change = t->cs_change;

                        if (t->len) {

                                if (!m->is_dma_mapped)

                                        t->rx_dma = t->tx_dma = 0;

                                status = bitbang->txrx_bufs(spi, t);//调用s3c24xx_spi_txrx开始传输数据

                           }

                        m->actual_length += status;

                        status = 0;

                        /* protocol tweaks before next transfer */

                        if (t->delay_usecs)

                                udelay(t->delay_usecs);

                        if (!cs_change)

                                continue;//不用重新片选，继续下一个message的传输

                        if (t->transfer_list.next == &m->transfers)//链表遍历完毕，退出循环

                                break;

                        bitbang->chipselect(spi, BITBANG_CS_INACTIVE);//需要重新片选的话...

                }

                m->status = status;//所用spi_message传输完毕

                m->complete(m->context);//应答返回变量，通知等待spi传输完毕的进程(具体来说就是spi_sync函数了)

          /* 前面重设过条件的，在这恢复之 */

                if (setup_transfer)

                        setup_transfer(spi, NULL);

        }

        bitbang->busy = 0;//处理完毕，清除忙标志

}

static int s3c24xx_spi_txrx(struct spi_device *spi, struct spi_transfer *t)

{

        struct s3c24xx_spi *hw = to_hw(spi);

        dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n",

                t->tx_buf, t->rx_buf, t->len);

        hw->tx = t->tx_buf;//发送指针

        hw->rx = t->rx_buf;//接收指针

        hw->len = t->len;//需要发送/接收的数据数目

        hw->count = 0;//存放实际spi传输的数据数目

        /* send the first byte */

        writeb(hw_txbyte(hw, 0), hw->regs + S3C2410_SPTDAT);

        wait_for_completion(&hw->done);

        /* 非常有意思，这里虽然只发送第一字节，可是中断里会帮你发送完其它的字节(并接收数据)，

         * 直到所有的数据发送完毕且所要接收的数据接收完毕(首要)才返回*/

        return hw->count;

}

static irqreturn_t s3c24xx_spi_irq(int irq, void *dev, struct pt_regs *regs)

{

        struct s3c24xx_spi *hw = dev;

        unsigned int spsta = readb(hw->regs + S3C2410_SPSTA);

        unsigned int count = hw->count;

        if (hw->len){

                hw->count++;

                if (hw->rx)

                        hw->rx[count] = readb(hw->regs + S3C2410_SPRDAT);//接收数据

                count++;

                if (count < hw->len)

                        writeb(hw_txbyte(hw, count), hw->regs + S3C2410_SPTDAT);//发送其它数据(或空数据0xFF)

                else

                        complete(&hw->done);//发送接收完毕，通知s3c24xx_spi_txrx函数

        }

}

static inline unsigned int hw_txbyte(struct s3c24xx_spi *hw, int count)

{

        return hw->tx ? hw->tx[count] : 0xff;

        //如果还有数据没接收完且要发送的数据经已发送完毕，发送空数据0xFF

}


2.spidev写分析

spidev的写write函数直接调用spidev_sync_write。

static inline ssize_t  spidev_sync_write(struct spidev_data *spidev, size_t len)

{

    struct spi_transfer t = {

            .tx_buf     = spidev->buffer,

            .len        = len,

        };

    struct spi_message  m;



    spi_message_init(&m);

    spi_message_add_tail(&t, &m);

    return spidev_sync(spidev, &m);

}



static inline void spi_message_init(struct spi_message *m)

{

    memset(m, 0, sizeof *m);

    INIT_LIST_HEAD(&m->transfers);    /*初始化链表头*/

}



spi_message_add_tail(struct spi_transfer *t, struct spi_message *m)

{

    list_add_tail(&t->transfer_list, &m->transfers);/*添加transfer_list*/

}

在这里，创建了transfer和message。spi_transfer包含了要发送数据的信息。然后初始化了message中的transfer链表头，并将spi_transfer添加到了transfer链表中。

最后，调用了spidev_sync，并将创建的spi_message作为参数传入。


在s3c24xx_spi_txrx函数中，首先发送了待发送数据中的第一个字节，随后就调用wait_for_completion来等待剩余的数据发送完成。

NOTE：这里的completion是master驱动层的，spi设备驱动也有一个completion，用于IO同步，不要混淆。

当第一个数据发送完成以后，SPI中断产生，开始执行中断服务程序。在中断服务程序中，将判断是否需要读取数据，如果是则从寄存器中读取数据。

NOTE：如果是使用read系统调用，那么在此发送的数据将是0。

随后发送下一个数据，直到数据发送完成。发送完成后调用complete，使在s3c24xx_spi_txrx的wait_for_completion得以返回。接着，s3c24xx_spi_txrx就将返回已发送的字节数。

NOTE：其实该中断服务子程序实现了全双工数据的传输，只不过特定于具体的系统调用，从而分为了半双工读和写。

static int spidev_message(struct spidev_data *spidev,

        struct spi_ioc_transfer *u_xfers, unsigned n_xfers)

{

    struct spi_message  msg;

    struct spi_transfer *k_xfers;

    struct spi_transfer *k_tmp;

    struct spi_ioc_transfer *u_tmp;

    unsigned        n, total;

    u8          *buf;

    int         status = -EFAULT;



    spi_message_init(&msg);     /*初始化message*/

    k_xfers = kcalloc(n_xfers, sizeof(*k_tmp), GFP_KERNEL); /*分配内存，并清0*/

    if (k_xfers == NULL)

        return -ENOMEM;

    buf = spidev->buffer;    /*所有的spi_transfer共享该buffer*/

    total = 0;

    /*遍历spi_ioc_transfer数组，拷贝相应的参数至spi_transfer数组*/

    for (n = n_xfers, k_tmp = k_xfers, u_tmp = u_xfers;

            n;

            n--, k_tmp++, u_tmp++) {

        k_tmp->len = u_tmp->len;



        total += k_tmp->len;

        if (total > bufsiz) {  /*缓冲区长度为4096字节*/

            status = -EMSGSIZE;

            goto done;

        }



        if (u_tmp->rx_buf) { /*需要接受收据*/

            k_tmp->rx_buf = buf;

            if (!access_ok(VERIFY_WRITE, (u8 __user *)  /*检查指针*/

                        (uintptr_t) u_tmp->rx_buf,

                        u_tmp->len))

                goto done;

        }

        if (u_tmp->tx_buf) { /*需要发送数据*/

            k_tmp->tx_buf = buf;

            if (copy_from_user(buf, (const u8 __user *) /*将用户空间待发送的数据拷贝至buf中*/

                        (uintptr_t) u_tmp->tx_buf,

                    u_tmp->len))

                goto done;

        }

        buf += k_tmp->len;       /*修改buf指针，指向下一个transfer的缓冲区首地址*/

        /*复制四个参数*/

        k_tmp->cs_change = !!u_tmp->cs_change;

        k_tmp->bits_per_word = u_tmp->bits_per_word;

        k_tmp->delay_usecs = u_tmp->delay_usecs;

        k_tmp->speed_hz = u_tmp->speed_hz;

#ifdef VERBOSE

        dev_dbg(&spi->dev,

            "  xfer len %zd %s%s%s%dbits %u usec %uHz\n",

            u_tmp->len,

            u_tmp->rx_buf ? "rx " : "",

            u_tmp->tx_buf ? "tx " : "",

            u_tmp->cs_change ? "cs " : "",

            u_tmp->bits_per_word ? : spi->bits_per_word,

            u_tmp->delay_usecs,

            u_tmp->speed_hz ? : spi->max_speed_hz);

#endif

        spi_message_add_tail(k_tmp, &msg); /*添加spi_transfer到message的链表中*/

    }



    /*spidev_sync->spi_async->spi_bitbang_transfer->bitbang_work->s3c24xx_spi_txrx*/

    status = spidev_sync(spidev, &msg);

    if (status < 0)

        goto done;



    /* copy any rx data out of bounce buffer */

    buf = spidev->buffer;

    for (n = n_xfers, u_tmp = u_xfers; n; n--, u_tmp++) {

        if (u_tmp->rx_buf) {

            if (__copy_to_user((u8 __user *)

                    (uintptr_t) u_tmp->rx_buf, buf,  /*从buf缓冲区复制数据到用户空间*/

                    u_tmp->len)) {

                status = -EFAULT;

                goto done;

            }

        }

        buf += u_tmp->len;

    }

    status = total;



done:

    kfree(k_xfers);

    return status;

}

 首先，根据spi_ioc_transfer的个数，分配了同样个数的spi_transfer，把spi_ioc_transfer中的信息复制给spi_transfer，然后将spi_transfer添加到spi_message的链

 表中。接着。执行了spidev_sync，这个东西似乎似曾相识，这个函数就是 8.3  小结的函数。之后的过程就和前面的write、read一样了。

 其实，这个函数的作用就是把所需要完成的数据传输任务转换成spi_transfer，然后添加到message的连表中。
