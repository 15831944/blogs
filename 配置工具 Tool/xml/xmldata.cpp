#include "stdafx.h"
#include "demo.h"
#include "xml.h"
#include "xmldata.h"
#include "MainFrm.h"
#include "myfun.h"

#define OBJ_NAME_LEN 32		//object max name length

int mSaveBackAi=0,mSaveBackDi=0,mSaveBackCi=0,mSaveBackDo;	//save back data send position
int mSaveCurAi=0,mSaveCurDi=0,mSaveCurCi=0,mSaveCurDo;		//save curtent data send position

int *aiindex = NULL;	//������ͨѶЭ��ģ������ٻ�ĳЩģ��������ű���Ļ�����
int *ciindex = NULL;	//ͬ��
int *diindex = NULL;	//ͬ��
int *doindex = NULL;	//ͬ��

struct xmtfileStru mxmtfile;	//�������Ϲ��ܵ��ļ����Ϳ����֣������˱���
struct filesStru mfiles;		//�������Ϲ��ܵ��ļ�Ŀ¼�����֣������˱���

struct rcvfileStru mrcvfile;	//�ļ����տ�����

struct scadaStru scadadata;

extern short NoAnalogs;
extern short NoContacts;
extern short NoAccums;
extern short NoDouts;
extern short NoSbos;

extern int REQUESTSBO(UWORD Index, UBYTE Type, UWORD Duration);
extern int REQUESTDOUT(unsigned short Index, unsigned char bVal);
extern int GetAiValue(unsigned short index, unsigned int *pYcValue);
extern int GetCiValue(UWORD index, UDWORD *pKwhValue);
extern int GetDiValue(UWORD index, char *pYxValue);
extern int GetDoValue (UWORD index, UBYTE *pDoValue);
extern void InitSavedSRAM();
extern UINT NetRcv1(LPVOID para);

//these function for debug
void OutXmlnode(struct nodeStru* pnode);

extern bool bwait_bytes;
extern int wait_bytes_len;

extern bool WaitSramFileCon;
extern UpSRAMStru mSRAMFile;
//
//���ܣ���ʼ���ļ�����ṹ
//
void IntXmtFile()
{
	int i;
	mxmtfile.filetype = FILE_NOFILE;
	mfiles.filebuf = (char*)malloc(FILE_BUF_LEN);
	mfiles.get = mfiles.put = 0;
	mfiles.bfull = false;
	for(i=0; i<MAX_FILE_NUM; i++)
		mfiles.file[i].filetype = FILE_NOFILE;
}

void RelXmtFile()
{
	free(mfiles.filebuf);
}

//
//���ܣ���ʼ��ͨѶЭ��
//
void IntProtocol()
{
	IntXmtFile();
}

//
//���ܣ��ش�һ�����ݵ�ȷ������
//
void ReqDataConfirm(char *pname,bool bsuccess)
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;
/*	
	AddANode(&pnewnode,TYPE_NODE,"Req",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;
*/	
	AddANode(&pnewnode,TYPE_NODE,pname,NULL);
//	pcurnode->child = pnewnode;
	phnode = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;
/*
	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;
*/
	if(bsuccess)
		AddANode(&pnewnode,TYPE_ELEM,"Success","y");
	else
		AddANode(&pnewnode,TYPE_ELEM,"Success","n");
	pcurnode->brother = pnewnode;

	//����
	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
}

//
//���ܣ��ش�һ���ļ���ȷ������
//
void ReqFileConfirm(char *pname,bool bsuccess)
{
	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;
	
	AddANode(&pnewnode,TYPE_NODE,"Req",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;
	
	AddANode(&pnewnode,TYPE_NODE,pname,NULL);
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_NODE,"Cmd","req");
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Num","0");
	pcurnode->brother = pnewnode;

	if(bsuccess)
		AddANode(&pnewnode,TYPE_ELEM,"Success","y");
	else
		AddANode(&pnewnode,TYPE_ELEM,"Success","n");
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_REQ));
}


