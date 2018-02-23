//����usb����Ҫ������

/****************** һ���������linux���� ******************/

/***** 3.1.	Ŀ¼��Ϣ��ȡ��ls��***************************
	���������ڻ�ȡ�豸�˵�Ŀ¼��Ϣ��
	��������:
	$ls\n                  #��ȡ��ǰĿ¼�µ�Ŀ¼���ļ���Ϣ
	$ls directory\n        #��ȡĿ¼directory�µ�Ŀ¼���ļ���Ϣ��
	�������
	$rsp [path]<path> [dir]<dir1,time> <dir2,time> <dir3,time> [file] <file1,time,size> <file2,time,size >\n
********************************************************/
const CString CLS = "ls";

/****** 3.2.	�ļ����ƣ�cp��***************************
	�����������ն������ļ��ĸ��Ʋ�����
	�������
	$cp source target\n         #���ļ�source ����Ϊ target
	$cp -av soure_dir target_dir\n #������Ŀ¼���ƣ���Ŀ¼��ȫһ��
	�������
	$rsp [ok] \n       #���Ƴɹ�
	$rsp [err] \n       #����ʧ��
*********************************************************/
const CString CCP = "cp";

/******* 3.3.	�ļ�ɾ����rm��****************************
	�������
	$rm file\n          #ɾ��ĳһ���ļ�
	$rm -r directory\n   #ɾ��Ŀ¼
	�������
	$rsp [ok] \n       #�ɹ�
	$rsp [err] \n       #ʧ��
**********************************************************/
const CString CRM = "RM";

/***************** 3.4.	�½�Ŀ¼��mkdir��*****************
	�������
	$mkdir directory\n   #�½�Ŀ¼
	�������
	$rsp [ok] \n       #�ɹ�
	$rsp [err] \n       #ʧ��
**********************************************************/
const CString CMKDIR = "mkdir";

/***************** 3.5.	ʱ�ӿ��ƣ�date��*******************
	�������
	$date\n              #��ʾ��ǰ����ʱ��
	$date -s 20:30:30\n    #����ϵͳʱ��Ϊ20:30:30
	$date -s 2002-3-5\n    #����ϵͳ����Ϊ2003-3-5
	�������
	$rsp [date] <yyyy-mm-dd hh:mm:ss>\n      #��Ӧʱ��
	$rsp [ok] \n        #�ɹ�
	$rsp [err] \n        #ʧ��
***********************************************************/
const CString CDATE = "date";

/***************** 3.6.	����ϵͳ��reboot��******************
	�������
	$reboot\n              #��ʾ��ǰ����ʱ��
	�������
	$rsp [ok] \n        #�ɹ�
	$rsp [err] \n        #ʧ��
************************************************************/
const CString CREBOOT = "reboot";

/************** 3.7.	��ʾ���̣�ps�� ********************/
const CString CPS = "ps";

/************** 3.8.	ɱ�����̣�kill��*******************/
const CString CKILL = "kill";

/************** 3.9.	�������磨ifconfig��****************
	�������
	$ifconfig\n                                #��ȡ��������
	$ifconfig [ip] <*.*.*.*> [netmask]<*.*.*.*>\n    #��������
	�������
	$rsp [ip]<*.*.*.*> [netmask]<*.*.*.*>\n         #��Ӧ��������
	$rsp [err] \n        #ʧ��
	$rsp [ok] \n        #�ɹ�
***********************************************************/
const CString CIFCONFIG = "ifconfig";
/*************** 3.10.	��ȡ���read��********************
	�������
	$read -a\n            #��ȡģ����
	$read -d\n           #��ȡң����
	$read -c\n           #��ȡ�ۼ���
	�������
	$rsp [ai]<name0,data0><name1,data1>......\n       #��Ӧģ����
	$rsp [di]<name0,data0><name1,data1>......\n       #��Ӧң����
	$rsp [ci]<name0,data0><name1,data1>......\n       #��Ӧ�ۼ���
************************************************************/
const CString CREAD = "read";

