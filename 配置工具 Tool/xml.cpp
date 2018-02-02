#include "stdafx.h"
#include "../demo.h"
#include "xml.h"
#include "myfun.h"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "MainFrm.h"
#include "xmldata.h"
#include "../NetPort.h"

const UINT BitMask[] = {
	0x0001, 0x0002, 0x0004, 0x0008,
	0x0010, 0x0020, 0x0040, 0x0080,
	0x0100, 0x0200, 0x0400, 0x0800,
	0x1000, 0x2000, 0x4000, 0x8000
};

#define STATE0  0		//普通状态
#define STATE1  1		//文件名称,即xml文件的总<name>
#define STATE2  2		//节点名称,即xml节点的总<name>
#define STATE3  3		//保留
#define STATE4  4		//保留

//解析xml通讯协议用到的常量
#define FIND_NORMAL		0
#define FIND_LEFT		1
#define FIND_RIGHT		2
#define FIND_REQ		3
#define FIND_ACK		4
#define FIND_END		5

#define SPECIALW_NORMAL 100		//普通字符
#define SPECIALW_BEGIN  10		//'&'
#define SPECIALW_NEXT	0		//'&'后面的

#define MATCH_NONE	0			//没有任何匹配的特殊字符
//temp const
#define NET_MAX_DATALEN 1024

#define SOCKET_RCV_BUFLEN 10242

void RelNode(struct nodeStru **pnode);


//these function for debug
void OutXmlnode(struct nodeStru* pnode);

int wait_bytes_len = 0;
bool bwait_bytes = false;
void *memmem(const void *, size_t, const void *, size_t);

int sock_fd;
extern SocketInterfStru SocketInterf;
extern UINT NetRcv1(LPVOID para);

struct sramfileStru sramfile;	//发送高端文件的控制字
extern UpSRAMStru mSRAMFile;

//发送给usb203的接口
BOOL SendToSocket(int *fd, char *msg,int len)
{
	int i = 0;
	if(*fd)
	{
//		SetDebugHistory(msg, len, false);
		int ret=send(*fd, (const char*)msg, len , 0);
		if(ret==SOCKET_ERROR)
		{
			AfxMessageBox("网络通讯错误，请重新连接服务器");
			closesocket( *fd );
			WSACleanup( );
			*fd = 0;
			return FALSE;
		}
//		if(bNeedRequest)
			while(!NetRcv1(NULL) && (i++ < 1500))
				Sleep(20);
			if(i >= 1500)
				return FALSE;
	}
	return TRUE;
}

/*************************************************
	功能：向维护子进程召唤模拟量
	参数：
	返回：
***************************************************
void CallAi()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"Ai",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Index","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Change","y");
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return;
}

*************************************************
	功能：向维护子进程召唤遥信量
	参数：
	返回：
***************************************************
void CallDi()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"Di",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Index","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Change","y");
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return;
}

*************************************************
	功能：向维护子进程召唤双点遥信量
	参数：
	返回：
***************************************************
void CallDDi()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"DDi",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Index","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Change","y");
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return;
}

*************************************************
	功能：向维护子进程召唤累加量
	参数：
	返回：
***************************************************
void CallCi()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"Ci",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Index","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Change","y");
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return;
}

*************************************************
	功能：向维护子进程召唤高端数据列表
	参数：
	返回：
*************************************************
void CallSramList()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"FileList",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
}

*************************************************
	功能：向维护子进程召唤高端文件内容
	参数：
	返回：
*************************************************
bool CallSramData(int index)
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;
	char itoastr[32];

	if((index < 0) || (index >= 32))
		return false;

	AddANode(&pnewnode,TYPE_NODE,"File",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;
	_snprintf(itoastr, sizeof(itoastr),"%d", index);
	AddANode(&pnewnode, TYPE_ELEM, "Index", itoastr);
	pcurnode->brother = pnewnode;
	
	mSRAMFile.Index = index;
	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
	return true;
}

*************************************************
	功能：向维护子进程召唤高端文件块
	参数：
	返回：
*************************************************
bool CallSramBlock(int blockno)
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;
	char itoastr[32];

	AddANode(&pnewnode,TYPE_NODE,"FileBlock",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	_snprintf(itoastr, sizeof(itoastr), "%d", mSRAMFile.Index);
	AddANode(&pnewnode, TYPE_ELEM, "Index", itoastr);
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	_snprintf(itoastr, sizeof(itoastr), "%d", blockno);
	AddANode(&pnewnode, TYPE_ELEM, "BlockNo", itoastr);
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
	return true;
}

*************************************************
	功能：删除指定的高端文件
	参数：
	返回：
*************************************************
bool CallRemoveSram(int index)
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;
	char itoastr[32];

	if((index < 0) || (index >= 32))
		return false;

	AddANode(&pnewnode,TYPE_NODE,"DelFile",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;
	_snprintf(itoastr, sizeof(itoastr),"%d", index);
	AddANode(&pnewnode, TYPE_ELEM, "Index", itoastr);
	pcurnode->brother = pnewnode;
	
	sramfile.index = index;
	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
	return true;
}

*************************************************
	功能：校正
	参数：
	返回：
*************************************************
bool CallAdjust()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"Adjust",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return true;
}
*/
/*************************************************
	功能：复位系统
	参数：
	返回：
*************************************************/
bool CallReset()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"Reset",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return true;
}