/*******************************************************************
*
*
*		������Ӧ����
*
*
*******************************************************************/
//
//���ܴ�����Ӧģ��������
//�ڶ���������Ϊ���ص��·����һ��EntityObjStru*
//
/*
bool DisposeAckAiObj(struct nodeStru *pAckAiObjnode, CRightAiView *pAiView)
{
	struct nodeStru *pnode = pAckAiObjnode;

	char sname[]  = "Name";
	char sdata[]  = "Data";
	char sindex[] = "Index";
	char sscale[] = "Scale";

	char ainame[OBJ_NAME_LEN+1] = "";
	int aidata = 0;
	int aiindex = 0;
	int aiscale = 1;
	char formatstr[32];

	CStringArray AiObjStrArr;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			if(pnode->element.len > OBJ_NAME_LEN)
			{
				return false;
			}
			memcpy(ainame,pnode->element.element,pnode->element.len);
			ainame[pnode->element.len] = '\0';
		}
		else if(!memcmp(pnode->sign.sign,sdata,strlen(sdata)))
		{
			aidata = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sindex,strlen(sindex)))
		{
			aiindex = atoi(pnode->element.element);
			if(aiindex < 0)
			{
				return false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sscale,strlen(sscale)))
		{
			aiscale = atoi(pnode->element.element);
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}
	_snprintf(formatstr,sizeof(formatstr),"%d",aiindex);
	AiObjStrArr.Add(formatstr);

	AiObjStrArr.Add(ainame);

//	float faidata = aidata;
//	_snprintf(formatstr,sizeof(formatstr),"%0.3f", faidata/1000);
//	AiObjStrArr.Add(formatstr);
	AiObjStrArr.Add(Str(aidata));

	_snprintf(formatstr,sizeof(formatstr),"%d",aiscale);
	AiObjStrArr.Add(formatstr);
	
	pAiView->SendMessage(ADD_A_ITEM_MSG, (WPARAM)(&AiObjStrArr), NULL);
	return true;
}

extern unsigned char WaitAdjustCounter;
//
//���ܣ�������ӦУ��
//
bool DisposeAckAdjust(struct nodeStru *pAdjustnode)
{
	struct nodeStru *pnode = pAdjustnode;
	bool bsuccess= false;
	char scmd[] = "Cmd";
	char ssuccess[] = "Success";
	FuncHistoryStruct FuncHistory;

	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,ssuccess,strlen(ssuccess)))
		{
			if(!memcmp(pnode->element.element,"y",1))	//��ͬ����0
				bsuccess = true;
			else
				bsuccess = false;
		}
//		else
//			return false;
		pnode = pnode->brother;
	}

	if(bsuccess)
	{
		WaitAdjustCounter |= 0x80;
		SetFuncHistory(&FuncHistory, "", OPER_ADJUST, true);
		AfxMessageBox("У���ɹ�");
	}
	else
	{
		WaitAdjustCounter = 0x7E;	//0x80=128���������Ա�־�ɹ��������˳��ȴ��߳�
									//=0x7E(ע�ⲻ��|=) ���Ը��ɹ����𿪣�����Ҳ�˳��߳�
									//����0x7F��ԭ�����߳������++�����ɹ������ֲ�����
		SetFuncHistory(&FuncHistory, "", OPER_ADJUST, false);
		AfxMessageBox("У��ʧ��");
	}
	NodityWorkSpace(FUNC_HISTORY_SPACE, 1, (void*)&FuncHistory);

	return true;
}

extern unsigned char WaitSetDataCounter;
//
//���ܣ�������Ӧ�趨����
//
bool DisposeAckSetData(struct nodeStru *pSetDatanode)
{
	struct nodeStru *pnode = pSetDatanode;
	bool bsuccess= false;
	char scmd[] = "Cmd";
	char ssuccess[] = "Success";
	FuncHistoryStruct FuncHistory;

	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,ssuccess,strlen(ssuccess)))
		{
			if(!memcmp(pnode->element.element,"y",1))	//��ͬ����0
				bsuccess = true;
			else
				bsuccess = false;
		}
		pnode = pnode->brother;
	}

	if(bsuccess)
	{
		WaitSetDataCounter |= 0x80;
		SetFuncHistory(&FuncHistory, "", OPER_SETDATA, true);
	}
	else
	{
		WaitSetDataCounter = 0x7E;
		SetFuncHistory(&FuncHistory, "", OPER_SETDATA, false);
	}
	NodityWorkSpace(FUNC_HISTORY_SPACE, 1, (void*)&FuncHistory);

	return true;
}

//
//���ܣ�������Ӧ�趨����
//
bool DisposeAckResetData(struct nodeStru *pResetDatanode)
{
	struct nodeStru *pnode = pResetDatanode;
	bool bsuccess= false;
	char scmd[] = "Cmd";
	char ssuccess[] = "Success";
	FuncHistoryStruct FuncHistory;

	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,ssuccess,strlen(ssuccess)))
		{
			if(!memcmp(pnode->element.element,"y",1))	//��ͬ����0
				bsuccess = true;
			else
				bsuccess = false;
		}
		pnode = pnode->brother;
	}

	if(bsuccess)
	{
		WaitSetDataCounter |= 0x80;
		SetFuncHistory(&FuncHistory, "", OPER_RESETDATA, true);
	}
	else
	{
		WaitSetDataCounter = 0x7E;
		SetFuncHistory(&FuncHistory, "", OPER_RESETDATA, false);
	}
	NodityWorkSpace(FUNC_HISTORY_SPACE, 1, (void*)&FuncHistory);

	return true;
}
*/
//
//���ܣ�������Ӧ��λ
//
bool DisposeAckReset(struct nodeStru *pResetnode)
{
	struct nodeStru *pnode = pResetnode;
//	bool bsuccess= false;
	char scmd[] = "Cmd";
//	char ssuccess[] = "Success";
//	FuncHistoryStruct FuncHistory;

	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		pnode = pnode->brother;
	}

