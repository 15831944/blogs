/* SPI 数据结构 */

#define		SPI_CPHA		0x01				/* 时钟相位 */
#define		SPI_CPOL		0x02				/* 时钟信号起始相位：高或者是低电平*/
#define		SPI_CS_HIGH		0x04				/* 为1时片选的有效信号是高电平*/
#define		SPI_LSB_FIRST	0x08				/* 发送时低比特在前  */
#define		SPI_3WIRE		0x10				/* 输入输出信号使用同一根信号线 */
#define		SPI_LOOP		0x20				/* 回环模式 */

#define		SPI_MODE_0		(0 | 0)
#define		SPI_MODE_1		(0 | SPI_CPHA)
#define		SPI_MODE_2		(SPI_CPOL | 0)
#define		SPI_MODE_3		(SPI_CPOL | SPI_CPHA)


struct spi_device {
	structdevice		dev;
	structspi_master	*master;
	u32					max_speed_hz;		/* 通信时钟最大频率 */
	u8					chip_select;		/* 片选号 */
	u8					mode;				/*SPI设备的模式，下面的宏是它各bit的含义  */
	u8					bits_per_word;		/* 每个通信字的字长（比特数）每次读写的数据长度 */
	int					irq;				/*使用到的中断 */
	void				*controller_state;
	void				*controller_data;
	char				modalias[32];		/* 绑定的设备驱动的名字*/
};

struct spi_ioc_transfer {
	__u64		tx_buf;		/* 写数据缓冲 */
	__u64		rx_buf;		/* 读数据缓冲 */

	__u32		len;		/* 缓冲的长度 */
	__u32		speed_hz;	/* 通信的时钟频率 */

	__u16		delay_usecs;		/* 两个 spi_ioc_transfer 之间的延时(us) */
	__u8		bits_per_word;		/* 字长（比特数）  */
	__u8		cs_change;			/* 是否改变片选 */
	__u32		pad;
};

struct spi_board_info {
	char		modalias[32];		/* 要绑定的驱动的名字 */
	constvoid	*platform_data;
	void		*controller_data;
	int			irq;
	u32			max_speed_hz;		/* 通信时钟最大速率 */
	u16			bus_num;			/* 总线编号  */
	u16			chip_select;		/* 片选号 */
	u8			mode;				/* 和spi_device中的mode成员类似   */
};