/*************************************************
	功能：设定值
	参数：
	返回：
*************************************************/
bool CallSetData(void *para)
{
	struct nodeStru *phnode = (struct nodeStru*)para;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return true;
}

/*************************************************
	功能：设定值
	参数：
	返回：
*************************************************/
bool CallResetData()
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	AddANode(&pnewnode,TYPE_NODE,"ResetData",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return true;
}

//
//功能：特殊字符串替换函数,这里只考虑特殊字符串被单个的特殊字符所代替
//使用范围：仅用在解析xml特殊字符串
//
bool ReplaceXmlWord(char *srcStr,		//源内存
					int  *srclen		//源内存长度
					)
{
	unsigned int i = 0;
	unsigned int j,tempj;
	int count;
	int spc = SPECIALW_NORMAL;
	char *tempbuf;
	int tempi = 0;
	char *src = srcStr;
	unsigned int len = (unsigned int)*srclen;
	unsigned short matchword = MATCH_NONE;

	tempbuf = (char *)malloc(len);
	while(i < len)
	{
		switch(spc)
		{
		case SPECIALW_NORMAL:
			for(count=0 ;count < SPECIAL_NUM; count++)
			{
				if ( *(src+i) == SpecialWord[count][0])
				{
					matchword |= BitMask[count];
				}
			}
			if(!matchword)
			{
				tempbuf[tempi] = *(src+i);
				tempi++;
				i++;
			}
			else
			{
				spc = SPECIALW_BEGIN;
				j = 1;
			}
			break;
		case SPECIALW_BEGIN:		//之所以要它是为本协议所定，因为所有的特殊字符串都以&开头
									//这个起一个过滤作用，可以节省大量处理时间
			for(count=0; count < SPECIAL_NUM; count++)
			{
				if(matchword & BitMask[count])
				{
					if(j >= strlen(SpecialWord[count]))	//找到
					{
						tempbuf[tempi++] = SpecialChar[count];
						i += j;
						j = 0;
						spc = SPECIALW_NORMAL;
						matchword = 0;
						break;
					}
					if(*(src+i+j) != SpecialWord[count][j])
					{
						matchword &= ~BitMask[count];
					}
				}
			}
			if( matchword )
			{
				j++;
				spc = SPECIALW_NEXT;
			}
			else	//这里这样处理仅对这个协议，如果是普通的话，应该用：
					//spc = SPECIALW_NOMAL; i++; 代替下面的
			{
				free(tempbuf);
				return false;
			}
			break;
		case SPECIALW_NEXT:
			for(count = 0; count < SPECIAL_NUM; count++)
			{
				if(!(matchword & BitMask[count]))
					continue;
				tempj = j;
				while((tempj < strlen(SpecialWord[count])) && ((i+tempj) < len))
				{
					if(*(src+i+tempj) == SpecialWord[count][tempj])
						tempj++;
					else
						break;
						//matchword &= ~BitMask[count];
				}
				if(tempj >= strlen(SpecialWord[count]))	//找到匹配字符串(最匹配的那个),
														//然后用特殊字符来替换
				{
					tempbuf[tempi++] = SpecialChar[count];
					i += tempj;
					j = 0;
					spc = SPECIALW_NORMAL;
					matchword = 0;
					break;
				}
			}
			if(count >= SPECIAL_NUM)//普通的话应该用spc = SPECIALW_NARMAL; i++;代替
			{
				free(tempbuf);
				return false;
			}
			break;
		default:
			break;
		}//end switch
	} //end while

	*srclen = tempi;
	memcpy(srcStr,tempbuf,*srclen);
	free(tempbuf);
	return true;
}