/**************** 3.11.	�����ļ���put��**********************
	�������
	$put [path]<***>[file]<***>[blocklen]<***>[timeout]<***>\n
	$put [dir]<***>[num]<***>[size]<***> [data]\n

	�������
	$rsp [ip]<*.*.*.*> [netmask]<*.*.*.*>\n         #��Ӧ��������
	$rsp [err] \n       #ʧ��
	$rsp [ok] \n        #�ɹ�
	$rsp [acknum]<***> \n        #ȷ������
************************************************************/
const CString CPUT = "put";
const CString CPUT_FILE = "putfile";

/***************** 3.12.	�����ļ���get��*****************/
const CString CGET = "get";
const CString CGET_FILE = "getfile";

/***************** 4.1. ȷ������ ***************************/
const CString CRSP = "rsp";

/***************** 4.2. ��������� **************************
	0	$	��������"$"��ͷ
	1	�ո�	��������ָ��
	2	-	��������ָ��
	3	\n	���������
	4	/	·������"/"�����зָ�
	5	[	���������ʿ�ʼ��
	6	]	���������ʽ�����
	7	<	ʵ�忪ʼ��
	8	>	ʵ�������
************************************************************/
const CString CHEAD      = "$";
const CString CSPACE     = " ";
const CString CSPLIT     = "-";
const CString CEND       = "\n";
const CString CPATHSPLIT = "/";
const CString CATTBEGIN  = "[";
const CString CATTEND    = "]";
const CString CENTBEGIN  = "<";
const CString CENTEND    = ">";

/**************** 4.3 ���������� **************************/
const CString DCPT_PATH		= "path";		//�ļ�����·��	<path>
const CString DCPT_PATHEXIST = "pathexist";	//ls��Ŀ¼���ڲ�����
const CString DCPT_DIR		= "dir";		//Ŀ¼��Ϣ	<dir1,time>
const CString DCPT_FILE		= "file";		//�ļ���Ϣ	<file1,time,size>
const CString DCPT_OK		= "ok"; 		//�ɹ�ȷ��	
const CString DCPT_ERR		= "err";		//ʧ��ȷ��	
const CString DCPT_DATE		= "date";		//����ʱ��	<yyyy-mm-dd-hh-mm-ss>
const CString DCPT_IP		= "ip";			//����IP��ַ	<*.*.*.*>
const CString DCPT_NETMASK  = "netmask";	//��������	<*.*.*.*>
const CString DCPT_AI		= "ai"; 		//ģ������	<name,data>
const CString DCPT_DI		= "di"; 		//��������	<name,data>
const CString DCPT_CI		= "ci";			//�ۼ�����	<name,data>
const CString DCPT_BLOCKLEN = "blocklen";	//�ļ�����鳤��	<len>
const CString DCPT_TIMEOUT  = "timeout";	//��ȷ��ʱ	<msnum>
const CString DCPT_ACKNUM	= "acknum";		//ȷ�Ͽ��	<num>
const CString DCPT_FILEEXIST = "fileexist"; //���ص��ļ��Ƿ����
const CString DCPT_SIZE		= "size";		//�ļ���С
const CString DCPT_BLOCKNUM = "blocknum";	//�ļ��ֵĿ���
const CString DCPT_BLOCKNO	= "blockno";	//�ļ��ֵĿ���
const CString DCPT_BLOCKSIZE = "blocksize";	//�ļ���Ĵ�С
const CString DCPT_SRAMLIST	= "sramlist";	//�߶������ļ����
const CString DCPT_INDEX	= "index";		//�߶�����������
/**************** ��������usb�ڲ��� ***********************/
const int WAIT_CMD  = 0;  //��ͨ����
const int WAIT_FILE = 1;  //�ļ�������

