typedef struct mysize_
{
	long cx;
	long cy;
}MySize;

/***********����ϵͳ��Ϣ************************/
const UINT SHOW_TEXT_AT_TOOLBAR = WM_USER + 1; //���ݷָ�ڵ���
										//�������ָ���λ��
const UINT FILE_COPY_PROGRESS   = WM_USER + 2; //�ļ���������
										//��̬�ı�״̬���Ͻ���������
const UINT ON_MYFOLDER_COMBO    = WM_USER + 3; //���ݹ������ϵ�ַ
										//�����·���ı䵱ǰĿ¼
/************************************************/

/************ list������ ************************/
const int ROOT_ITEM1   = 0;  //��Ŀ¼���ҵĵ���
const int DRIVE_ITEM1  = 1;  //����Ŀ¼��
const int FOLDER_ITEM1 = 2;  //�ļ���
const int FILE_ITEM1   = 3;  //�ļ�
/***************************************************/

/***************** �ļ��������� *********************/
const int DEL_FILE		= 0;  //ɾ���ļ���Ŀ¼
const int NEW_FOLDER	= 1;  //�½��ļ���Ŀ¼
const int CUT_FILE		= 2;  //�����ļ���Ŀ¼
const int COPY_FILE		= 3;  //�����ļ���Ŀ¼
const int PASTE_FILE	= 4;  //ճ���ļ���Ŀ¼
const int RENAME_FILE	= 5;  //�������ļ���Ŀ¼
/**************************************************/

/*********** ǰ���ṹ *****************************/
typedef struct ForwardStru_
{
	CString PathArr[16];
	int ptr;
	int size;
	int max;
}ForwardStru;

/*********** ���˽ṹ *******************************/
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

//�����ֵ
#define VK_ALT 18
#define VK_ENTER 13
