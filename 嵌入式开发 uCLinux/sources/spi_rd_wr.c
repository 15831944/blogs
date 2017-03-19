1. 读写操作实际上完成的都是数据的交换, 即主机传送1个字节给从机(写), 从机同时传送1个字节给主机(读)
2. 读操作看起来像是写数据, 但实际上, 写入完成后, 就可以从 SPI0DAT 中获得从机的应答数据了

为什么 spi 的读函数要写 Dummy 字节呢?

SPI是一个环形总线结构，在sck的控制下，两个双向移位寄存器进行数据交换，
所以它是一边发送一边接收，你想接收一个自己数据，就要先发送一个字节数据。
因为这样才产生时钟信号，数据才从从机发送出来；
也因此，写入时交换来的数据是无效的，读取时写入的数据是无效的。

spi的读和写的区别是因为这个么：
SPI0DAT = (reg | 0x80); （写）SPI0DAT = reg;(读）。
是因为寄存器地址是7位，二进制形式下最高位是0，
SPI0DAT = (reg | 0x80); 把最高位强制置1，
SPI0DAT = reg; 最高位0，执行读操作。是这样么？还有您懂不懂crc检测？

读写的具体区别，要看你单片机的芯片手册了，一般是没有区别的，读写甚至可以写成一个函数。。。

/* 主机: c8051f330 单片机; 从机 si4432 */

void SpiWriteRegister(uchar reg, uchar value)
{
	RF_NSEL = 0;			//Select the radio by pulling the nSEL pin to low
	SPI0DAT = (reg | 0x80);	//write the address of the register into the SPI buffer of the MCU
	while( SPIF == 0);		//wait until the MCU finishes sending the byte
	SPIF = 0;

	SPI0DAT = value;		//write the new value of the radio register into the SPI buffer of the MCU.
	while( SPIF == 0);		//wait until the MCU finishes sending the byte.
	SPIF = 0;

	RF_NSEL = 1;			//Deselect the radio by pulling high the nSEL pin.
}

void SpiWriteRegister(uchar reg, uchar value)
{
   	RF_NSEL = 0;				// 片选拉低启动SPI通讯

	SPI0DAT = (reg | 0x80);		// 写入1个字节的寄存器地址
	while(SPIF == 0);		    // 等待SPI传输完成
	SPIF = 0;

	SPI0DAT = value;			// 继续写入第二个字节(寄存器值)
	while(SPIF == 0);			// 等待SPI传输完成
	SPIF = 0;

	RF_NSEL = 1;				// 片选拉高结束SPI通讯
}

/*****************
	SPI读取函数
*****************/
uchar SpiReadRegister(uchar reg)
{
	RF_NSEL = 0;				// 片选拉低, 启动SPI通讯

   	SPI0DAT = reg;				// 写入1个字节的寄存器地址
	while(SPIF == 0);			// 等待SPI传输完成
	SPIF = 0;

	SPI0DAT = 0xFF;				// 写一个 Dummy 字节(因为要读取的话必须用写入来启动一个交换数据的传输), 当写入完成后从机的数据也完成了读入
	while(SPIF == 0);			// 等待SPI传输完成
	SPIF = 0;

	RF_NSEL = 1;				// 片选拉高, 结束SPI通讯
   	return SPI0DAT;				// 返回读取的值(在 SPI0DAT = 0xFF 中完成读取)
}

uchar SpiReadRegister(uchar reg)
{
	RF_NSEL = 0;				//Select the radio by pulling the nSEL pin to low

	SPI0DAT = reg;				//Write the address of the register into the SPI buffer of the MCU, write data into the SPI register
	while(SPIF == 0);			//Wait untill the MCU finishes sending the byte
	SPIF = 0;

	SPI0DAT = 0xFF;				//write dummy data into the SPI register. During sending this byte the MCU will read the value of the radio register and save it in its SPI buffer.
	while( SPIF == 0);			//Wait untill the MCU finishes sending the byte.
	SPIF = 0;

	RF_NSEL = 1;				//Deselect the radio by pulling high the nSEL pin
	return SPI0DAT;				//Read the received radio register value and return with it
}