const int RSP_NONE =			0;
const int RSP_LS =				1;
const int RSP_CP =				2;
const int RSP_RM =				3;
const int RSP_MKDIR =			4;
const int RSP_DATE =			5;
const int RSP_REBOOT =			6;
const int RSP_PS =				7;
const int RSP_KILL =			8;
const int RSP_IFCONFIG =		9;
const int RSP_READ =			10;
const int RSP_PUT =				11;
const int RSP_PUT_FILE	=		12;
const int RSP_GET =				13;
const int RSP_GET_FILE =		14;
const int RSP_FILE_DATA =		15;
const int RSP_WAIT_FILE_DATA =	16;
const int RSP_MV =				17;
const int RSP_HELO =			18;
//����Ϊ�ٻ��߶��ڴ�ʹ��
const int RSP_SRAM_LIST =		19;
const int RSP_SRAM_FILE =		20;
const int RSP_SRAM_BLOCK =		21;
const int RSP_SRAM_FILE_DATA =	22;
//��λ�ն�
const int RSP_RESET =			23;

//�����ϱ���������
const int NONE_DATA = 0;
const int AI_DATA	= 1;
const int DI_DATA	= 2;
const int CI_DATA	= 3;

/*********** �����ƻ��ǿ���� ************************/
#define STREAMCTRL 1
#define BLOCKCTRL  2

/*********** ��ȷȷ�ϻ��Ǵ���ȷ�� *******************/
#define RSP_OK	0
#define RSP_ERR 1

/**************** ��������Linux����ṹ�� *****************/
//
//usb��ͨѶЭ��ṹ��1���ڽ�������ʱ����һ��
//
//������һ��<... , ... , ...>���������
typedef struct EntityObjStructure
{
	CStringArray EntityObj;   //��ǰ<...>���������
	int EntityObjNum;          //ʵ�������
	EntityObjStructure *next; //��һ��<...>���������
}EntityObjStru;

//��������һ��[...]<... , ...><... , ...>...
typedef struct EntityStructure
{
	CString character;         //���������ʣ�[...]���������
	EntityObjStru *EntityObj;  //ʵ�����<...><...>...
	int EntityNum;             //ʵ����
	EntityStructure *next;     //��һ��[...]<...><...>...
}EntityStru;

typedef struct LinuxCommandStructure
{
	CString CmdName;		//Linux������
	CString CmdPara;		//�������
	EntityStru* Entity;		//ʵ��
	int EntityNum;			//ʵ����
	CStringArray ConPara;   //��ͨ����
}LinuxCmdStru;	//��CString����ʾ�Ľṹ

//
//usb��ͨѶЭ��ṹ��2���ڷ�������ʱ����һ��
//
#define NAME_LEN 33         //���һ������'\n'
#define CMD_PARA_LEN 17
#define CON_PARA_LEN 33
#define CHAR_LEN 17          //character����󳤶ȣ�Ҳ����[]������ַ�����󳤶�
#define OBJ_LEN 256         //���ﲻ�÷�'\n',����Ķ��ã���Ϊ������
							//������ʱ���ݣ���Ҫ��һ���ӹ�
#define CON_PRRA_MAX 2
//������һ��<... , ... , ...>���������
typedef struct EntityObjStructure1
{
	char EntityObj[OBJ_LEN];  //һ��<>��������е�����
	int EntityObjNum;     //�м���<>		
	struct EntityObjStructure1 *next; //��һ��<>���������
}EntityObjStru1;

//��������һ��[...]<... , ...><... , ...>...
typedef struct EntityStructure1
{
	char character[CHAR_LEN];          //���������ʣ�[...]���������
	EntityObjStru1 *EntityObj;   //ʵ�����<...><...>...
	int EntityNum;					   //ʵ����
	struct EntityStructure1 *next;		   //��һ��[...]<...><...>...
}EntityStru1;

