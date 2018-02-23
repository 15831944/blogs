
//#define NULL 0

#define UWORD unsigned short
#define UBYTE unsigned char
#define UDWORD unsigned int
//定义xml各部分最大长度
#define SIGN_LEN 32
#define ELEMENT_MAXLEN 1024
#define XMLNAME_LEN 8

//node or element
#define TYPE_NODE	1
#define TYPE_ELEM	2

//sign or element
#define CPY_SIGN	1
#define CPY_ELEM	2

//主招，被召类型标志
#define TYPE_REQ	1
#define TYPE_ACK	2

//定义特殊字符数量
#define SPECIAL_NUM 5

extern char *SpecialWord[];
extern char SpecialChar[];
extern char REQ[];
extern char ACK[];

//定义标记结构体如下：
struct signStru
{
	char sign[SIGN_LEN];	//标记，32bytes最大长度
	char len;				//标记长度
};

//定义元素结构体如下：
struct elementStru
{
	char *element;			//元素，不定长，暂时取最大长度为1024bytes
	int len;				//元素长度
};

//定义元素或节点结构如下：
struct nodeStru
{
	struct signStru sign;		//标记
	struct elementStru element;	//元素
	char type;					//类型，1-节点；2-元素；.....
	struct nodeStru *brother;				//同级节点
	struct nodeStru *child;				//下级节点
};

//定义整个xml数据包解析结构如下：
struct xmlpgeStru
{
	char name[XMLNAME_LEN+1];		//xml数据包名称，8bytes最大长度，以后可根据需要扩长
	struct nodeStru *node;		//节点
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
