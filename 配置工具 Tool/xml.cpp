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

#define STATE0  0		//��ͨ״̬
#define STATE1  1		//�ļ�����,��xml�ļ�����<name>
#define STATE2  2		//�ڵ�����,��xml�ڵ����<name>
#define STATE3  3		//����
#define STATE4  4		//����

//����xmlͨѶЭ���õ��ĳ���
#define FIND_NORMAL		0
#define FIND_LEFT		1
#define FIND_RIGHT		2
#define FIND_REQ		3
#define FIND_ACK		4
#define FIND_END		5

#define SPECIALW_NORMAL 100		//��ͨ�ַ�
#define SPECIALW_BEGIN  10		//'&'
#define SPECIALW_NEXT	0		//'&'�����

#define MATCH_NONE	0			//û���κ�ƥ��������ַ�
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

struct sramfileStru sramfile;	//���͸߶��ļ��Ŀ�����
extern UpSRAMStru mSRAMFile;

//���͸�usb203�Ľӿ�
BOOL SendToSocket(int *fd, char *msg,int len)
{
	int i = 0;
	if(*fd)
	{
//		SetDebugHistory(msg, len, false);
		int ret=send(*fd, (const char*)msg, len , 0);
		if(ret==SOCKET_ERROR)
		{
			AfxMessageBox("����ͨѶ�������������ӷ�����");
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
	���ܣ���ά���ӽ����ٻ�ģ����
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ�ң����
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ�˫��ң����
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ��ۼ���
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ��߶������б�
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ��߶��ļ�����
	������
	���أ�
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
	���ܣ���ά���ӽ����ٻ��߶��ļ���
	������
	���أ�
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
	���ܣ�ɾ��ָ���ĸ߶��ļ�
	������
	���أ�
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
	���ܣ�У��
	������
	���أ�
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
	���ܣ���λϵͳ
	������
	���أ�
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
	���ܣ��趨ֵ
	������
	���أ�
*************************************************/
bool CallSetData(void *para)
{
	struct nodeStru *phnode = (struct nodeStru*)para;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));

	return true;
}

/*************************************************
	���ܣ��趨ֵ
	������
	���أ�
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
//���ܣ������ַ����滻����,����ֻ���������ַ����������������ַ�������
//ʹ�÷�Χ�������ڽ���xml�����ַ���
//
bool ReplaceXmlWord(char *srcStr,		//Դ�ڴ�
					int  *srclen		//Դ�ڴ泤��
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
		case SPECIALW_BEGIN:		//֮����Ҫ����Ϊ��Э����������Ϊ���е������ַ�������&��ͷ
									//�����һ���������ã����Խ�ʡ��������ʱ��
			for(count=0; count < SPECIAL_NUM; count++)
			{
				if(matchword & BitMask[count])
				{
					if(j >= strlen(SpecialWord[count]))	//�ҵ�
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
			else	//������������������Э�飬�������ͨ�Ļ���Ӧ���ã�
					//spc = SPECIALW_NOMAL; i++; ���������
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
				if(tempj >= strlen(SpecialWord[count]))	//�ҵ�ƥ���ַ���(��ƥ����Ǹ�),
														//Ȼ���������ַ����滻
				{
					tempbuf[tempi++] = SpecialChar[count];
					i += tempj;
					j = 0;
					spc = SPECIALW_NORMAL;
					matchword = 0;
					break;
				}
			}
			if(count >= SPECIAL_NUM)//��ͨ�Ļ�Ӧ����spc = SPECIALW_NARMAL; i++;����
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
//���ܣ��ѽ����õ�xml�ṹ���ʽ��,Ҳ����ת���ַ�ת����ԭ�����ַ�
//���Ϸ������:����&,<,>,",'�ȷ�ת���ַ�,�����Ǳ�׼��ת���ַ�
//
bool FormatXmlStr(char *XmlStr)
{
	return true;
}

//
//����:�ж��ļ���ڵ����Ƿ�Ϸ�
//���Ϸ������,��ʽ������ַ����г���&,<,>,",'�ȷǷ��ַ�
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

//���ܣ���ʼ��һ��xmlpgeStru
void IntXmlpge(struct xmlpgeStru *pxml)
{
	pxml->node = NULL;
}

//
//����: ��ʼ��һ��nodeStru�ڵ�
//
void IntNode(struct nodeStru *pnode)
{
	pnode->sign.len = 0;
	pnode->element.len = 0;
	pnode->brother = pnode->child = NULL;
	pnode->type = TYPE_NODE;
}

//
//���ܣ�����һ��nodeStru�ṹ�洢�����������ʼ��
//
void NewIntNode(struct nodeStru **pnode)
{
	*pnode = (struct nodeStru*)malloc(sizeof(struct nodeStru));
	IntNode(*pnode);
}

//
//���ܣ�����һ���ַ�����nodeStru->sign��nodeStru->element
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
//���ܣ�����һ���ַ�����nodeStru->sign��nodeStru->element
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
//����:����һ���ڵ�,������������ӽڵ�
//����:������󷵻�false,�ڷ���false֮ǰ�ͷŵ�����������ڴ�
//
bool ParseNode(char *nodestr,
			   int len,
			   struct nodeStru **pnode
			   )
{
	char *pheadstr = nodestr;
	int head = 0;
	struct nodeStru *pchildnode;
	struct nodeStru *ptchildnode = *pnode;	//childβָ��,���ָ�������pnode��child
	struct nodeStru *ptbronode = NULL;				//brotherβָ��,���ָ�������pnode����һ���ӽڵ�
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
		//pnode->brother = NULL;		//����֮���Բ�Ҫ����Ϊ�ڵ������������ʱ���Ѿ�������ʼ������
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
				return false;		//û���ҵ�'>'
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
									signlen+3)))//����ԭ��:û��</>
			{
				RelNode(pnode);
				return false;
			}
//			head = int(findposi - pheadstr) + 3 + signlen;
			//�ҵ�<></>��˵������һ���ڵ㣬��<></>�����������Ϊ�����ݹ���ô˺���
			pchildnode = (struct nodeStru *)malloc(sizeof(struct nodeStru));
			IntNode(pchildnode);
			memcpy(pchildnode->sign.sign,tempstr+2,signlen);
			if(!ReplaceXmlWord(pchildnode->sign.sign,&signlen))
			{
//				printf("parsenode err!");
				return false;
			}
			if(!CheckSign(pchildnode->sign.sign,signlen))		//����ԭ��:������&,<,>�ȷǷ��ַ�
				return false;

			pchildnode->sign.len = signlen;
			pchildnode->sign.sign[signlen] = '\0';
			if(ptchildnode->child == NULL)	//����ֻ�ҽӵ�һ���ӽӵ㣬�����ӽڵ�ͨ����һ���ֽڵ��brother�ҽ�
			{
				(*pnode)->child = pchildnode;
				ptbronode = pchildnode;			//��һ���ӽڵ�
			}
			else
			{
				ptbronode->brother = pchildnode;	//�ҽ�brother
				ptbronode = pchildnode;
			}
			head += signlen + 1;	//��λ��<sign>����ĵ�һ���ַ�

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
//����:����xmlpge�ṹ�µĵ�һ��ڵ�,������������ӽڵ�
//����:������󷵻�false,�ڷ���false֮ǰ�ͷŵ�����������ڴ�
//
bool ParseXmlNode(char *nodestr,
			   int len,
			   struct nodeStru **pnode
			   )
{
	char *pheadstr = nodestr;
	int head = 0;
	struct nodeStru *pchildnode;
	struct nodeStru *ptchildnode = *pnode;	//childβָ��,���ָ�������pnode��child
	struct nodeStru *ptbronode = NULL;				//brotherβָ��,���ָ�������pnode����һ���ӽڵ�
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
				return false;		//û���ҵ�'>'
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
									signlen+3)))//����ԭ��:û��</>
			{
				printf("parsexmlnode err!\n");
				return false;
			}
			head += signlen + 1;	//��λ��<sign>����ĵ�һ���ַ�
			//�ҵ�<></>��˵������һ���ڵ㣬��<></>�����������Ϊ�����ݹ���ô˺���
			pchildnode = (struct nodeStru *)malloc(sizeof(struct nodeStru));
			IntNode(pchildnode);
			memcpy(pchildnode->sign.sign,tempstr+2,signlen);
			if(!ReplaceXmlWord(pchildnode->sign.sign,&signlen))
			{
//				printf("parsexmlnode err!\n");
				return false;
			}
			if(!CheckSign(pchildnode->sign.sign,signlen))		//����ԭ��:������&,<,>�ȷǷ��ַ�
				return false;

			pchildnode->sign.len = signlen;
			pchildnode->sign.sign[signlen] = '\0';
			if(ptchildnode == NULL)	//����ֻ�ҽӵ�һ���ӽӵ㣬�����ӽڵ�ͨ����һ���ֽڵ��brother�ҽ�
			{
				*pnode = pchildnode;
				ptbronode = pchildnode;			//��һ���ӽڵ�
			}
			else
			{
				ptbronode->brother = pchildnode;	//�ҽ�brother
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
//���ܣ��ͷŵ�struct nodeStru
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
//���ܣ��ͷŵ�strcut xmlpgeStru
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
//���ܣ���δ��ת���ַ�ת����ԭ�����ַ����ַ���������xmlstru�ṹ
//
bool ParseXmlStr(char *XmlStr,				//Դ�ַ���
				 int  len,					//Դ�ַ�������
				 struct xmlpgeStru *pxml	//��Ž�����xml�ṹ��,
											//���ĳ�ʼ�����ڵ�����������ĺ�����
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
		case STATE0:			//��ͨ״̬,Ҳ����ʱ��״̬�����κα��
								//Ԫ�ػ�����
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
				return false; //���������' '�ֲ���'<',����
			break;
		case STATE1:				//xml�ļ���
			posi1 = (char *)memmem(XmlStr,len-head,">",1);
			if(posi1 == 0)
				return false;
			namelen = (int)(posi1 - XmlStr - head);
			if(namelen > XMLNAME_LEN)
				return false;

			tempstr[0]='<';
			tempstr[1]='/';

			memcpy(tempstr+2,XmlStr+head,namelen); //ע�⣬����copyʱû�п�����Ǹ�'/0'
			tempstr[2+namelen] = '>';
			tempstr[3+namelen] = '\0';
			if(!(findposi = (char*)memmem(XmlStr+head,
									len-head,
									tempstr,
									namelen+3)))//����ԭ��:û��</>
				return false;
			if(findposi-XmlStr+namelen+3 < len)   //+3����Ϊ��</>3���ַ�,����ԭ��:</>�����ַ�
				return false;
			memcpy(pxml->name, XmlStr+head, namelen);
			pxml->name[namelen] = '\0';
			head += 1+namelen;

			if(!ReplaceXmlWord(pxml->name,&namelen))
			{
//				printf("parsexmlstr err!");
				return false;
			}

			if(!CheckSign(pxml->name,namelen))		//����ԭ��:������&,<,>�ȷǷ��ַ�
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
//���ܣ��ڸ������������ҳ�һ������<Req>...</Req>��<Ack>...</Ack>�Ľṹ��
//		����������һ���»�������ͬʱ������Ϲ淶�Ķ����ַ���
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
				if(j >= strlen(ACK))	//ƥ��
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
				if(j >= strlen(ACK))	//ƥ��
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
		case FIND_RIGHT:	//���û��
			if(!bfindhead)		//�����Ǵ���<...>
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
	*objbuf = (char *)malloc(*objlen+1);	//��1��Ŀ��Ϊ�����ַ�����һ��'\0',Ϊ����print����������Ҳû��ϵ
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

//	strcpy(*objbuf, "<Ack><Di><Cmd>ack</Cmd><DiObj><Name>name</Name><State>��</State><Index>0</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>1</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>2</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>3</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>4</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>5</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>6</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>7</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>8</Index></DiObj><DiObj><Name>name</Name><State>��</State><Index>9</Index></DiObj><FirstData>y</FirstData><LastData>n</LastData></Di></Ack>");
//����Ϊ���Դ���
	*srcget = findedend;
	return true;
}

/***************************************************************
*
*
*			���ʹ�����
*
*
****************************************************************/

//
//���ܣ�����һ���ַ���Ŀ�귢�ͻ�������Ŀ�귢�ͻ�����������ˣ���ô���ͳ�ȥ
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
//���ܣ���һ������������Ŀ�귢�ͻ��������ڿ�����ͬʱ�������ַ����滻�����ַ�
//		Ŀ�귢�ͻ�����������ˣ���ô���ͳ�ȥ����պ��������copy
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
				*buf += strlen(SpecialWord[j]);	//����֮���Կ���ֱ��+�����������,����Ϊ
												//�����if(remainlen <= strlen(SpecialWord[j]))
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
//���ܣ���һ��nodeStru�ṹ�����signд��Ŀ���ַ���
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
//���ܣ���һ��nodeStru�ṹ�����sign����д��Ŀ���ַ���
//
//ע�⣺�Ȳ����������ַ����滻���Ժ�Ҫ����
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
//���ܣ���һ��nodeStru�ṹ�����sign����д��Ŀ���ַ���
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
//��һ��nodeStru��д��һ��char[]
//
//˼·���Ȱ�node��sign����Ŀ�껺������Ȼ���ж�node�Ƿ���element�������
//���element����Ŀ�껺���������ǵĻ�����child node��Ϊ�������ݹ���ô�
//������Ȼ��д</...>��д����brother node��Ϊ�������ݹ���ô˺���
//
void NodeToStrAndSend(struct nodeStru **pnode,	//nodeStru�ĵ�һ��ָ��
					  char **objbuf,				//Ҫ������λ��
					  int *remainlen,			//�����Կ����ĳ���
					  char *ori_objbuf)			//���ͻ���������ʼ��ַ�����ֵʼ�ղ���
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
//���ܣ���һ������õ�xmlpge�ṹת����һ����׼��xml�ַ���
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
//���ܣ����Ѿ������ڵ��xml�ṹ����xml�������Ӧ��ͷ��
//ʹ���Ϊһ���淶��xmlpge��
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
