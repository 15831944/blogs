//�����������ͳ���
//extern REQ[];
//extern ACK[];

//����ң�س���

//��������
#define OPERATE_INVALID		-1

//SBO��������
#define OPERATE_SELECT		1
//#define OPERATE_TRIP		2
//#define OPERATE_CLOSE		3
#define OPERATE_CANCEL		4

//DO��������
#define DO_TRIP				0
#define DO_CLOSE			1			


//�����ȣ���/��/����
#define LONG_PULSE		0
#define SHORT_PULSE		1
#define CUSTOM_PULSE	2
#define INVAILD_PULSE	-1

//�ļ�����
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

//�ļ�����
	int filetype;
	int totalblock;
	int size;

//����ʱ�ĵ�ǰ״̬
	int filename;
	int block;

	char *pfile;
	int	 offset;
};

//�ļ�����ĳ���
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

//�߶��ļ�����ʱ��һ�����ݵ�����ֽ���
#define MAX_SRAMFILE_LEN 1024

struct sramfileStru
{
	int index;
	int blocknum;
	int curblock;
	char filebuf[MAX_SRAMFILE_LEN];
	int tail;
};