//
//功能：把解析好的xml结构体格式化,也即把转义字符转化成原来的字符
//不合法的情况:出现&,<,>,",'等非转义字符,即不是标准的转移字符
//
bool FormatXmlStr(char *XmlStr)
{
	return true;
}

//
//功能:判断文件或节点标记是否合法
//不合法的情况,格式化后的字符串中出现&,<,>,",'等非法字符
//
bool CheckSign(char *name,int len)
{
	int i = 0;
	char spc_chr;
	while(i < SPECIAL_NUM)
	{
		spc_chr = SpecialChar[i++];
		if(memmem(name,len,&spc_chr,1))
			return false;
	}
	return true;
}

//功能：初始化一个xmlpgeStru
void IntXmlpge(struct xmlpgeStru *pxml)
{
	pxml->node = NULL;
}

//
//功能: 初始化一个nodeStru节点
//
void IntNode(struct nodeStru *pnode)
{
	pnode->sign.len = 0;
	pnode->element.len = 0;
	pnode->brother = pnode->child = NULL;
	pnode->type = TYPE_NODE;
}

//
//功能：分配一个nodeStru结构存储区，并对其初始化
//
void NewIntNode(struct nodeStru **pnode)
{
	*pnode = (struct nodeStru*)malloc(sizeof(struct nodeStru));
	IntNode(*pnode);
}

//
//功能：拷贝一个字符串给nodeStru->sign或nodeStru->element
//
void SignElemCpy(struct nodeStru *pnode,
				 char *sign,
				 char *elem)
{
	int cpylen = 0;
	if(sign)
	{
		cpylen = strlen(sign);
		if(cpylen > SIGN_LEN)
			cpylen = SIGN_LEN;
		memcpy(pnode->sign.sign,sign,cpylen);
		pnode->sign.len = strlen(sign);
	}

	if(elem)
	{
		cpylen = strlen(elem);
		if(cpylen <= 0)
			return;
		if(cpylen > ELEMENT_MAXLEN)
			cpylen = ELEMENT_MAXLEN;
		pnode->element.element = (char *)malloc(cpylen);
		memcpy(pnode->element.element,elem,cpylen);
		pnode->element.len = strlen(elem);
	}
}

//
//功能：拷贝一个字符串给nodeStru->sign或nodeStru->element
//
void SignElemCpy1(struct nodeStru *pnode,
				  char *sign,
				  int signlen,
				  char *elem,
				  int elemlen)
{
	int cpylen = 0;

	if(sign)
	{
		cpylen = signlen;
		if(cpylen < 0)
			return;
		if(cpylen > SIGN_LEN)
			cpylen = SIGN_LEN;
		memcpy(pnode->sign.sign,sign,cpylen);
		pnode->sign.len = strlen(sign);
	}

	if(elem)
	{
		cpylen = elemlen;
		if(cpylen <= 0)
			return;
		if(cpylen > ELEMENT_MAXLEN)
			cpylen = ELEMENT_MAXLEN;
		pnode->element.element = (char *)malloc(cpylen);
		memcpy(pnode->element.element,elem,cpylen);
		pnode->element.len = strlen(elem);
	}
}

void AddANode(struct nodeStru **pnode,
			  int type,
			  char *sign,
			  char *elem)
{
	NewIntNode(pnode);
	(*pnode)->type = type;
	SignElemCpy(*pnode,sign,elem);
}

void AddANode1(struct nodeStru **pnode,
			  int type,
			  char *sign,
			  int signlen,
			  char *elem,
			  int elemlen)
{
	NewIntNode(pnode);
	(*pnode)->type = type;
	SignElemCpy1(*pnode,sign,signlen,elem,elemlen);
}

