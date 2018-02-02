//定义usb口需要的命令

/****************** 一、定义基本linux命令 ******************/

/***** 3.1.	目录信息读取（ls）***************************
	本命令用于获取设备端的目录信息。
	下行命令:
	$ls\n                  #读取当前目录下的目录及文件信息
	$ls directory\n        #读取目录directory下的目录及文件信息。
	上行命令：
	$rsp [path]<path> [dir]<dir1,time> <dir2,time> <dir3,time> [file] <file1,time,size> <file2,time,size >\n
********************************************************/
const CString CLS = "ls";

/****** 3.2.	文件复制（cp）***************************
	本命令用于终端自身文件的复制操作。
	下行命令：
	$cp source target\n         #将文件source 复制为 target
	$cp -av soure_dir target_dir\n #将整个目录复制，两目录完全一样
	上行命令：
	$rsp [ok] \n       #复制成功
	$rsp [err] \n       #复制失败
*********************************************************/
const CString CCP = "cp";

/******* 3.3.	文件删除（rm）****************************
	下行命令：
	$rm file\n          #删除某一个文件
	$rm -r directory\n   #删除目录
	上行命令：
	$rsp [ok] \n       #成功
	$rsp [err] \n       #失败
**********************************************************/
const CString CRM = "RM";

/***************** 3.4.	新建目录（mkdir）*****************
	下行命令：
	$mkdir directory\n   #新建目录
	上行命令：
	$rsp [ok] \n       #成功
	$rsp [err] \n       #失败
**********************************************************/
const CString CMKDIR = "mkdir";

/***************** 3.5.	时钟控制（date）*******************
	下行命令：
	$date\n              #显示当前日期时间
	$date -s 20:30:30\n    #设置系统时间为20:30:30
	$date -s 2002-3-5\n    #设置系统日期为2003-3-5
	上行命令：
	$rsp [date] <yyyy-mm-dd hh:mm:ss>\n      #响应时间
	$rsp [ok] \n        #成功
	$rsp [err] \n        #失败
***********************************************************/
const CString CDATE = "date";

/***************** 3.6.	复归系统（reboot）******************
	下行命令：
	$reboot\n              #显示当前日期时间
	上行命令：
	$rsp [ok] \n        #成功
	$rsp [err] \n        #失败
************************************************************/
const CString CREBOOT = "reboot";

/************** 3.7.	显示进程（ps） ********************/
const CString CPS = "ps";

/************** 3.8.	杀死进程（kill）*******************/
const CString CKILL = "kill";

/************** 3.9.	设置网络（ifconfig）****************
	下行命令：
	$ifconfig\n                                #读取网络配置
	$ifconfig [ip] <*.*.*.*> [netmask]<*.*.*.*>\n    #设置网络
	上行命令：
	$rsp [ip]<*.*.*.*> [netmask]<*.*.*.*>\n         #响应网络配置
	$rsp [err] \n        #失败
	$rsp [ok] \n        #成功
***********************************************************/
const CString CIFCONFIG = "ifconfig";
/*************** 3.10.	读取命令（read）********************
	下行命令：
	$read -a\n            #读取模拟量
	$read -d\n           #读取遥信量
	$read -c\n           #读取累加量
	上行命令：
	$rsp [ai]<name0,data0><name1,data1>......\n       #响应模拟量
	$rsp [di]<name0,data0><name1,data1>......\n       #响应遥信量
	$rsp [ci]<name0,data0><name1,data1>......\n       #响应累加量
************************************************************/
const CString CREAD = "read";

/**************** 3.11.	下载文件（put）**********************
	下行命令：
	$put [path]<***>[file]<***>[blocklen]<***>[timeout]<***>\n
	$put [dir]<***>[num]<***>[size]<***> [data]\n

	上行命令：
	$rsp [ip]<*.*.*.*> [netmask]<*.*.*.*>\n         #响应网络配置
	$rsp [err] \n       #失败
	$rsp [ok] \n        #成功
	$rsp [acknum]<***> \n        #确认命令
************************************************************/
const CString CPUT = "put";
const CString CPUT_FILE = "putfile";

