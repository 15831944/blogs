
//#define NULL 0

#define UWORD unsigned short
#define UBYTE unsigned char
#define UDWORD unsigned int
//����xml��������󳤶�
#define SIGN_LEN 32
#define ELEMENT_MAXLEN 1024
#define XMLNAME_LEN 8

//node or element
#define TYPE_NODE	1
#define TYPE_ELEM	2

//sign or element
#define CPY_SIGN	1
#define CPY_ELEM	2

//���У��������ͱ�־
#define TYPE_REQ	1
#define TYPE_ACK	2

//���������ַ�����
#define SPECIAL_NUM 5

extern char *SpecialWord[];
extern char SpecialChar[];
extern char REQ[];
extern char ACK[];

//�����ǽṹ�����£�
struct signStru
{
	char sign[SIGN_LEN];	//��ǣ�32bytes��󳤶�
	char len;				//��ǳ���
};

//����Ԫ�ؽṹ�����£�
struct elementStru
{
	char *element;			//Ԫ�أ�����������ʱȡ��󳤶�Ϊ1024bytes
	int len;				//Ԫ�س���
};

//����Ԫ�ػ�ڵ�ṹ���£�
struct nodeStru
{
	struct signStru sign;		//���
	struct elementStru element;	//Ԫ��
	char type;					//���ͣ�1-�ڵ㣻2-Ԫ�أ�.....
	struct nodeStru *brother;				//ͬ���ڵ�
	struct nodeStru *child;				//�¼��ڵ�
};

//��������xml���ݰ������ṹ���£�
struct xmlpgeStru
{
	char name[XMLNAME_LEN+1];		//xml���ݰ����ƣ�8bytes��󳤶ȣ��Ժ�ɸ�����Ҫ����
	struct nodeStru *node;		//�ڵ�
};

void IntXmlpge(struct xmlpgeStru *pxml);
void IntNode(struct nodeStru *pnode);
void NewIntNode(struct nodeStru **pnode);
void SignElemCpy(struct nodeStru *pnode,char *sign,char *elem);
void AddANode(struct nodeStru **, int, char*, char*);
void AddANode1(struct nodeStru **, int, char*, int, char*, int);
bool XmlpgeToStrAndSend(struct xmlpgeStru *pxmlpge);
struct xmlpgeStru* FormatXmlpge(struct nodeStru *pnode,int type);

bool GetAXmlStr(char *srcbuf,int *srcget,int *srcput, char **objbuf,int *objlen);
bool ParseXmlStr(char *XmlStr,int  len,struct xmlpgeStru *pxml);