//
//功能:解析一个节点,包括它下面的子节点
//返回:如果错误返回false,在返回false之前释放掉分配的所有内存
//
bool ParseNode(char *nodestr,
			   int len,
			   struct nodeStru **pnode
			   )
{
	char *pheadstr = nodestr;
	int head = 0;
	struct nodeStru *pchildnode;
	struct nodeStru *ptchildnode = *pnode;	//child尾指针,这个指针是针对pnode的child
	struct nodeStru *ptbronode = NULL;				//brother尾指针,这个指针是针对pnode的下一层子节点
//	char chr = '<',chr1 = '>';
	int state = STATE0;
	char *findposi;
	char tempstr[SIGN_LEN];
	int signlen,elemlen;

	if(len == 0)
	{
		RelNode(pnode);
		return true;
	}
	if(!memmem(pheadstr,len,"<",1))
	{
		elemlen = len;
		(*pnode)->element.len = elemlen;
		(*pnode)->element.element = (char *)malloc((*pnode)->element.len+1);

		memcpy((*pnode)->element.element,pheadstr,elemlen);
		ReplaceXmlWord((*pnode)->element.element,&((*pnode)->element.len));
		(*pnode)->element.element[len] = '\0';
		(*pnode)->type = TYPE_ELEM;
		//pnode->brother = NULL;		//这里之所以不要是因为在调用这个函数的时候已经给他初始化过了
		//pnode->child = NULL;
		return true;
	}
	while(head < len)
	{
		switch(state)
		{
		case STATE0:
			if(*(pheadstr+head) == ' ')
			{
				state = STATE0;
				head++;
				break;
			}
			if(*(pheadstr+head) == '<')
			{
				state = STATE2;
				head++;
				break;
			}
			RelNode(pnode);
			return false;
		case STATE2:
			if(!(findposi = (char*)memmem(pheadstr+head,
							len - head,
							">",
							1)))
				return false;		//没有找到'>'
			signlen = (int)(findposi - pheadstr - head);
			if(signlen > SIGN_LEN)
				return false;
			tempstr[0] = '<';
			tempstr[1] = '/';
			memcpy(tempstr+2,pheadstr+head,signlen);
			tempstr[2+signlen] = '>';
			if(!(findposi = (char*)memmem(findposi+1,
									len+pheadstr-findposi-1,
									tempstr,
									signlen+3)))//错误原因:没有</>
			{
				RelNode(pnode);
				return false;
			}
//			head = int(findposi - pheadstr) + 3 + signlen;
			//找到<></>，说明有下一级节点，把<></>里面的内容作为参数递归调用此函数
			pchildnode = (struct nodeStru *)malloc(sizeof(struct nodeStru));
			IntNode(pchildnode);
			memcpy(pchildnode->sign.sign,tempstr+2,signlen);
			if(!ReplaceXmlWord(pchildnode->sign.sign,&signlen))
			{
//				printf("parsenode err!");
				return false;
			}
			if(!CheckSign(pchildnode->sign.sign,signlen))		//错误原因:里面有&,<,>等非法字符
				return false;

			pchildnode->sign.len = signlen;
			pchildnode->sign.sign[signlen] = '\0';
			if(ptchildnode->child == NULL)	//这里只挂接第一个子接点，其他子节点通过第一个字节点的brother挂接
			{
				(*pnode)->child = pchildnode;
				ptbronode = pchildnode;			//第一个子节点
			}
			else
			{
				ptbronode->brother = pchildnode;	//挂接brother
				ptbronode = pchildnode;
			}
			head += signlen + 1;	//定位到<sign>后面的第一个字符

//AfxMessageBox(Str(findposi-pheadstr-head) + (char*)(pheadstr+head));
			if(!ParseNode(pheadstr+head,(int)(findposi-pheadstr)-head,&pchildnode))
			{
				RelNode(pnode);
				return false;
			}
			head = (int)(findposi - pheadstr + 3 + signlen);
			state = STATE0;
		default:
			break;
		}
	}
	return true;
}