//	SetFuncHistory(&FuncHistory, "", OPER_REBOOT, true);
//	NodityWorkSpace(FUNC_HISTORY_SPACE, 1, (void*)&FuncHistory);
	AfxMessageBox("�豸����3�����ڸ�λ");
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//pFrame->m_wndWorkspace.Invalidate();
	return true;
}
/*
//
//���ܣ�������Ӧģ����
//
bool DisposeAckAi(struct nodeStru *pAckAinode)
{
	struct nodeStru *pnode = pAckAinode;
	char saiobj[] = "AiObj";
	char scmd[] = "Cmd";
	char sfirstdata[] = "FirstData";
	char slastdata[] = "LastData";
	bool blastdata = false;
	bool bfirstdata = false;
	CView *pView;
	CRightAiView *pAiView;

	bool bPackUsbPge = true;
	int col, row;
	unsigned short row_col = 0;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pView = (CView*)pFrame->SendMessage(GET_SPLITTER_VIEW, (WPARAM)NULL, (LPARAM)&row_col);
	if(!pView)
		return false;
//	if (pView->IsKindOf(RUNTIME_CLASS(CRightAiView)))
//		return false;
	pAiView = (CRightAiView *)pView;

	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,saiobj,strlen(saiobj)))
		{
			if(!DisposeAckAiObj(pnode->child, pAiView))
			{
				//�Ӵ����ͷŵ���ǰ���������pentityobj�ڴ�
				bPackUsbPge = false;
				break;
			}
		}
		else if(!memcmp(pnode->sign.sign,sfirstdata,strlen(sfirstdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				bfirstdata = true;
			else
				bfirstdata = false;
		}
		else if(!memcmp(pnode->sign.sign,slastdata,strlen(slastdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				blastdata = true;
			else
				blastdata = false;
		}
		else
			return false;

		pnode = pnode->brother;
	}
	if(bfirstdata)
	{}//strcat(mlinuxcmd.CmdPara, "f");
	if(blastdata)
	{}//strcat(mlinuxcmd.CmdPara, "l");

	//�����Ҫ����ȷ�ϣ�дȷ�ϴ���
	if(!blastdata)
	{
		ReqDataConfirm("Ai",bPackUsbPge);
	}
	return true;
}

//
//���ܴ�����Ӧң��������
//
bool DisposeAckDiObj(struct nodeStru *pAckDiObjnode, CRightDiView *pDiView)
{
	struct nodeStru *pnode = pAckDiObjnode;

	char sname[]  = "Name";
	char sstate[]  = "State";
	char sindex[] = "Index";
//	char slastdata[] = "LastData";

	char diname[OBJ_NAME_LEN+1] = "";
	bool bdistate = false;	//trueΪ��,falseΪ��
	int diindex = 0;
//	bool blastdata = true;
	char formatstr[32];

	CStringArray DiObjStrArr;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			if(pnode->element.len > OBJ_NAME_LEN)
			{
				return false;
			}
			memcpy(diname,pnode->element.element,pnode->element.len);
			diname[pnode->element.len] = '\0';
		}
		else if(!memcmp(pnode->sign.sign,sstate,strlen(sstate)))
		{
			//bdistate = atoi(pnode->element.element);
			if(strcmp(pnode->element.element , "��") == 0)
				bdistate = true;
			else
				bdistate = false;
		}
		else if(!memcmp(pnode->sign.sign,sindex,strlen(sindex)))
		{
			diindex = atoi(pnode->element.element);
			if(diindex < 0)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}
	_snprintf(formatstr,sizeof(formatstr),"%d",diindex);
	DiObjStrArr.Add(formatstr);

//	strcat((*pentityobj)->EntityObj,diname);
	DiObjStrArr.Add(diname);

	if(bdistate)
		DiObjStrArr.Add("��");//strcat((*pentityobj)->EntityObj,"��");
	else
		DiObjStrArr.Add("  ��");//strcat((*pentityobj)->EntityObj,"��");

	pDiView->SendMessage(ADD_A_ITEM_MSG, (WPARAM)(&DiObjStrArr), NULL);

	return true;
}

const char *_str_ddi_stata[] = { "",				//0
								"",				//1
								"˫���",		//2
								"˫���",		//3
								"˫�ֲ�ȷ��",	//4
								"˫�ϲ�ȷ��"	//5
};

//
//���ܴ�����Ӧ˫��ң��������
//
bool DisposeAckDDiObj(struct nodeStru *pAckDDiObjnode, CRightDDiView *pDDiView)
{
	struct nodeStru *pnode = pAckDDiObjnode;

	char sname[]  = "Name";
	char sstate[]  = "State";
	char sindex[] = "Index";
//	char slastdata[] = "LastData";

	char ddiname[OBJ_NAME_LEN+1] = "";
	char sddistate[32];
	int ddiindex = 0;
//	bool blastdata = true;
	char formatstr[32];
	int i;

	CStringArray DDiObjStrArr;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			if(pnode->element.len > OBJ_NAME_LEN)
			{
				return false;
			}
			memcpy(ddiname,pnode->element.element,pnode->element.len);
			ddiname[pnode->element.len] = '\0';
		}
		else if(!memcmp(pnode->sign.sign, sstate, strlen(sstate)))
		{
//			strcpy(sddistate, pnode->element.element);
			i = atoi(pnode->element.element);
			if( (i < 2) || (i > 5) )
				i = 4;	//˫�ֲ�ȷ��
			strcpy(sddistate, _str_ddi_stata[i]);
		}
		else if(!memcmp(pnode->sign.sign, sindex, strlen(sindex)))
		{
			ddiindex = atoi(pnode->element.element);
			if(ddiindex < 0)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}
	_snprintf(formatstr,sizeof(formatstr), "%d", ddiindex);
	DDiObjStrArr.Add(formatstr);
	DDiObjStrArr.Add(ddiname);
	DDiObjStrArr.Add(sddistate);
	pDDiView->SendMessage(ADD_A_ITEM_MSG, (WPARAM)(&DDiObjStrArr), NULL);

	return true;
}

//
//���ܣ�������Ӧң����
//
bool DisposeAckDi(struct nodeStru *pAckDinode)
{
	struct nodeStru *pnode = pAckDinode;
	char sdiobj[] = "DiObj";
	char scmd[] = "Cmd";
	char slastdata[] = "LastData";
	char sfirstdata[] = "FirstData";
	bool blastdata = false;
	bool bfirstdata = false;

	CView *pView;
	CRightDiView *pDiView;

	bool bPackUsbPge = true;
	int col, row;
	unsigned short row_col = 0;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pView = (CView*)pFrame->SendMessage(GET_SPLITTER_VIEW, (WPARAM)NULL, (LPARAM)&row_col);
	if(!pView)
		return false;
//	if (pView->IsKindOf(RUNTIME_CLASS(CRightCiView)))
//		return false;
	pDiView = (CRightDiView *)pView;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,sdiobj,strlen(sdiobj)))
		{
			if(!DisposeAckDiObj(pnode->child, pDiView))
			{
				//��Ӵ����ͷŵ��ѷ�����ڴ�
				bPackUsbPge = false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sfirstdata,strlen(sfirstdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				bfirstdata = true;
			else
				bfirstdata = false;
		}
		else if(!memcmp(pnode->sign.sign,slastdata,strlen(slastdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				blastdata = true;
			else	//ֻҪ����"��"������Ϊ��"��"
				blastdata = false;
		}
		else
			return false;

		pnode = pnode->brother;
	}

	if(bfirstdata)
	{}//strcat(mlinuxcmd.CmdPara, "f");
	if(blastdata)
	{}//AfxMessageBox("���������ս���");//strcat(mlinuxcmd.CmdPara, "l");
	//��������ӷ��͵�usb�ڵĴ���

	//�����Ҫ����ȷ��

	if(!blastdata)
		ReqDataConfirm("Di",bPackUsbPge);
	return true;
}

//
//���ܣ�������Ӧң����
//
bool DisposeAckDDi(struct nodeStru *pAckDDinode)
{
	struct nodeStru *pnode = pAckDDinode;
	char sddiobj[] = "DDiObj";
	char scmd[] = "Cmd";
	char slastdata[] = "LastData";
	char sfirstdata[] = "FirstData";
	bool blastdata = false;
	bool bfirstdata = false;

	CView *pView;
	CRightDDiView *pDDiView;

	bool bPackUsbPge = true;
	int col, row;
	unsigned short row_col = 0;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pView = (CView*)pFrame->SendMessage(GET_SPLITTER_VIEW, (WPARAM)NULL, (LPARAM)&row_col);
	if(!pView)
		return false;
//	if (pView->IsKindOf(RUNTIME_CLASS(CRightCiView)))
//		return false;
	pDDiView = (CRightDDiView *)pView;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,sddiobj,strlen(sddiobj)))
		{
			if(!DisposeAckDDiObj(pnode->child, pDDiView))
			{
				//��Ӵ����ͷŵ��ѷ�����ڴ�
				bPackUsbPge = false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sfirstdata,strlen(sfirstdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				bfirstdata = true;
			else
				bfirstdata = false;
		}
		else if(!memcmp(pnode->sign.sign,slastdata,strlen(slastdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				blastdata = true;
			else	//ֻҪ����"��"������Ϊ��"��"
				blastdata = false;
		}
		else
			return false;

		pnode = pnode->brother;
	}

	if(bfirstdata)
	{}//strcat(mlinuxcmd.CmdPara, "f");
	if(blastdata)
	{}//AfxMessageBox("���������ս���");//strcat(mlinuxcmd.CmdPara, "l");
	//��������ӷ��͵�usb�ڵĴ���

	//�����Ҫ����ȷ��

	if(!blastdata)
		ReqDataConfirm("DDi",bPackUsbPge);
	return true;
}

//
//���ܴ�����Ӧ�ۼ�������
//
bool DisposeAckCiObj(struct nodeStru *pAckCiObjnode, CRightCiView *pCiView)
{
	struct nodeStru *pnode = pAckCiObjnode;

	char sname[]  = "Name";
	char sdata[]  = "Data";
	char sindex[] = "Index";
	char sscale[] = "Scale";
//	char slastdata[] = "LastData";

	char ciname[OBJ_NAME_LEN+1] = "";
	int cidata = 0;
	int ciindex = 0;
	int ciscale = 1;
//	int blastdata = true;

	char formatstr[32];
	CStringArray CiObjStrArr;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			if(pnode->element.len > OBJ_NAME_LEN)
			{
				return false;
			}
			memcpy(ciname,pnode->element.element,pnode->element.len);
			ciname[pnode->element.len] = '\0';
		}
		else if(!memcmp(pnode->sign.sign,sdata,strlen(sdata)))
		{
			cidata = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sindex,strlen(sindex)))
		{
			ciindex = atoi(pnode->element.element);
			if(ciindex < 0)
			{
				return false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sscale,strlen(sscale)))
		{
			ciscale = atoi(pnode->element.element);
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}
	_snprintf(formatstr,sizeof(formatstr),"%d",ciindex);
	CiObjStrArr.Add(formatstr);

//	strcat((*pentityobj)->EntityObj,ciname);
	CiObjStrArr.Add(ciname);

	_snprintf(formatstr,sizeof(formatstr),"%d",cidata);
	CiObjStrArr.Add(formatstr);

	_snprintf(formatstr,sizeof(formatstr),"%d",ciscale);
	CiObjStrArr.Add(formatstr);

	pCiView->SendMessage(ADD_A_ITEM_MSG, (WPARAM)(&CiObjStrArr), NULL);

	return true;
}

//
//���ܣ�������Ӧ�ۼ���
//
bool DisposeAckCi(struct nodeStru *pAckCinode)
{
	struct nodeStru *pnode = pAckCinode;
	char sciobj[] = "CiObj";
	char scmd[] = "Cmd";
	char slastdata[] = "LastData";
	char sfirstdata[] = "FirstData";
	bool blastdata = false;
	bool bfirstdata = false;

	CView *pView;
	CRightCiView *pCiView;

	bool bPackUsbPge = true;
	int col, row;
	unsigned short row_col = 0;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pView = (CView*)pFrame->SendMessage(GET_SPLITTER_VIEW, (WPARAM)NULL, (LPARAM)&row_col);
	if(!pView)
		return false;
//	if (pView->IsKindOf(RUNTIME_CLASS(CRightCiView)))
//		return false;
	pCiView = (CRightCiView *)pView;
	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,sciobj,strlen(sciobj)))
		{
			if(!DisposeAckCiObj(pnode->child, pCiView))
			{
				//��Ӵ����ͷŵ���������ڴ�
				bPackUsbPge = false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sfirstdata,strlen(sfirstdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				bfirstdata = true;
			else
				bfirstdata = false;
		}
		else if(!memcmp(pnode->sign.sign,slastdata,strlen(slastdata)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				blastdata = true;
			else
				blastdata = false;
		}
		else
			return false;

		pnode = pnode->brother;
	}

	if(bfirstdata)
	{}//strcat(mlinuxcmd.CmdPara, "f");
	if(blastdata)
	{}//AfxMessageBox("�ۼ������ս���");//strcat(mlinuxcmd.CmdPara, "l");

	//��������ӷ��͵�usb�ڵĴ���

	//�����Ҫ����ȷ��
	if(!blastdata)
		ReqDataConfirm("Ci",bPackUsbPge);
	return true;
}

//
//���ܣ������ļ���Ӧ
//
bool DisposeAckFile(struct nodeStru *pAckFilenode)
{
	struct nodeStru *pnode = pAckFilenode;
	char scmd[] = "Cmd";
	char sfilename[] = "FileName";
	char sname[] = "Name";
	char stype[] = "Type";
	char ssize[] = "Size";
	char sblocknum[] = "BlockNum";

	int mfilename = -1;
	char mname[MAX_FILE_NAME_LEN];
	int mtype = 0;
	int msize = -1;
	int mblocknum = 1;

	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,sfilename,strlen(sfilename)))
		{
			mfilename = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			memcpy(mname,pnode->element.element,pnode->element.len);
		}
		else if(!memcmp(pnode->sign.sign,stype,strlen(stype)))
		{
			mtype = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,ssize,strlen(ssize)))
		{
			msize = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sblocknum,strlen(sblocknum)))
		{
			mblocknum = atoi(pnode->element.element);
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}

	if(mfilename < 0)
		return false;
	mrcvfile.filename = mfilename;
	mrcvfile.filelen = msize;
	mrcvfile.filetype = mtype;
	if(msize <= 0)
		return false;
	mrcvfile.filebuf = (char*)malloc(sizeof(msize));
	mrcvfile.tail = 0;
	mrcvfile.blocknum = mblocknum;
	mrcvfile.curblock = 0;
	memcpy(mrcvfile.name,mname,MAX_FILE_NAME_LEN);

	AddANode(&pnewnode,TYPE_NODE,"FileBlock",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

//	snprintf(itoastr,sizeof(itoastr),"%d",mfilename);

//	AddANode(&pnewnode,TYPE_ELEM,"BlockNo","0");

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_ACK));
	return true;
}

//
//���ܣ������ļ���ȡʧ�������pc
//
void BackFileErrToPc()
{
	return;
}

//
//���ܣ������ļ���usb��
//
void SendFileToPc()
{
	return;
}

//
//���ܣ������ļ�����Ӧ
//
bool DisposeAckBlock(struct nodeStru *pAckBlocknode)
{
	struct nodeStru *pnode = pAckBlocknode;
	char scmd[] = "Cmd";
	char sfilename[] = "FileName";
	char sblocksize[] = "BlockSize";
	char sblockno[] = "BlockNo";
	char scontent[] = "Content";
	char slastblock[] = "LastBlock";

	int mfilename = -1;
	int mblocksize = 0;
	int mblockno = 0;
	char mcontent[MAX_BLOCK_LEN];
	bool blastblock = false;

	struct nodeStru *phnode;
	struct nodeStru *pnewnode,*pcurnode;

	char itoastr[20];

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!memcmp(pnode->sign.sign,sfilename,strlen(sfilename)))
		{
			mfilename = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sblockno,strlen(sblockno)))
		{
			mblockno = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sblocksize,strlen(sblocksize)))
		{
			mblocksize = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,scontent,strlen(scontent)))
		{
			memcpy(mcontent,pnode->element.element,MAX_BLOCK_LEN);
		}
		else if(!memcmp(pnode->sign.sign,slastblock,strlen(slastblock)))
		{
			if(!memcmp(pnode->element.element,"y",1))
				blastblock = true;
			else
				blastblock = false;
		}
		else
		{
			return false;
		}

		pnode = pnode->brother;
	}

	if( (mrcvfile.filename != mfilename) ||
		(mblockno > mrcvfile.blocknum) ||
		((mrcvfile.curblock+1) != mblockno) ||
		((mrcvfile.tail + mblocksize) > (mrcvfile.filelen)) )
	{
		BackFileErrToPc();
		return false;
	}

	memcpy(mrcvfile.filebuf+mrcvfile.tail,mcontent,mblocksize);
	if(!blastblock)
	{
		mrcvfile.curblock += 1;
		mrcvfile.tail += MAX_BLOCK_LEN;
	}
	
	AddANode(&pnewnode,TYPE_NODE,"FileBlock",NULL);
	phnode = pnewnode;
	pcurnode = pnewnode;

	_snprintf(itoastr,sizeof(itoastr),"%d",mfilename);
	AddANode(&pnewnode,TYPE_ELEM,"FileName",itoastr);
	pcurnode->child = pnewnode;
	pcurnode = pnewnode;

	_snprintf(itoastr,sizeof(itoastr),"%d",mblockno);
	AddANode(&pnewnode,TYPE_ELEM,"BlockNo",itoastr);
	pcurnode->brother = pnewnode;
	pcurnode = pnewnode;

	AddANode(&pnewnode,TYPE_ELEM,"Success","y");
	pcurnode->brother = pnewnode;

	XmlpgeToStrAndSend(FormatXmlpge(phnode,TYPE_ACK));

	if(mrcvfile.curblock >= mrcvfile.blocknum)
	{}//�������д�ļ��Ĵ���//��ǰ�Ĵ�����SendFileToPc();

	return true;
}

//
//���ܣ�����߶��ļ�����
//
bool DisposeAckSRAMListObj(struct nodeStru *pAckFileObjnode, CSramTreeView *pTreeView)
{
#define MAX_SRAM_FILENAME_LEN 18

	struct nodeStru *pnode = pAckFileObjnode;

	char sname[]  = "Name";
	char stype[]  = "Type";
	char sindex[] = "Index";

	char filename[MAX_SRAM_FILENAME_LEN+1];
	int type = 0;
	int index = 0;

	char formatstr[32];

	CStringArray SramFileListStrArr;

	while(pnode)
	{
		if(!memcmp(pnode->sign.sign,sname,strlen(sname)))
		{
			if(pnode->element.len > MAX_SRAM_FILENAME_LEN)
				pnode->element.len = MAX_SRAM_FILENAME_LEN;
			memcpy(filename,pnode->element.element,pnode->element.len);
			filename[pnode->element.len] = '\0';
		}
		else if(!memcmp(pnode->sign.sign,stype,strlen(stype)))
		{
			type = atoi(pnode->element.element);
		}
		else if(!memcmp(pnode->sign.sign,sindex,strlen(sindex)))
		{
			index = atoi(pnode->element.element);
		}
		else
		{
			return false;
		}
		pnode = pnode->brother;
	}
	_snprintf(formatstr,sizeof(formatstr),"%d",index);
	SramFileListStrArr.Add(formatstr);

	_snprintf(formatstr, sizeof(formatstr), "%d", type);
	SramFileListStrArr.Add(formatstr);

//	strcat((*pentityobj)->EntityObj,filename);
	SramFileListStrArr.Add(filename);

	pTreeView->SendMessage(LOADING_SRAM_LIST, (WPARAM)&SramFileListStrArr, NULL);

	return true;
}

//
//���ܣ�����߶������б�
//
bool DisposeAckSRAMList(struct nodeStru *pAckSRAMnode)
{
	struct nodeStru *pnode = pAckSRAMnode;
	char sfileobj[] = "FileObj";
	char scmd[] = "Cmd";
	int col, row;
	unsigned short row_col = 0;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();	
	CView *pView = (CView*)pFrame->SendMessage(GET_SPLITTER_VIEW, (WPARAM)NULL, (LPARAM)&row_col);
	if(!pView)
		return false;
//	if(!pView->IsKindOf(RUNTIME_CLASS(CSramTreeView)))
//		break;

	InitSavedSRAM();
	CSramTreeView *pTreeView = (CSramTreeView *)pView;
	pTreeView->RemoveItems();
	while(pnode) 
	{
		if(!memcmp(pnode->sign.sign,scmd,strlen(scmd)))
		{
			if(memcmp(pnode->element.element,"ack",3))
			{
				return false;
			}
		}
		else if(!memcmp(pnode->sign.sign,sfileobj,strlen(sfileobj)))
		{
			if(!DisposeAckSRAMListObj(pnode->child, pTreeView))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		pnode = pnode->brother;
	}
	pTreeView->SendMessage(FINISH_LOAD_SRAM_LIST, (WPARAM)NULL, NULL);
	//��ӷ��ʹ���
//	SendToUsb(&mlinuxcmd);
	return true;
}

//
//���ܣ������ļ���Ӧ
//
bool DisposeAckSRAMFile(struct nodeStru *pAckFilenode)
{
	struct nodeStru *pnode = pAckFilenode;
	char scmd[] = "Cmd";
	char sindex[] = "Index";
	char srequest[] = "Request";
	char sdatasize[] = "DataSize";
	char sblocknum[] = "BlockNum";

#define REQ_SRAM_NONE	0
#define REQ_SRAM_NAME	1
#define REQ_SRAM_DATA	2

	int mindex = -1;
	int mdatasize = -1;
	int mblocknum = 1;
	int mrequest = REQ_SRAM_NONE;

	while(pnode)
	{
		if(!strcmp(pnode->sign.sign,scmd))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!strcmp(pnode->sign.sign,sindex))
		{
			mindex = atoi(pnode->element.element);
		}
		else if(!strcmp(pnode->sign.sign,srequest))
		{
			if(strcmp(pnode->element.element, "name"))
				mrequest = REQ_SRAM_NAME;
			else if(strcmp(pnode->element.element, "data"))
				mrequest = REQ_SRAM_DATA;
		}
		else if(!strcmp(pnode->sign.sign,sdatasize))
		{
			mdatasize = atoi(pnode->element.element);
		}
		else if(!strcmp(pnode->sign.sign,sblocknum))
		{
			mblocknum = atoi(pnode->element.element);
		}

		pnode = pnode->brother;
	}

	if((mindex < 0) || (mindex >= 32) || (mindex != mSRAMFile.Index))
		return false;

	if(mindex == mSRAMFile.Index)
		WaitSramFileCon = true;
	if(mblocknum <= 0)
		return true;
	mSRAMFile.BlockNum = mblocknum;
	mSRAMFile.CurBlock = 0;
	if(mSRAMFile.size > 0)
		delete []mSRAMFile.FileBuf;
	mSRAMFile.size = mdatasize;
	if(mSRAMFile.size > 0)
		mSRAMFile.FileBuf = new char[mdatasize];
	mSRAMFile.tail = 0;
//���͸�usb��
	//
	return true;
}

//
//���ܣ������ļ�����Ӧ
//
bool DisposeAckSRAMBlock(struct nodeStru *pAckBlocknode)
{
	struct nodeStru *pnode = pAckBlocknode;
	char scmd[] = "Cmd";
	char sindex[] = "Index";
	char sblocksize[] = "BlockSize";
	char sblockno[] = "BlockNo";

	int mindex = -1;
	int mblockno = 1;
	int msize = -1;

	int i = 0;

	while(pnode)
	{
		if(!strcmp(pnode->sign.sign,scmd))
		{
			if(memcmp(pnode->element.element,"ack",3))
				return false;
		}
		else if(!strcmp(pnode->sign.sign,sindex))
		{
			mindex = atoi(pnode->element.element);
		}
		else if(!strcmp(pnode->sign.sign,sblockno))
		{
			mblockno = atoi(pnode->element.element);
		}
		else if(!strcmp(pnode->sign.sign,sblocksize))
		{
			msize = atoi(pnode->element.element);
		}
		else
			continue;

		pnode = pnode->brother;
	}

	if((mindex != mSRAMFile.Index) || (mblockno != mSRAMFile.CurBlock))
		return false;

	wait_bytes_len = msize;
	bwait_bytes = true;

	while(NetRcv1(NULL) && (i++ < 1500))
		Sleep(20);
	if( i >= 1500)
		return false;

	return true;
}

//
//���ܣ������ļ���������Ӧ
//
bool DisposeAckSRAMBlockData(char *msg, int len)
{
//	SendDataToUsb(msg, len);
	if((mSRAMFile.size - mSRAMFile.tail) < len)
		return false;
	memcpy(mSRAMFile.FileBuf + mSRAMFile.tail, msg, len);
	mSRAMFile.CurBlock++;
	mSRAMFile.tail += len;
	return true;
}
*/
//
//���ܣ�������Ӧ����
//
bool DisposeAck(struct nodeStru *pAcknode)
{
	char sai[] = "Ai";
	char sdi[] = "Di";
	char sci[] = "Ci";
	char sddi[] = "DDi";
	char sdostate[] = "DoState";
	char sfile[] = "File";
	char sfileblock[] = "FileBlock";
	char ssbo[] = "Sbo";
	char sdo[] = "Do";
	char sfilelist[] = "FileList";
	char sadjust[] = "Adjust";
	char sreset[] = "Reset";
	char ssetdata[] = "SetData";
	char sresetdata[] = "ResetData";

	struct nodeStru *pnode = pAcknode;

	while(pnode)
	{
/*		if(!strcmp(pnode->sign.sign,sai))
			DisposeAckAi(pnode->child);
		else if(!strcmp(pnode->sign.sign,sdi))
			DisposeAckDi(pnode->child);
		else if(!strcmp(pnode->sign.sign,sddi))
			DisposeAckDDi(pnode->child);
		else if(!strcmp(pnode->sign.sign,sci))
			DisposeAckCi(pnode->child);
		else if(!strcmp(pnode->sign.sign,sfile))
			//DisposeAckFile(pnode->child);
			DisposeAckSRAMFile(pnode->child);
		else if(!strcmp(pnode->sign.sign,sfileblock))
			//DisposeAckBlock(pnode->child);
			DisposeAckSRAMBlock(pnode->child);
		else if(!strcmp(pnode->sign.sign,sfilelist))
			DisposeAckSRAMList(pnode->child);
		else if(!strcmp(pnode->sign.sign, sadjust))
			DisposeAckAdjust(pnode->child);
		else if(!strcmp(pnode->sign.sign, ssetdata))
			DisposeAckSetData(pnode->child);
		else if(!strcmp(pnode->sign.sign, sresetdata))
			DisposeAckResetData(pnode->child);
		else if(!strcmp(pnode->sign.sign, sreset))
			DisposeAckReset(pnode->child);
*/
		if(!strcmp(pnode->sign.sign, sreset))
			DisposeAckReset(pnode->child);
		else
			return false;

		pnode = pnode->brother;
	}
	return true;
}

//
//���ܣ�����һ���Ѿ������õ�xmlpackage
//
bool DisPoseXmlStr(struct xmlpgeStru *ppackage)
{
//	char sreq[] = "Req";
//	char sack[] = "Ack";

	if(!memcmp(ppackage->name,ACK,3))
		return DisposeAck(ppackage->node);
	else
		return false;

	return true;
}
