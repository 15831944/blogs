//定义命令类型常量
//extern REQ[];
//extern ACK[];

//定义遥控常量

//操作类型
#define OPERATE_INVALID		-1

//SBO操作类型
#define OPERATE_SELECT		1
//#define OPERATE_TRIP		2
//#define OPERATE_CLOSE		3
#define OPERATE_CANCEL		4

//DO操作类型
#define DO_TRIP				0
#define DO_CLOSE			1			


//脉冲宽度，长/短/持续
#define LONG_PULSE		0
#define SHORT_PULSE		1
#define CUSTOM_PULSE	2
#define INVAILD_PULSE	-1

//文件类型
#define FILE_NOFILE -1
#define FILE_FLT 0
#define FILE_PRO 1

struct scadaStru
{
	int aibuf[1024];
	int ainum;

	char dibuf[1024];
	int dinum;

	int cibuf[1024];
	int cinum;

	char dobuf[32];
	int	donum;
};

struct xmtfileStru
{
	bool xmtfile;

//文件属性
	int filetype;
	int totalblock;
	int size;

//发送时的当前状态
	int filename;
	int block;

	char *pfile;
	int	 offset;
};

//文件传输的常量
#define MAX_FILE_NUM 256
#define MAX_FILE_LEN 0x20000
#define FILE_BUF_LEN 0xA0000
#define MAX_FILE_TYPE 16
#define MAX_FILE_NAME_LEN 32
#define MAX_BLOCK_LEN 1024//4096//256//1024

struct fileStru
{
	int filehead;
	char filetype;
	int filelen;
};

struct filesStru
{
	char *filebuf;//[FILE_BUF_LEN];
	struct fileStru file[MAX_FILE_NUM];
	int get;
	int put;
	bool bfull;
};

struct rcvfileStru
{
	char *filebuf;
	int tail;
	int filelen;
	int filetype;
	int filename;
	char name[MAX_FILE_NAME_LEN];
	int blocknum;
	int curblock;
};

//高端文件传输时，一包数据的最大字节数
#define MAX_SRAMFILE_LEN 1024

struct sramfileStru
{
	int index;
	int blocknum;
	int curblock;
	char filebuf[MAX_SRAMFILE_LEN];
	int tail;
};