//
//功能:解析xmlpge结构下的第一层节点,包括它下面的子节点
//返回:如果错误返回false,在返回false之前释放掉分配的所有内存
//
bool ParseXmlNode(char *nodestr,
			   int len,
			   struct nodeStru **pnode
			   )
{
	char *pheadstr = nodestr;
	int head = 0;
	struct nodeStru *pchildnode;
	struct nodeStru *ptchildnode = *pnode;	//child尾指针,这个指针是针对pnode的child
	struct nodeStru *ptbronode = NULL;				//brother尾指针,这个指针是针对pnode的下一层子节点
//	char chr = '<',chr1 = '>';
	int state = STATE0;
	char *findposi;
	char tempstr[SIGN_LEN];
	int signlen;//,elemlen;

	if(len == 0)
	{
		RelNode(pnode);
		return true;
	}

	if(!memmem(pheadstr,len,"<",1))
	{
		RelNode(pnode);
		return false;
	}

	while(head < len)
	{
		switch(state)
		{
		case STATE0:
			if(*(pheadstr+head) == ' ')
			{
				state = STATE0;
				head++;
				break;
			}
			if(*(pheadstr+head) == '<')
			{
				state = STATE2;
				head++;
				break;
			}
			RelNode(pnode);
			return false;
		case STATE2:
			if(!(findposi = (char*)memmem(pheadstr+head,
							len - head,
							">",
							1)))
				return false;		//没有找到'>'
			signlen = (int)(findposi - pheadstr - head);
			if(signlen > SIGN_LEN)
				return false;
			tempstr[0] = '<';
			tempstr[1] = '/';
			memcpy(tempstr+2,pheadstr+head,signlen);
			tempstr[2+signlen] = '>';

			if(!(findposi = (char*)memmem(findposi+1,
									len+pheadstr-findposi-1,
									tempstr,
									signlen+3)))//错误原因:没有</>
			{
				printf("parsexmlnode err!\n");
				return false;
			}
			head += signlen + 1;	//定位到<sign>后面的第一个字符
			//找到<></>，说明有下一级节点，把<></>里面的内容作为参数递归调用此函数
			pchildnode = (struct nodeStru *)malloc(sizeof(struct nodeStru));
			IntNode(pchildnode);
			memcpy(pchildnode->sign.sign,tempstr+2,signlen);
			if(!ReplaceXmlWord(pchildnode->sign.sign,&signlen))
			{
//				printf("parsexmlnode err!\n");
				return false;
			}
			if(!CheckSign(pchildnode->sign.sign,signlen))		//错误原因:里面有&,<,>等非法字符
				return false;

			pchildnode->sign.len = signlen;
			pchildnode->sign.sign[signlen] = '\0';
			if(ptchildnode == NULL)	//这里只挂接第一个子接点，其他子节点通过第一个字节点的brother挂接
			{
				*pnode = pchildnode;
				ptbronode = pchildnode;			//第一个子节点
			}
			else
			{
				ptbronode->brother = pchildnode;	//挂接brother
				ptbronode = pchildnode;
			}
//AfxMessageBox(Str(findposi-pheadstr-head) + (char*)(pheadstr+head));
			if(!ParseNode(pheadstr+head,(int)(findposi-pheadstr)-head,&pchildnode))
			{
				RelNode(pnode);
				return false;
			}

			head = (int)(findposi - pheadstr + 3 + signlen);
			state = STATE0;
		default:
			break;
		}
	}
	return true;
}

//
//功能：释放掉struct nodeStru
//
void RelNode(struct nodeStru **pnode)
{
	if(*pnode == NULL)
		return;

	if((*pnode)->type == TYPE_ELEM)
		if((*pnode)->element.len > 0)
			free((*pnode)->element.element);

	if((*pnode)->brother)
		RelNode(&(*pnode)->brother);
	else if((*pnode)->child)
		RelNode(&(*pnode)->child);

	free(*pnode);
	(*pnode) = NULL;
	return;
}

//
//功能：释放掉strcut xmlpgeStru
//
void RelXmlPackage(struct xmlpgeStru *pxml)
{
	struct nodeStru *pnode;
	pnode = pxml->node;
	if(!pnode)
		RelNode(&pnode);
	free(pxml);
	return;
}

//
//功能：把未把转义字符转化成原来的字符的字符串解析成xmlstru结构
//
bool ParseXmlStr(char *XmlStr,				//源字符串
				 int  len,					//源字符串长度
				 struct xmlpgeStru *pxml	//存放解析的xml结构体,
											//它的初始化放在调用这个函数的函数里
				 )
{
	int head=0;
	char *posi1,*posi2,*findposi;
	int namelen;//,signlen;
	int state = STATE0;
//	char chr='<';
//	char chr1 = '>';
	char tempstr[SIGN_LEN+1];
	bool bwaithead = true;
//	struct nodeStru *pnode,*plastnode;

	posi1 = posi2 = 0;
	if(len == 0)
		return true;
	while(head < len)
	{
		switch(state)
		{
		case STATE0:			//普通状态,也即这时的状态不在任何标记
								//元素或标记里
			if( *(XmlStr + head) == ' ')
			{
				state = STATE0;
				head++;
			}
			else if( *(XmlStr + head) == '<')
			{
				if(bwaithead)
					state = STATE1;
				else
					state = STATE2;
				head++;
			}
			else
				return false; //如果即不是' '又不是'<',报错
			break;
		case STATE1:				//xml文件名
			posi1 = (char *)memmem(XmlStr,len-head,">",1);
			if(posi1 == 0)
				return false;
			namelen = (int)(posi1 - XmlStr - head);
			if(namelen > XMLNAME_LEN)
				return false;

			tempstr[0]='<';
			tempstr[1]='/';

			memcpy(tempstr+2,XmlStr+head,namelen); //注意，这里copy时没有拷最后那个'/0'
			tempstr[2+namelen] = '>';
			tempstr[3+namelen] = '\0';
			if(!(findposi = (char*)memmem(XmlStr+head,
									len-head,
									tempstr,
									namelen+3)))//错误原因:没有</>
				return false;
			if(findposi-XmlStr+namelen+3 < len)   //+3是因为有</>3个字符,错误原因:</>后还有字符
				return false;
			memcpy(pxml->name, XmlStr+head, namelen);
			pxml->name[namelen] = '\0';
			head += 1+namelen;

			if(!ReplaceXmlWord(pxml->name,&namelen))
			{
//				printf("parsexmlstr err!");
				return false;
			}

			if(!CheckSign(pxml->name,namelen))		//错误原因:里面有&,<,>等非法字符
				return false;

			bwaithead = false;
			pxml->node = NULL;
			if(!ParseXmlNode(XmlStr+head,(int)(findposi-XmlStr-head),&(pxml->node)))
			{
				RelNode(&(pxml->node));
				return false;
			}
			head = len;
			state = STATE0;
			break;
		default:
			return false;
		}
	}//end while

//add for debug
//	OutXmlnode(pxml->node);

	return true;
}