/***************** 3.12.	上载文件（get）*****************/
const CString CGET = "get";
const CString CGET_FILE = "getfile";

/***************** 4.1. 确认命令 ***************************/
const CString CRSP = "rsp";

/***************** 4.2. 命令结束符 **************************
	0	$	命令行以"$"开头
	1	空格	命令输入分割符
	2	-	命令参数分割符
	3	\n	命令结束符
	4	/	路径采用"/"符进行分割
	5	[	属性描述词开始符
	6	]	属性描述词结束符
	7	<	实体开始符
	8	>	实体结束符
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

/**************** 4.3 定义描述词 **************************/
const CString DCPT_PATH		= "path";		//文件操作路径	<path>
const CString DCPT_PATHEXIST = "pathexist";	//ls的目录存在不存在
const CString DCPT_DIR		= "dir";		//目录信息	<dir1,time>
const CString DCPT_FILE		= "file";		//文件信息	<file1,time,size>
const CString DCPT_OK		= "ok"; 		//成功确认	
const CString DCPT_ERR		= "err";		//失败确认	
const CString DCPT_DATE		= "date";		//日期时间	<yyyy-mm-dd-hh-mm-ss>
const CString DCPT_IP		= "ip";			//网络IP地址	<*.*.*.*>
const CString DCPT_NETMASK  = "netmask";	//子网掩码	<*.*.*.*>
const CString DCPT_AI		= "ai"; 		//模拟数据	<name,data>
const CString DCPT_DI		= "di"; 		//数字数据	<name,data>
const CString DCPT_CI		= "ci";			//累加数据	<name,data>
const CString DCPT_BLOCKLEN = "blocklen";	//文件传输块长度	<len>
const CString DCPT_TIMEOUT  = "timeout";	//超确认时	<msnum>
const CString DCPT_ACKNUM	= "acknum";		//确认块号	<num>
const CString DCPT_FILEEXIST = "fileexist"; //上载的文件是否存在
const CString DCPT_SIZE		= "size";		//文件大小
const CString DCPT_BLOCKNUM = "blocknum";	//文件分的块数
const CString DCPT_BLOCKNO	= "blockno";	//文件分的块数
const CString DCPT_BLOCKSIZE = "blocksize";	//文件块的大小
const CString DCPT_SRAMLIST	= "sramlist";	//高端数据文件类别
const CString DCPT_INDEX	= "index";		//高端数据索引号
/**************** 二、定义usb口参数 ***********************/
const int WAIT_CMD  = 0;  //普通命令
const int WAIT_FILE = 1;  //文件块数据

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
//下面为召唤高端内存使用
const int RSP_SRAM_LIST =		19;
const int RSP_SRAM_FILE =		20;
const int RSP_SRAM_BLOCK =		21;
const int RSP_SRAM_FILE_DATA =	22;
//复位终端
const int RSP_RESET =			23;

//定义上报数据类型
const int NONE_DATA = 0;
const int AI_DATA	= 1;
const int DI_DATA	= 2;
const int CI_DATA	= 3;

/*********** 流控制还是块控制 ************************/
#define STREAMCTRL 1
#define BLOCKCTRL  2

/*********** 正确确认还是错误确认 *******************/
#define RSP_OK	0
#define RSP_ERR 1

/**************** 三、定义Linux命令结构体 *****************/
//
//usb口通讯协议结构体1，在接收命令时用这一个
//
//描述了一个<... , ... , ...>里面的数据
typedef struct EntityObjStructure
{
	CStringArray EntityObj;   //当前<...>里面的数据
	int EntityObjNum;          //实体对象数
	EntityObjStructure *next; //下一个<...>里面的数据
}EntityObjStru;

