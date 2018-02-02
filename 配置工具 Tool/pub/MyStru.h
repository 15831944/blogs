typedef struct mysize_
{
	long cx;
	long cy;
}MySize;

/***********定义系统消息************************/
const UINT SHOW_TEXT_AT_TOOLBAR = WM_USER + 1; //根据分割窗口调节
										//工具栏分割线位置
const UINT FILE_COPY_PROGRESS   = WM_USER + 2; //文件拷贝过程
										//动态改变状态栏上进度条进度
const UINT ON_MYFOLDER_COMBO    = WM_USER + 3; //根据工具栏上地址
										//栏里的路径改变当前目录
/************************************************/

/************ list项类型 ************************/
const int ROOT_ITEM1   = 0;  //根目录，我的电脑
const int DRIVE_ITEM1  = 1;  //分区目录，
const int FOLDER_ITEM1 = 2;  //文件夹
const int FILE_ITEM1   = 3;  //文件
/***************************************************/

/***************** 文件操作类型 *********************/
const int DEL_FILE		= 0;  //删除文件或目录
const int NEW_FOLDER	= 1;  //新建文件或目录
const int CUT_FILE		= 2;  //剪切文件或目录
const int COPY_FILE		= 3;  //拷贝文件或目录
const int PASTE_FILE	= 4;  //粘贴文件或目录
const int RENAME_FILE	= 5;  //重命名文件或目录
/**************************************************/

/*********** 前进结构 *****************************/
typedef struct ForwardStru_
{
	CString PathArr[16];
	int ptr;
	int size;
	int max;
}ForwardStru;

/*********** 后退结构 *******************************/
typedef struct BackwardStru_
{
	CString PathArr[16];
	int ptr;
	int size;
	int max;
}BackwardStru;

const UINT BitMask[] = {
	0x0001, 0x0002, 0x0004, 0x0008,
	0x0010, 0x0020, 0x0040, 0x0080,
	0x0100, 0x0200, 0x0400, 0x0800,
	0x1000, 0x2000, 0x4000, 0x8000
};
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


typedef struct
{
	CStringArray filename;
	CString srcpath;
	CStringArray srctype;
	int where_is_src;
}PasteBoardStru;

#define NONE_PANE	0
#define LEFT_PANE	1
#define RIGHT_PANE	2

//定义键值
#define VK_ALT 18
#define VK_ENTER 13