//
//功能：在给定缓冲区里找出一个符合<Req>...</Req>或<Ack>...</Ack>的结构，
//		把它拷贝给一个新缓冲区，同时清除不合规范的多余字符串
//
bool GetAXmlStr(char *srcbuf,int *srcget,int *srcput,
				char **objbuf,int *objlen)
{
	int findingbegin = *srcget,findingend = *srcput;
	int findedbegin = findingbegin, findedend =0;
	int mfind = FIND_NORMAL;
	unsigned int j=0;
	int findAckOrReq = 0;
	bool bfindhead = false;
	bool bfindxmlstr = false;

	while( (findingbegin != findingend) && (!bfindxmlstr) )
	{
		switch(mfind)
		{
		case FIND_NORMAL:
			if(*(srcbuf + findingbegin) == '<')
			{
				if(findAckOrReq != 0)
					mfind = FIND_END;
				else
					mfind = FIND_LEFT;
				j = 0;
			}
			findingbegin++;
			if(findingbegin >= SOCKET_RCV_BUFLEN)
				findingbegin = 0;
			break;
		case FIND_LEFT:
			if(ACK[j] == REQ[j])
			{
				if(!(*(srcbuf+findingbegin) == ACK[j]))
					mfind = FIND_NORMAL;
			}
			else
			{
				if(*(srcbuf+findingbegin) == ACK[j])
					mfind = FIND_ACK;
				else if(*(srcbuf+findingbegin) == REQ[j])
					mfind = FIND_REQ;
				else
					mfind = FIND_NORMAL;
			}
			findingbegin++;
			if(findingbegin >= SOCKET_RCV_BUFLEN)
				findingbegin = 0;
			j++;
			break;
		case FIND_ACK:
			if(*(srcbuf+findingbegin) == ACK[j])
			{
				j++;
				if(j >= strlen(ACK))	//匹配
				{
					findAckOrReq = FIND_ACK;
					mfind = FIND_RIGHT;
				}
			}
			else
			{
				mfind = FIND_NORMAL;
				j = 0;
			}
			findingbegin++;
			if(findingbegin >= SOCKET_RCV_BUFLEN)
				findingbegin = 0;
			break;
		case FIND_REQ:
			if(*(srcbuf+findingbegin) == REQ[j])
			{
				j++;
				if(j >= strlen(ACK))	//匹配
				{
					findAckOrReq = FIND_REQ;
					mfind = FIND_RIGHT;
				}
			}
			else
			{
				mfind = FIND_NORMAL;
				j = 0;
			}
			findingbegin++;
			if(findingbegin >= SOCKET_RCV_BUFLEN)
				findingbegin = 0;
			break;
		case FIND_RIGHT:	//这个没用
			if(!bfindhead)		//现在是处理<...>
			{
				if(*(srcbuf + findingbegin) != '>')
					findAckOrReq = 0;
				else
				{
					findedbegin = findingbegin - j - 1; 
					bfindhead = true;
				}
				mfind = FIND_NORMAL;
			}
			else			//now is </...>
			{
				if(*(srcbuf + findingbegin) != '>')
				{
					mfind = FIND_NORMAL;
					findingbegin++;
				}
				else
				{
					findedend = findingbegin+1;	//why +1?because the get point will 
										//point to the new position after a <...>...</...>
										//and the findedend is the position afger a <...>...</...>
					bfindxmlstr = true;
				}
			}
			break;
		case FIND_END:
			if(*(srcbuf + findingbegin) == '/')
				mfind = findAckOrReq;
			else
				mfind = FIND_NORMAL;
			findingbegin++;
			if(findingbegin >= SOCKET_RCV_BUFLEN)
				findingbegin = 0;
			break;
		default:
			break;
		}
	}

	if(!bfindxmlstr)
	{
		*srcget = findedbegin;
		return false;
	}

	*objlen = findedend - findedbegin;
	if (*objlen < 0)
		*objlen += SOCKET_RCV_BUFLEN;
	*objbuf = (char *)malloc(*objlen+1);	//加1的目的为了在字符串加一个'\0',为了能print出来，不加也没关系
	j = 0;
	while(findedbegin != findedend)
	{
		//*(*objbuf + j++) = *(srcbuf + findedbegin);
		(*objbuf)[j++] = *(srcbuf + findedbegin);
		if(++findedbegin >= SOCKET_RCV_BUFLEN)
			findedbegin = 0;
	}
	//*(*objbuf + j++) = 0;
	(*objbuf)[j++] = 0;
	//strcpy(*objbuf, tempbuf);

//	strcpy(*objbuf, "<Ack><Di><Cmd>ack</Cmd><DiObj><Name>name</Name><State>分</State><Index>0</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>1</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>2</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>3</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>4</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>5</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>6</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>7</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>8</Index></DiObj><DiObj><Name>name</Name><State>分</State><Index>9</Index></DiObj><FirstData>y</FirstData><LastData>n</LastData></Di></Ack>");
//上面为调试代码
	*srcget = findedend;
	return true;
}