//用来描述一个[...]<... , ...><... , ...>...
typedef struct EntityStructure
{
	CString character;         //属性描述词，[...]里面的数据
	EntityObjStru *EntityObj;  //实体对象，<...><...>...
	int EntityNum;             //实体数
	EntityStructure *next;     //下一个[...]<...><...>...
}EntityStru;

typedef struct LinuxCommandStructure
{
	CString CmdName;		//Linux命令名
	CString CmdPara;		//命令参数
	EntityStru* Entity;		//实体
	int EntityNum;			//实体数
	CStringArray ConPara;   //普通参数
}LinuxCmdStru;	//用CString来表示的结构

//
//usb口通讯协议结构体2，在发送命令时用这一个
//
#define NAME_LEN 33         //多出一个来放'\n'
#define CMD_PARA_LEN 17
#define CON_PARA_LEN 33
#define CHAR_LEN 17          //character的最大长度，也就是[]里面的字符的最大长度
#define OBJ_LEN 256         //这里不用放'\n',上面的都用，因为这里存的
							//还是临时数据，还要进一步加工
#define CON_PRRA_MAX 2
//描述了一个<... , ... , ...>里面的数据
typedef struct EntityObjStructure1
{
	char EntityObj[OBJ_LEN];  //一个<>里面的所有的数据
	int EntityObjNum;     //有几个<>		
	struct EntityObjStructure1 *next; //下一个<>里面的数据
}EntityObjStru1;

//用来描述一个[...]<... , ...><... , ...>...
typedef struct EntityStructure1
{
	char character[CHAR_LEN];          //属性描述词，[...]里面的数据
	EntityObjStru1 *EntityObj;   //实体对象，<...><...>...
	int EntityNum;					   //实体数
	struct EntityStructure1 *next;		   //下一个[...]<...><...>...
}EntityStru1;

//用来描述一个完整的liunx命令
typedef struct
{
	char CmdName[NAME_LEN];			//Linux命令名
	char CmdPara[CMD_PARA_LEN];		//命令参数 -后面的参数
	EntityStru1* Entity;		//实体
	int EntityNum;					//实体数
	char ConPara[CON_PRRA_MAX][CON_PARA_LEN];	//普通参数
	int ConParaNum;
}LinuxCmdStru1;	//用二进制数组来表示的结构


//
//用于上载文件时的控制结构体
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
//用于上载高端文件的结构
//
typedef struct
{
	int Index;
	int BlockNum;
	int CurBlock;
	char *FileBuf;
	int size;
	int tail;		//文件保存到什么地方了
} UpSRAMStru;

#define MAX_SRAM_FILENUM 32
//
//用于保存当前的存储在计算机上的高端数据
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
*	定义数据发送优先级
*
*****************************************************/
const int PRIORITY_MIN			= 0;
const int PRIORITY_PART_CMD		= PRIORITY_MIN + 1;	//用于表示一包没发完的数据包的后续部分
const int PRIORITY_FILE_DATA	= PRIORITY_MIN + 2;	//用语表示文件的数据部分
const int PRIORITY_FILE			= PRIORITY_MIN + 3;	//用语文件传输的控制部分
const int PRIORITY_CMD			= PRIORITY_MIN + 4;	//用语普通命令

/*********** usb口发送消息结构体(链表) ***************/
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

//变量声明:
//extern UsbXmtStru* XmtFileMsg;  //文件通讯缓冲
extern UsbXmtStru* XmtDataMsg;  //所有的命令的发送待法缓冲区

extern bool bSystemIsRuning;   //系统运行状态
extern int DataCtrlType;  //数据控制方式，现在用流控制方式
extern int WaitConfirmType;        //标志等待确认的命令

extern int WaitCmdType;     //等待的命令类型，是标准命令还是文件块数据
extern int WaitFileLen;                //希望收到的文件的块的长度

extern unsigned char RcvBuf[];     //暂时先用4096，以后根据实际传输块大小再修改
extern int RcvGet,RcvPut;        //收缓冲区收发指针
extern unsigned char* RcvPtr;

//函数声明
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