//��������һ��������liunx����
typedef struct
{
	char CmdName[NAME_LEN];			//Linux������
	char CmdPara[CMD_PARA_LEN];		//������� -����Ĳ���
	EntityStru1* Entity;		//ʵ��
	int EntityNum;					//ʵ����
	char ConPara[CON_PRRA_MAX][CON_PARA_LEN];	//��ͨ����
	int ConParaNum;
}LinuxCmdStru1;	//�ö�������������ʾ�Ľṹ


//
//���������ļ�ʱ�Ŀ��ƽṹ��
//
typedef struct
{
	CString PCPath;
	CString FileName;

	long FileSize;
	int BlockNum;

	int CurBlock;
	int BlockSize;

	int TimeOut;
	CFile hfile;
} UpFileStru;

//
//�������ظ߶��ļ��Ľṹ
//
typedef struct
{
	int Index;
	int BlockNum;
	int CurBlock;
	char *FileBuf;
	int size;
	int tail;		//�ļ����浽ʲô�ط���
} UpSRAMStru;

#define MAX_SRAM_FILENUM 32
//
//���ڱ��浱ǰ�Ĵ洢�ڼ�����ϵĸ߶�����
//
typedef struct
{
	bool bValid;
	bool bSavedData;
	int type;
	CString sFileName;
	CString sSavedFilename;
} SavedSRAMStru;


/*****************************************************
*
*	�������ݷ������ȼ�
*
*****************************************************/
const int PRIORITY_MIN			= 0;
const int PRIORITY_PART_CMD		= PRIORITY_MIN + 1;	//���ڱ�ʾһ��û��������ݰ��ĺ�������
const int PRIORITY_FILE_DATA	= PRIORITY_MIN + 2;	//�����ʾ�ļ������ݲ���
const int PRIORITY_FILE			= PRIORITY_MIN + 3;	//�����ļ�����Ŀ��Ʋ���
const int PRIORITY_CMD			= PRIORITY_MIN + 4;	//������ͨ����

/*********** usb�ڷ�����Ϣ�ṹ��(����) ***************/
typedef struct UsbXmtStructure
{
	char *msg;
	int msglen;
	int priority;
	struct UsbXmtStructure *next;

	int wait_flag;
	int timeout;
}UsbXmtStru;

typedef struct
{
	int wait_flag;
	int timeout;
}TimeOutStru;

const int XMT_FILE = 1;
const int XMT_DATA = 2;

//��������:
//extern UsbXmtStru* XmtFileMsg;  //�ļ�ͨѶ����
extern UsbXmtStru* XmtDataMsg;  //���е�����ķ��ʹ���������

extern bool bSystemIsRuning;   //ϵͳ����״̬
extern int DataCtrlType;  //���ݿ��Ʒ�ʽ�������������Ʒ�ʽ
extern int WaitConfirmType;        //��־�ȴ�ȷ�ϵ�����

extern int WaitCmdType;     //�ȴ����������ͣ��Ǳ�׼������ļ�������
extern int WaitFileLen;                //ϣ���յ����ļ��Ŀ�ĳ���

extern unsigned char RcvBuf[];     //��ʱ����4096���Ժ����ʵ�ʴ�����С���޸�
extern int RcvGet,RcvPut;        //�ջ������շ�ָ��
extern unsigned char* RcvPtr;

//��������
int GetNumFromUsb();
int ReadFromUsb(unsigned char *RcvMsg,int Len);
int ReadFromUsb(unsigned char *RcvMsg);
int WriteToUsb(unsigned char *msg,int len);
int WriteToUsb(CString str);
UINT MainThread(LPVOID para);
UINT SendDataToUsb(LPVOID para);
BOOL Dispose(unsigned char *msg,int len);
bool WaitConfirm(LinuxCmdStru *LinuxCmd);
//BOOL TransToLinuxCmd(CString str,
//					 LinuxCmdStru *LinuxCmd);
BOOL TransToLinuxCmd(unsigned char *msg,
					 int len,
					 LinuxCmdStru *LinuxCmd);
void AddDataToXmtList(char *msg,int len,int type,int PRIORITY_CMD, int wait_flag, int timeout);