/***************************************************************
*
*
*			发送处理函数
*
*
****************************************************************/

//
//功能：拷贝一个字符给目标发送缓冲区，目标发送缓冲区如果满了，那么发送出去
//
void cpyachar(char **buf,
			  char *src,
			  int *remainlen,
			  char *ori_objbuf)
{
	if(*remainlen < 1)
	{
		SendToSocket(&(SocketInterf.Socket[1]),ori_objbuf,NET_MAX_DATALEN - *remainlen);
		*remainlen = NET_MAX_DATALEN;
		*buf = ori_objbuf;
	}

	**buf = *src;
	*remainlen -= 1;

	if(*remainlen > 0)
		(*buf)++;
	else
	{
		SendToSocket(&(SocketInterf.Socket[1]),ori_objbuf,NET_MAX_DATALEN - *remainlen);
		*remainlen = NET_MAX_DATALEN;
		*buf = ori_objbuf;
	}
}

//
//功能：把一个缓存区拷给目标发送缓冲区，在拷贝的同时用特殊字符串替换特殊字符
//		目标发送缓冲区如果满了，那么发送出去，清空后继续往里copy
//
void formatcpybuf(char **buf,
					char *src,
					int srclen,
					int *remainlen,
					char *ori_objbuf)
{
	char *srcbuf = src;
	int i = 0,j;
	while(i < srclen)
	{
		for(j=0;j<SPECIAL_NUM;j++)
		{
			if(srcbuf[i] == SpecialChar[j])
			{
				if(*remainlen <= (int)strlen(SpecialWord[j]))
				{
					SendToSocket(&(SocketInterf.Socket[1]),ori_objbuf,NET_MAX_DATALEN - *remainlen);
					*remainlen = NET_MAX_DATALEN;
					*buf = ori_objbuf;
				}
				memcpy(*buf,SpecialWord[j],strlen(SpecialWord[j]));
				*buf += strlen(SpecialWord[j]);	//这里之所以可以直接+而不考虑溢出,是因为
												//上面的if(remainlen <= strlen(SpecialWord[j]))
				*remainlen -= strlen(SpecialWord[j]);
				break;
			}
		}

		if(j < SPECIAL_NUM)
		{
			i++;
			continue;
		}

		cpyachar(buf,&srcbuf[i],remainlen,ori_objbuf);
		i++;
	}

}

//
//功能：把一个nodeStru结构里面的sign写到目标字符串
//
bool cpysign(char **buf,
			 char *sign,
			 int signlen,
			 int *remainlen,
			 char *ori_objbuf)
{
	cpyachar(buf, "<", remainlen, ori_objbuf);
	formatcpybuf(buf, sign, signlen, remainlen, ori_objbuf);
	cpyachar(buf, ">", remainlen, ori_objbuf);

	return true;
}

//
//功能：把一个nodeStru结构里面的sign结束写到目标字符串
//
//注意：先不考虑特殊字符的替换，以后要加上
//
bool cpyendsign(char **buf,
			 char *sign,
			 int signlen,
			 int *remainlen,
			 char *ori_objbuf)
{
	cpyachar(buf,"<", remainlen, ori_objbuf);
	cpyachar(buf,"/", remainlen, ori_objbuf);
	formatcpybuf(buf, sign,signlen, remainlen, ori_objbuf);
	cpyachar(buf,">", remainlen, ori_objbuf);

	return true;
}

//
//功能：把一个nodeStru结构里面的sign结束写到目标字符串
//
bool cpyelement(char **buf,
				char *elem,
				int elemlen,
				int *remainlen,
				char *ori_objbuf)
{
	formatcpybuf(buf,elem,elemlen,remainlen,ori_objbuf);
	return true;
}

//
//把一个nodeStru树写给一个char[]
//
//思路：先把node的sign拷给目标缓冲区，然后判断node是否是element，如果是
//则把element拷给目标缓冲区，不是的话，把child node作为参数，递归调用此
//函数，然后写</...>，写完后把brother node作为参数，递归调用此函数
//
void NodeToStrAndSend(struct nodeStru **pnode,	//nodeStru的第一个指针
					  char **objbuf,				//要拷贝的位置
					  int *remainlen,			//还可以拷贝的长度
					  char *ori_objbuf)			//发送缓冲区的起始地址，这个值始终不变
{
	if(!(*pnode))
		return;

	cpysign(objbuf,(*pnode)->sign.sign,(*pnode)->sign.len,remainlen,ori_objbuf);

	if((*pnode)->type == TYPE_ELEM)
		cpyelement(objbuf,(*pnode)->element.element,(*pnode)->element.len,remainlen,ori_objbuf);
	else
	{
		if((*pnode)->child)
			NodeToStrAndSend(&(*pnode)->child,objbuf,remainlen,ori_objbuf);
	}
	cpyendsign(objbuf,(*pnode)->sign.sign,(*pnode)->sign.len,remainlen,ori_objbuf);

	if((*pnode)->brother)
		NodeToStrAndSend(&(*pnode)->brother,objbuf,remainlen,ori_objbuf);
	
	if((*pnode)->type == TYPE_ELEM)
		if((*pnode)->element.len > 0)
			free((*pnode)->element.element);

	free((*pnode));
	*pnode = NULL;
}

//
//功能：把一个打包好的xmlpge结构转化成一个标准的xml字符串
//
bool XmlpgeToStrAndSend(struct xmlpgeStru *pxmlpge)
{
	char sendbuf[NET_MAX_DATALEN];
	int remainlen = NET_MAX_DATALEN;
	char *hbuf = sendbuf;

	if(!pxmlpge)
		return true;

	cpysign(&hbuf,pxmlpge->name,strlen(pxmlpge->name),&remainlen,sendbuf);
	NodeToStrAndSend(&(pxmlpge->node),&hbuf,&remainlen,sendbuf);
	cpyendsign(&hbuf, pxmlpge->name, strlen(pxmlpge->name), &remainlen, sendbuf);

//	sendbuf[NET_MAX_DATALEN - remainlen] = 0;
//	AfxMessageBox(sendbuf);
	SendToSocket(&(SocketInterf.Socket[1]),sendbuf,NET_MAX_DATALEN - remainlen);
	free(pxmlpge);

	return true;
}

//
//功能：把已经填充完节点的xml结构加上xml请求或响应的头，
//使其成为一包规范的xmlpge包
//
struct xmlpgeStru* FormatXmlpge(struct nodeStru *pnode,
								 int type)
{
	struct xmlpgeStru *pxmlpge;
	pxmlpge = (struct xmlpgeStru *)malloc(sizeof(struct xmlpgeStru));

	if(type == TYPE_REQ)
		strcpy((char*)pxmlpge->name,REQ);
	else
		strcpy((char*)pxmlpge->name,ACK);

	pxmlpge->node = pnode;
	return pxmlpge;
}

//add for debug,output strcut xmlpgestru data
void OutXmlnode(struct nodeStru* pnode)
{
	if(!pnode)
		return;
	if(pnode->type == TYPE_NODE)
		printf("%s\n",pnode->sign.sign);
	else
		printf("%s   %s\n",pnode->sign.sign,pnode->element.element);
	OutXmlnode(pnode->child);
	OutXmlnode(pnode->brother);
	return;
}
