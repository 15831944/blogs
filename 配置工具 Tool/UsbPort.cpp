#include "stdafx.h"
#include <direct.h>
#include "demo.h"
#include "MainFrm.h"
#include "MyFun.h"
#include "uftp.h"
#include "UpLoadDlg.h"
#include "DownLoadDlg.h"

void SendDataToUsb();
void WaitConfirm();
UINT WaitTimeOut(void *para);
bool WaitFileCon;
extern CDemoApp theApp;
extern CUpLoadDlg UpLoadDlg;
extern CDownLoadDlg DownLoadDlg;
SavedSRAMStru SavedSRAM[MAX_SRAM_FILENUM];
//UsbXmtStru* XmtFileMsg = NULL;  //�ļ�ͨѶ����ͷָ�룬�����ڴ�������
								//���ļ�ʱ������ʱ�������ݻ���
//UsbXmtStru* XmtFileTail= NULL;  //�ļ�ͨѶ����βָ��
UsbXmtStru* XmtDataMsg = NULL;  //�ɼ����ݻ���ͷָ��
UsbXmtStru* XmtDataTail= NULL;	//�ɼ����ݻ���βָ��
bool bSystemIsRuning = false;   //ϵͳ����״̬
int DataCtrlType = STREAMCTRL;  //���ݿ��Ʒ�ʽ�������������Ʒ�ʽ
int WaitConfirmType = 0;        //��־�ȴ�ȷ�ϵ�����

int WaitCmdType = WAIT_CMD;     //�ȴ����������ͣ��Ǳ�׼������ļ�������
int WaitFileLen;                //ϣ���յ����ļ��Ŀ�ĳ���

#define MAX_RCV_LEN 4096
unsigned char RcvBuf[MAX_RCV_LEN];     //��ʱ����4096���Ժ����ʵ�ʴ�����С���޸�
int RcvGet = 0,RcvPut = 0;        //�ջ������շ�ָ��
unsigned char* RcvPtr;			//����ָ�룬������ǵ�ǰ���յ�RcvBuf�е�ƫ����
TimeOutStru mWaitTimeOut;

UpFileStru mUpFile;
//extern UpSRAMStru mSRAMFile;
bool bAlowUpLoad, bAlowDownLoad;
extern BOOL PcUsbComm(HUFTP hUFTP, TCHAR *msg, DWORD len,bool bNeedRequest);
extern BOOL Uftp_GetSimple(HUFTP hUFTP);
extern bool WaitSramFileCon;
/******************************************************
	ע������û�о���˵��Ӧ�÷�Χ�ĺ������ǿ���
		�������еط���
*******************************************************/
void InitSavedSRAM()
{
	char i = 0;
	while(i < MAX_SRAM_FILENUM)
	{
		SavedSRAM[i].bValid = false;
		SavedSRAM[i].bSavedData = false;
		SavedSRAM[i].sFileName = "";
		SavedSRAM[i].sSavedFilename = "";
		SavedSRAM[i].type = -1;
		i++;
	}
}

void InitUsb()
{
//	mSRAMFile.size = 0;
//	InitSavedSRAM();
}

void SaveDebugToFile(char filename[], unsigned char DbgBuf[], unsigned int len)
{
	CFile file;
	file.Open(filename, CFile::modeWrite | CFile::modeCreate, NULL);
	file.Write((void*)DbgBuf, len);
	file.Close();
}
/*******************************************************
	Ӧ�÷�Χ�������ƺͿ���Ƶ�Ӧ��
	���ܣ����usb�ڻ�����ֽ���
	��������
	���أ�I�� �����Ʒ�ʽ��usb�ڻ�����ֽ���
		  II������Ʒ�ʽ��usb���л���Ŀ���
*******************************************************/
int GetNumFromUsb()
{
	int GetNum = 0;
	switch(DataCtrlType)
	{
	case STREAMCTRL:
		GetNum = 0;
	case BLOCKCTRL:
		GetNum = 0;
	}

	return GetNum;
}

/*******************************************************
	Ӧ�÷�Χ�������Ƶ�Ӧ��
	���ܣ���usb�ڻ����ж���ָ����Ŀ���ֽ�
	�������������ݻ�������ַ��ϣ����usb�������ж�����byte��
	���أ����usb��������ϣ����ȡ��������bytes������ϣ������
	      ֵ�����򷵻�ʵ�ʶ���������
********************************************************/
int ReadFromUsb(unsigned char *RcvMsg, int Len)
{
	return Len;
}

/*********************************************************
	Ӧ�÷�Χ�������ƺͿ���Ƶ�Ӧ��
	���ܣ�I�������Ʒ�ʽ������usb�ڻ��������е��ֽ�
		  II������Ʒ�ʽ������usb�ڻ�����һ������
	�������������ݻ�������ַ
	���أ�ʵ�ʶ���������
*********************************************************/
int ReadFromUsb(unsigned char *RcvMsg)
{
	int ReadNum = 0;
	switch(DataCtrlType)
	{
	case STREAMCTRL:
		ReadNum = 0;
	case BLOCKCTRL:
		ReadNum = 0;
	}

	return ReadNum;
}

/***************************************************************
	���ܣ���usb�����ݻ����������һ�����ݳ���������ȴ�������ͨ���
		�����'$'��'\n'���ж�һ�����ݣ���������ļ��Ŀ鳤����ȷ��
		һ�����ݡ�
	�������������ݻ�������ַ
	���أ�ʵ�ʶ������ֽ���
	ע�⣺�������usb�ڻ������ݻ�����������ݲ���1���Ļ����򷵻�-1��
****************************************************************/
int ReadAPackageFromUsb(unsigned char *RcvMsg)
{
	int tempGet = RcvGet;
	int i=0;
	if(mWaitTimeOut.wait_flag != RSP_WAIT_FILE_DATA)
	{
		while((tempGet != RcvPut) && (RcvBuf[tempGet] != '$'))
			tempGet = (tempGet+1) % MAX_RCV_LEN;
		while(tempGet != RcvPut)
		{
			*(RcvMsg++) = RcvBuf[tempGet];
			i++;
			if(RcvBuf[tempGet] = '\n')
			{
				tempGet = (tempGet+1) % MAX_RCV_LEN;
				RcvGet = tempGet;
				return i;
			}
			tempGet = (tempGet+1) % MAX_RCV_LEN;
		}
	}
	else
	{
		int srclen = (RcvPut - RcvGet + MAX_RCV_LEN) % MAX_RCV_LEN;
		if(srclen < mUpFile.BlockSize)
			return -1;
		i = 0;
		while(i++ < mUpFile.BlockSize)
		{
			*(RcvMsg+i) = *(RcvBuf + RcvGet++);
			if(RcvGet >= MAX_RCV_LEN)
				RcvGet = 0;
		}
		return mUpFile.BlockSize;
	}
	return -1;
}
/*********************************************************
	���ܣ���usb�ڷ���ָ�����ȵ��ֽ�
	������I - ���ͻ�������ַ
	      II - ���ͳ���
	���أ�ʵ�ʷ����ֽ���
	ע�⣺���͵����ݶ������ֽڴ��ķ�ʽ���͵�
**********************************************************/
int WriteToUsb(char *msg,int len)
{
	return len;
}

/*********************************************************
	���ܣ���usb�ڷ����ַ���
	���������͵��ַ���
	���أ�ʵ�ʷ����ֽ���
	ע�⣺���͵����ݶ������ֽڴ��ķ�ʽ���͵�
**********************************************************/
int WriteToUsb(CString str)
{
	return 0;
}

/*********************************************************
	���ܣ�usb��ͨѶ���̣߳������й�usb�ڵ�ͨѶ����������
		  ʵ�ֵģ�ϵͳ��ʼ���󼴰�������֪��ϵͳ��������
		  �ű��ͷŵ���
		  ��Ҫ֧�ֹ��ܣ�
			1���ɼ�mk�е�ģ������ң�������ۼ���
			2����mkʱ�ӵ��趨
			3����mk��ʽ�ֵ����غ�����
			4����mk��pc�����ļ����໥����
			5����λϵͳ
			6���鿴��ɱ��ϵͳ����
			7������mk�������
	ע�⣺MainThreadֻ����,���ܷ�,���ķ���ͨ������SendDataToUsb
		������ʵ�ֵ�,���ڷ�ʲô,MainThread����֪��
**********************************************************/
UINT MainThread(LPVOID para)
{
	unsigned char RcvMsg[4096];
	int RcvLen = 0;
	AfxBeginThread(SendDataToUsb,NULL);
	while(bSystemIsRuning)
	{
		RcvLen = GetNumFromUsb();//ReadAPackageFromUsb(RcvMsg);
		if(RcvLen <= 0)
		{
			Sleep(200);
			continue;
		}
		if(ReadAPackageFromUsb(RcvMsg) < 0)
		{
			Sleep(50);
			continue;
		}
		if (Dispose(RcvMsg,RcvLen) == FALSE)
		{
			AfxMessageBox("�����ʱ���ִ����˳����߳�");
			break;
		}
		Sleep(200);
	}
	return TRUE;
}

/**********************************************************
	���ܣ�ȷ����ǰҪ��usb���з�������
		  Ϊ�������ṩ��ǰҪ�������ݣ���������Ҫ��usb�ڷ�����
		  ��ȫ�����������ȥ
	��������
	ע�⣺����Ҫ���������Ǵ�file��data���������������ġ�
		file�������ȼ�����data
		���ߵ�������Դ�Ǹ���MainThread�յ����ݺ󣬷�����Ӧ�Ĵ�
		���������д���󣬸�����Ҫ������2�������
***********************************************************/
UINT SendDataToUsb(LPVOID para)
{
//	unsigned char *XmtMsg;
//	int XmtLen;
	UsbXmtStru *tempPtr;
	while(bSystemIsRuning)
	{
		if(XmtDataMsg != NULL)
		{
			if(!WriteToUsb(XmtDataMsg->msg,XmtDataMsg->msglen))
				AfxMessageBox("����ʧ�ܣ������·���");
			tempPtr = XmtDataMsg;
			XmtDataMsg = XmtDataMsg->next;
			mWaitTimeOut.wait_flag = XmtDataMsg->wait_flag;
			mWaitTimeOut.timeout = XmtDataMsg->timeout;
			delete[] tempPtr->msg;
			delete tempPtr;
			WaitTimeOut(NULL);
		}
		Sleep(200);
	}
	return TRUE;
}

UINT WaitTimeOut(void *para)
{
	while(mWaitTimeOut.wait_flag && mWaitTimeOut.timeout)
	{
		mWaitTimeOut.timeout -= 50;
	}
	if(mWaitTimeOut.timeout <= 0)
	{
		mWaitTimeOut.wait_flag = RSP_NONE;
		AfxMessageBox("�ȴ���ʱ,�������ٻ�!");
	}

	return TRUE;
}

void AddDataToXmtList(char *msg,int len,int type, int priority, int wait_flag, int timeout)
{
	UsbXmtStru *pTempXmt, *pFindXmt1, *pFindXmt2;
	if( (len <=0) || (len > 4096) )
		return;
	switch(type)
	{
	case XMT_FILE:
	case XMT_DATA:
		pTempXmt = new UsbXmtStru;
		pTempXmt->msg = new char[len];
		pTempXmt->priority = priority;
		memcpy(pTempXmt->msg,msg,len);
		pTempXmt->msglen = len;
		pTempXmt->next = NULL;
		pTempXmt->wait_flag = wait_flag;
		pTempXmt->timeout = timeout;
		//�����ȼ�����ǰ��˳����½ڵ���뵽����������
		pFindXmt1 = NULL;
		pFindXmt2 = XmtDataMsg;
		while(pFindXmt2)
		{
			if(pFindXmt2->priority < pTempXmt->priority)
				break;
			pFindXmt1 = pFindXmt2;
			pFindXmt2 = pFindXmt2->next;
		}
		if(!pFindXmt1)
			XmtDataMsg = pTempXmt;
		else
			pFindXmt1->next = pTempXmt;
		pTempXmt->next = pFindXmt2;
		if(!pFindXmt2)
			XmtDataTail = pTempXmt;
		break;
	default:
		AfxMessageBox("�������˴���ķ������ݵ����ͣ���ȷ��");
		break;
	}
}

bool WaitFileData(unsigned char *msg, int len)
{
	//�ݲ�����д�ļ�ʧ��
	if(!mUpFile.hfile.m_hFile)
		return false;
	mUpFile.hfile.Write(msg,len);
	WaitFileCon = true;

	return true;
}

//
//�ͷŵ�LinuxCmdStru�ṹ��
//
void RelLinuxCmd(LinuxCmdStru *LinuxCmd)
{
	EntityStru *pEntity = LinuxCmd->Entity, **pDelEntity;
	EntityObjStru *pEntityObj,**pDelEntityObj;

	while(pEntity)
	{
		pEntityObj = pEntity->EntityObj;
		while(pEntityObj)
		{
			pDelEntityObj = &pEntityObj;
			(*pDelEntityObj)->EntityObj.RemoveAll();
			pEntityObj = pEntityObj->next;
			delete *pDelEntityObj;
			*pDelEntityObj = NULL;
		}
		pDelEntity = &pEntity;
		pEntity = pEntity->next;
		delete *pDelEntity;
		*pDelEntity = NULL;
	}
}

/**********************************************************
	���ܣ���������
	������I�� ������ַ
		  II�������
	���أ��ɹ�����TRUE,ʧ�ܷ���FALSE
**********************************************************/
BOOL Dispose(unsigned char *msg,int len)
{
//	CString( LPCTSTR lpch, int nLength ); 
	LinuxCmdStru LinuxCmd;
	CString CmdName;
	bool returnVal = false;
	switch(mWaitTimeOut.wait_flag)
	{
	case RSP_WAIT_FILE_DATA:
		returnVal = WaitFileData(msg,len);
		break;
	default:
		if(TransToLinuxCmd(msg,len,&LinuxCmd) == FALSE)
		{
			AfxMessageBox("����ΪLinux����ʱ���ִ���!");
			return FALSE;
		}
		CmdName = LinuxCmd.CmdName;
		CmdName.MakeLower();
		if(LinuxCmd.CmdName == CREAD)// = "read";
		{}
		else if(LinuxCmd.CmdName == CPUT)// = "put";
		{}
		else if(LinuxCmd.CmdName == CRSP)// = "rsp";
			returnVal = WaitConfirm(&LinuxCmd);
		break;
	} //end switch

	if(returnVal)
		return TRUE;
	else
		return FALSE;
}

int CheckRspErr(LinuxCmdStru *LinuxCmd)
{
	EntityStru *pEntity;
	CString mDescriptor;
	int rtnVal = -1;

	pEntity = LinuxCmd->Entity;
	while(pEntity != NULL)
	{
		mDescriptor = pEntity->character;
		if(mDescriptor.Compare("ok") == 0)
		{
			if(rtnVal >= 0)
				return -1;
			rtnVal = RSP_OK;
		}
		else if(mDescriptor.Compare("err") == 0)
		{
			if(rtnVal >= 0)
				return -1;
			rtnVal = RSP_ERR;
		}
		else
			return -1;
		pEntity = pEntity->next;
	}
	return rtnVal;
}

/*
void ConfirmLs(LinuxCmdStru *LinuxCmd, CRightListView *pObjView)
{
}

void ConfirmCp(LinuxCmdStru *LinuxCmd)
{
}

void ConfirmRm(LinuxCmdStru *LinuxCmd)
{
}

void ConfirmMkDir(LinuxCmdStru *LinuxCmd)
{

}

void ConfirmRead(LinuxCmdStru *LinuxCmd, CView *pView)
{

}

void ConfirmReboot(LinuxCmdStru *LinuxCmd)
{

}

void ConfirmIfConfig(LinuxCmdStru *LinuxCmd, CView *pView)
{

}

void ConfirmDate(LinuxCmdStru *LinuxCmd, CView *pView)
{

}
*/
bool ConfirmGet(LinuxCmdStru *LinuxCmd)
{
	EntityStru *pEntity;
	EntityObjStru *pEntityObj;
	int mInsItem = 0;
	CString mDescriptor;
	int bGetConfirm = 0x00;

	pEntity = LinuxCmd->Entity;
	while(pEntity != NULL)
	{
		mDescriptor = pEntity->character;
		pEntityObj = pEntity->EntityObj;
		while(pEntityObj != NULL)
		{
			if(mDescriptor == DCPT_FILEEXIST)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					if(pEntityObj->EntityObj.GetAt(0) != "y")
						break;
					if(mUpFile.PCPath.Right(1) != "\\")
						mUpFile.PCPath += "\\";
					if(!mUpFile.hfile.Open(mUpFile.PCPath+mUpFile.FileName, CFile::modeWrite | CFile::modeCreate, NULL))
						mUpFile.hfile.m_hFile = 0;
					bGetConfirm |= 0x01;
				}
			}
			else if(mDescriptor == DCPT_SIZE)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					mUpFile.FileSize = atoi(pEntityObj->EntityObj.GetAt(0));
					bGetConfirm |= 0x02;
				}
			}
			else if(mDescriptor == DCPT_BLOCKNUM)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					mUpFile.BlockNum = atoi(pEntityObj->EntityObj.GetAt(0));
					bGetConfirm |= 0x04;
				}
			}
			else if(mDescriptor == DCPT_TIMEOUT)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					mUpFile.TimeOut = atoi(pEntityObj->EntityObj.GetAt(0));
					bGetConfirm |= 0x08;
				}
			}
			pEntityObj = pEntityObj->next;
		}
		pEntity = pEntity->next;
	}
	if(bGetConfirm != 0x0f)
		WaitFileCon = false;
	else
		WaitFileCon = true;
	return true;
}

bool ConfirmGetFile(LinuxCmdStru *LinuxCmd)
{
	EntityStru *pEntity;
	EntityObjStru *pEntityObj;
	int mInsItem = 0;
	CString mDescriptor;
	bool BlockConfirm = false;

	pEntity = LinuxCmd->Entity;
	while(pEntity != NULL)
	{
		mDescriptor = pEntity->character;
		pEntityObj = pEntity->EntityObj;
		while(pEntityObj != NULL)
		{
			if(mDescriptor == DCPT_BLOCKNO)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					if(mUpFile.CurBlock == atoi(pEntityObj->EntityObj.GetAt(0)))
						BlockConfirm = true;
				}
			}
			else if(mDescriptor == DCPT_BLOCKSIZE)
			{
				if(pEntityObj->EntityObj.GetSize() > 0)
				{
					mUpFile.BlockSize = atoi(pEntityObj->EntityObj.GetAt(0));
				}
			}
			pEntityObj = pEntityObj->next;
		}
		pEntity = pEntity->next;
	}
	WaitFileCon = BlockConfirm;
	mWaitTimeOut.wait_flag = RSP_WAIT_FILE_DATA;
	mWaitTimeOut.timeout = 3000;
	return true;
}

bool ConfirmPut(LinuxCmdStru *LinuxCmd)
{
	return true;
}

bool ConfirmPutFile(LinuxCmdStru *LinuxCmd)
{
	return (CheckRspErr(LinuxCmd) == RSP_OK);
}

bool ConfirmFileData(LinuxCmdStru *LinuxCmd)
{
	return (CheckRspErr(LinuxCmd) == RSP_OK);
}

bool ConfirmSramList(LinuxCmdStru *LinuxCmd, CView *pView)
{
	return true;
}

bool ConfirmSramFile(LinuxCmdStru *LinuxCmd)
{
	return true;
}

bool ConfirmSramBlock(LinuxCmdStru *LinuxCmd)
{
	return true;
}

bool ConfirmReset(LinuxCmdStru *LinuxCmd)
{
	AfxMessageBox("ϵͳ�յ���λ�������5���ڸ�λ");
	return true;
}

bool WaitConfirm(LinuxCmdStru *LinuxCmd)
{
	CString mDescriptor;
	int col, row;
	unsigned short row_col = 0;
	int mInsItem = 0;
	int mWaitConfirmType = mWaitTimeOut.wait_flag;
	bool returnVal = false;
	if(!mWaitConfirmType)
	{
		RelLinuxCmd(LinuxCmd);
		return false;
	}

	mWaitTimeOut.wait_flag = RSP_NONE;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CView *pView = NULL;
	row = 0;
	col = 1;
	row_col = row;
	row_col <<= 8;
	row_col = (row_col & 0xff00) | col;	//1Ϊ�к�

	switch(mWaitConfirmType)
	{
	case RSP_PUT:// = 11;
		returnVal = ConfirmPut(LinuxCmd);
		break;
	case RSP_PUT_FILE:
		returnVal = ConfirmPutFile(LinuxCmd);
		break;
	case RSP_FILE_DATA:
		returnVal = ConfirmFileData(LinuxCmd);
		break;
	case RSP_GET://
		returnVal = ConfirmGet(LinuxCmd);
		break;
	case RSP_GET_FILE:
		returnVal = ConfirmGetFile(LinuxCmd);
		break;
	case RSP_RESET:
		returnVal = ConfirmReset(LinuxCmd);
		break;
	default:
		break;
	}
	RelLinuxCmd(LinuxCmd);
	return returnVal;
}

/********************************************************
	Ӧ�÷�Χ��Ӧ���ڳ��ļ����������������Э���ʽ�ķ���
	���ܣ��Ѹ������ַ�������ɱ�׼��linux����ṹ
	������I��  �ַ�����ַ
		  II�� ����
		  III������linux�ṹ��ָ��
	���أ�����Ǹ�����������ʽ����FALSE����ȷ�ķ���TRUE
*********************************************************/
BOOL TransToLinuxCmd(unsigned char *msg,
					 int len,
					 LinuxCmdStru *LinuxCmd)
{
	if (len<0)
		return FALSE;

	if (*msg != '$')
		return FALSE;

	CString str;
	int Pos,StartPos,SpacePos,EnterPos;
	memcpy(str.GetBuffer(len),msg,len); 
	str.ReleaseBuffer();
	//��ʼ��LinuxCmd
	LinuxCmd->Entity = NULL;

	//����������
	StartPos = 1;
	CString CommandStr;
	SpacePos = str.Find(" ",1);

	EnterPos = str.Find("\n",1);

	if (SpacePos < 0)
		Pos = EnterPos;
	else
		Pos = SpacePos;

	if(Pos < 0)
		return FALSE;

	LinuxCmd->CmdName = str.Mid(StartPos,Pos - StartPos);
	LinuxCmd->CmdName.TrimLeft();
	LinuxCmd->CmdName.TrimRight();

	//���������������ͨ����
	StartPos = str.Find(" ",Pos);
	int i;
	while(StartPos >= 0)
	{
		i = 1;
		while(str.Mid(StartPos+i,1) == " ")
			i++;
		StartPos += i;
		if((str.Mid(StartPos,1) == "<") || (str.Mid(StartPos,1) == "["))
		{
			StartPos = -1;//str.Find(" ",StartPos);
			continue;
		}

		SpacePos = str.Find(" ",StartPos);
		EnterPos = str.Find("\n",StartPos);

		if (SpacePos < 0)
			Pos = EnterPos;
		else
			Pos = SpacePos;

		if (Pos < 0)
			return FALSE;

		if(str.Mid(StartPos,1) == "-")
		{
			LinuxCmd->CmdPara = str.Mid(StartPos+1,Pos - StartPos);
			LinuxCmd->CmdPara.TrimLeft();
			LinuxCmd->CmdPara.TrimRight();
		}
		else
			LinuxCmd->ConPara.Add(str.Mid(StartPos,Pos - StartPos));

		StartPos = str.Find(" ",Pos);
	}

	//����ʵ��
	EntityStru *pEntity,*pTempEntity;
	EntityObjStru *pEntityObj,*pTempEntityObj;
	int StartPos1,Pos1;  //����ȷ��ÿ��ʵ�������ʵ�����
	int StartPos2,Pos2;  //����ȷ��ʵ����Ķ���λ
	CString EntityStr;
	StartPos = str.Find("[");
	while(StartPos >= 0)
	{
		Pos = str.Find("]",StartPos);
		if(Pos < 0)
			return FALSE;

		pEntity = new EntityStru;
		pEntity->next = NULL;
		pEntity->EntityObj = NULL;
		pEntity->character = str.Mid(StartPos+1,Pos-StartPos-1);
		pEntity->character.TrimLeft();
		pEntity->character.TrimRight();
		if(pEntity->character.GetLength() <= 0)
		{
			delete pEntity;
			AfxMessageBox("[]�ڲ���Ϊ��!");
			return FALSE;
		}
		StartPos = Pos+1;
		StartPos1 = str.Find("<",StartPos);
		while(StartPos1 >= 0)
		{
			Pos1 = str.Find(">",StartPos1);
			if (Pos1 < 0)
			{
				delete pEntity;
				AfxMessageBox("û���ҵ�ƥ���>!");
				return FALSE;
			}
			EntityStr = str.Mid(StartPos1+1,Pos1-StartPos1-1);
			if(str.GetLength() <= 0)
			{
				delete pEntity;
				AfxMessageBox("<>�ڲ���Ϊ��!");
				return FALSE;
			}
			pEntityObj = new EntityObjStru;
			pEntityObj->next = NULL;
//			pEntityObj->EntityObj = NULL;
			StartPos2 = 0;
			while(StartPos2 >= 0)
			{
				Pos2 = EntityStr.Find(",",StartPos2);
				if (Pos2 < 0)
				{
	//				pEntityObj->EntityObj.Add(EntityStr);
					pEntityObj->EntityObj.Add(EntityStr.Right(EntityStr.GetLength() - StartPos2));
					StartPos2 = Pos2;
				}
				else
				{
					pEntityObj->EntityObj.Add(EntityStr.Mid(StartPos2,Pos2-StartPos2));
					StartPos2 = Pos2 + 1;
				}
			}
			if(pEntity->EntityObj == NULL)  //��һ��<...>
			{
				pEntity->EntityObj = pEntityObj;
				pTempEntityObj = pEntityObj;
			}
			else                            //�����<...>
			{
				pTempEntityObj->next = pEntityObj;
				pTempEntityObj = pEntityObj;
			}
			StartPos1 = str.Find("<",Pos1+1); //������һ��<...>,
			                                  //����������
			if(str.Find("[",Pos1+1) < 0)
				continue;
			if(StartPos1 > str.Find("[",Pos1+1))
				StartPos1 = -1;
		}  //������<...>
//		pTempEntityObj->next = NULL;
		if(LinuxCmd->Entity == NULL)
		{
			LinuxCmd->Entity = pEntity;        //��һ��[...]<...>...
			pTempEntity = pEntity;
		}
		else
		{
			pTempEntity->next = pEntity;       //�����[...]<...>...
			pTempEntity = pEntity;
		}
		StartPos = str.Find("[",Pos+1);        //������һ��[...]<...>..
		                                       //������
	} //ȫ������
//	pTempEntity->next = NULL;		

	return TRUE;
}

bool mmemcpy(char objbase[], int *offset, char *srcbase, int objmaxlen)
{
	int len = strlen(srcbase);
	if((*offset + len) >= objmaxlen)
		return false;
	memcpy(objbase+*offset, srcbase, len);
	*offset += len;
	return true;
}

bool pmemcpy(char objbase[], int *offset, char *srcbase, int objmaxlen)
{
	int len = strlen(srcbase);
	if((*offset + len + 2) >= objmaxlen)
		return false;
	*(objbase + *offset) = '[';
	memcpy(objbase + *offset +1, srcbase, len);
	*offset += len + 2;
	*(objbase + *offset - 1) = ']';
	return true;
}

bool omemcpy(char objbase[], int *offset, char *srcbase, int objmaxlen)
{
	int len = strlen(srcbase);
	if((*offset + len + 2) >= objmaxlen)
		return false;
	*(objbase + *offset) = '<';
	memcpy(objbase + *offset +1, srcbase, len);
	*offset += len + 2;
	*(objbase + *offset - 1) = '>';
	return true;
}

/***************************************************
	���ܣ���struct LinuxCmdStru�ṹ�����ݷ�����ַ�����
			��ÿ1024��Ϊ��λ���͸�SendDataToUsb()������
			Ȼ��ͨ��SendDataToUsb()����ͨ��usb�ڷ���
	��������Ҫ���͵���struct LinuxCmdStruΪ�ṹ������
	���أ���

	ע�ͣ������������λ���ķ������ֻ���ļ����Ʋ���
		  �����usb�������ݵĽӿڣ������Ѿ�������
****************************************************/
void SendToUsb(LinuxCmdStru1 *LinuxCmd, int Priority, int wait_flag, int timeout)
{
	EntityStru1 *pEntity,*pDelEntity;
	EntityObjStru1 *pEntityObj,*pDelEntityObj;
	int i;
	int maxlen = 1023;
	char tempBuf[1024];
	int ptr=1;
	bool FirstPackage = true;

	tempBuf[0] = '$';
	mmemcpy(tempBuf,&ptr,LinuxCmd->CmdName,maxlen);
	mmemcpy(tempBuf,&ptr," ",maxlen);
	mmemcpy(tempBuf,&ptr,LinuxCmd->CmdPara,maxlen);
	mmemcpy(tempBuf,&ptr," ",maxlen);
	for(i=0; i<LinuxCmd->ConParaNum; i++)
	{
		mmemcpy(tempBuf,&ptr,LinuxCmd->ConPara[i],maxlen);
		mmemcpy(tempBuf,&ptr," ",maxlen);
	}
	pEntity = LinuxCmd->Entity;
	while(pEntity != NULL)
	{
		//printf("\n[%s]\n",pEntity->character);
		if(!pmemcpy(tempBuf,&ptr,pEntity->character,maxlen))
		{
			if(FirstPackage)
				AddDataToXmtList(tempBuf,ptr,XMT_FILE,Priority,wait_flag,timeout);
			else
				AddDataToXmtList(tempBuf,ptr,XMT_FILE,PRIORITY_PART_CMD,wait_flag,timeout);
			ptr = 0;
			pmemcpy(tempBuf,&ptr,pEntity->character,maxlen);
		}
		pEntityObj = pEntity->EntityObj;
		while(pEntityObj != NULL)
		{
			//printf("<%s>\n",pEntityObj->EntityObj);
			if(!omemcpy(tempBuf,&ptr,pEntityObj->EntityObj,maxlen))
			{
				if(FirstPackage)
					AddDataToXmtList(tempBuf,ptr,XMT_FILE,Priority,wait_flag,timeout);
				else
					AddDataToXmtList(tempBuf,ptr,XMT_FILE,PRIORITY_PART_CMD,wait_flag,timeout);
				ptr = 0;
				omemcpy(tempBuf,&ptr,pEntityObj->EntityObj,maxlen);
			}
			pDelEntityObj = pEntityObj;
			pEntityObj = pEntityObj->next;
			delete pDelEntityObj;
		}
		pDelEntity = pEntity;
		pEntity = pEntity->next;
		delete pDelEntity;
	}
//	strcat(tempBuf,"123456\n");
	tempBuf[++ptr] = '\n';
	if(FirstPackage)
		AddDataToXmtList(tempBuf,ptr,XMT_FILE,Priority,wait_flag,timeout);
	else
		AddDataToXmtList(tempBuf,ptr,XMT_FILE,PRIORITY_PART_CMD,wait_flag,timeout);
	LinuxCmd->Entity = NULL;
}

void Esc_CString(CString *str)
{
	str->Replace("[","\\[");
	str->Replace("]","\\]");
	str->Replace("<","\\<");
	str->Replace(">","\\>");
	str->Replace("\\","\\\\");
	str->Replace("-","\\-");
	str->Replace(" ","\\ ");
}

int Esc_Chars(char *srcchrs, char objchrs[])
{
	int len = strlen(srcchrs);
	int i = 0;
	char *ptr = srcchrs;
	char *objptr = objchrs;

	while(i++ < len)
	{
		if( (*ptr == '[') || (*ptr == ']') || (*ptr == '<') ||
			(*ptr == '>') || (*ptr == '\\') || (*ptr == '-') )
		{
			*(objptr++) = '\\';
		}
		*(objptr++) = *(ptr++);
	}
	*objptr = 0;
	return strlen(objchrs);
}

void Esc_LinuxCmd(LinuxCmdStru *LinuxCmd)
{
	int i = 0, j;
	CString str;
	EntityStru *pEntity = LinuxCmd->Entity;
	EntityObjStru *pEntityObj;

	Esc_CString(&LinuxCmd->CmdPara);
	j = LinuxCmd->ConPara.GetSize();
	while(i < j)
	{
		str = LinuxCmd->ConPara.GetAt(0);
		Esc_CString(&str);
		LinuxCmd->ConPara.RemoveAt(0);
		LinuxCmd->ConPara.Add(str);
	}

	while(pEntity)
	{
		Esc_CString(&pEntity->character);
		pEntityObj = pEntity->EntityObj;
		i = 0;
		j = pEntityObj->EntityObj.GetSize();
		while(i < j)
		{
			str = pEntityObj->EntityObj.GetAt(i);
			Esc_CString(&str);
			pEntityObj = pEntityObj->next;
		}
		pEntity = pEntity->next;
	}
}

BOOL SendToUsb(LinuxCmdStru1 *LinuxCmd, int wait_flag,bool bNeedRequest)
{
	EntityStru1 *pEntity,*pDelEntity;
	EntityObjStru1 *pEntityObj,*pDelEntityObj;
	int i;
	int maxlen = 1023;
	char EscBuf[1024];
	char tempBuf[1024];
	int ptr=1;

	mWaitTimeOut.wait_flag = wait_flag;

	tempBuf[0] = '$';

	Esc_Chars(LinuxCmd->CmdName, EscBuf);
	mmemcpy(tempBuf,&ptr,EscBuf,maxlen);
	mmemcpy(tempBuf,&ptr," ",maxlen);
	Esc_Chars(LinuxCmd->CmdPara, EscBuf);
	mmemcpy(tempBuf,&ptr,EscBuf,maxlen);
	mmemcpy(tempBuf,&ptr," ",maxlen);
	for(i=0; i<LinuxCmd->ConParaNum; i++)
	{
		Esc_Chars(LinuxCmd->ConPara[i],EscBuf);
		mmemcpy(tempBuf,&ptr,EscBuf,maxlen);
		mmemcpy(tempBuf,&ptr," ",maxlen);
	}
	pEntity = LinuxCmd->Entity;
	while(pEntity != NULL)
	{
		//printf("\n[%s]\n",pEntity->character);
		Esc_Chars(pEntity->character, EscBuf);
		if(!pmemcpy(tempBuf,&ptr,EscBuf,maxlen))
		{
			PcUsbComm(theApp.m_uFtp, tempBuf, ptr, bNeedRequest);
			ptr = 0;
			Esc_Chars(pEntity->character,EscBuf);
			pmemcpy(tempBuf,&ptr,EscBuf,maxlen);
		}
		pEntityObj = pEntity->EntityObj;
		while(pEntityObj != NULL)
		{
			//printf("<%s>\n",pEntityObj->EntityObj);
			Esc_Chars(pEntityObj->EntityObj, EscBuf);
			if(!omemcpy(tempBuf,&ptr,EscBuf,maxlen))
			{
				PcUsbComm(theApp.m_uFtp, tempBuf, ptr, bNeedRequest);
				ptr = 0;
				Esc_Chars(pEntityObj->EntityObj,EscBuf);
				omemcpy(tempBuf,&ptr,EscBuf,maxlen);
			}
			pDelEntityObj = pEntityObj;
			pEntityObj = pEntityObj->next;
			delete pDelEntityObj;
		}
		pDelEntity = pEntity;
		pEntity = pEntity->next;
		delete pDelEntity;
	}
	LinuxCmd->Entity = NULL;
//	strcat(tempBuf,"123456\n");
	tempBuf[ptr++] = '\n';
	return PcUsbComm(theApp.m_uFtp, tempBuf, ptr, bNeedRequest);
}

BOOL SendToUsb(char *buf, int len, int wait_flag, bool bNeedRequest)
{
	mWaitTimeOut.wait_flag = wait_flag;
	return PcUsbComm(theApp.m_uFtp, buf, len, bNeedRequest);
}

bool WaitFileConfirm()
{
	int i = 150;
	while( (i-- > 0) && !WaitFileCon)
		Sleep(20);
	if( i <= 0)
		return false;

	return true;
}

void NewAEntity(EntityStru1 **pEntity, CString character)
{
	*pEntity = new EntityStru1;
	strcpy((*pEntity)->character,character.GetBuffer(character.GetLength()));
	character.ReleaseBuffer();
	(*pEntity)->EntityNum = 0;
	(*pEntity)->next = NULL;
	(*pEntity)->EntityObj = NULL;
}

void NewAEntityObj(EntityObjStru1 **pEntityObj)
{
	*pEntityObj = new EntityObjStru1;
	(*pEntityObj)->EntityObjNum = 0;
	strcpy((*pEntityObj)->EntityObj,"");
	(*pEntityObj)->next = NULL;
}

//
//�����ļ�
//
//����˵����
//
//	Ŀ��Ŀ¼��Ŀ���ļ�������λ��Ŀ¼��
//
const int DN_BLK_LEN = 3069;//4093;//4093��Ŀǰ֧�ֵ���󳤶ȣ�����֮�⻹��3���ֽڵ�type��len��Ϣ
//#define __DEBUG

UINT DownloadFile(LPVOID para)
{
	CStringArray *sarr = (CStringArray*)para;
	int i = 0;
	CString FileName;
	char filebuf[5060];//[1060];	//ʵ���õ�1024

	LinuxCmdStru1 LinuxCmd;
	EntityStru1 *pEntity,*pTailEntity;
	EntityObjStru1 *pEntityObj;
	CFile file;
	CString tempStr;
	CFileFind mFind;
	CString dstStr;
	CFileStatus fs;
	char formatStr[32];
	int blocknum;
TRACE("\nnow download files\n");	
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;//(CMainFrame*)(AfxGetApp()->GetMainWnd());
	int CopyPersent = 0;

	//CString ss;
	//AfxMessageBox("aaaaaaaaaaaaaaaaa");
	//ss.Format("%d",sarr->GetSize());
	//AfxMessageBox(ss);
	if(sarr->GetSize() < 3)
		return false;
	dstStr = sarr->GetAt(2)+sarr->GetAt(1);
	if(mFind.FindFile(dstStr))
	{
		mFind.FindNextFile();
		if( (mFind.IsDots()) || (mFind.IsDirectory()))
			return true;
	}
	mFind.Close();

	if(file.Open(dstStr,CFile::modeRead,NULL) < 0)
		return false;

	strcpy(LinuxCmd.CmdName, "put");
	strcpy(LinuxCmd.CmdPara, "");
	LinuxCmd.ConParaNum = 0;
	LinuxCmd.EntityNum = 0;
	LinuxCmd.Entity = NULL;

	//[Path]<path>
	NewAEntity(&pEntity,"path");
	LinuxCmd.Entity = pTailEntity = pEntity;
	NewAEntityObj(&pEntityObj);
	tempStr = sarr->GetAt(0);
//	if(tempStr.Right(1) != "/")
//		tempStr += "/";
	strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
	tempStr.ReleaseBuffer();
	pEntity->EntityObj = pEntityObj;

	//[File]<FileName>
	NewAEntity(&pEntity,"file");
	NewAEntityObj(&pEntityObj);
	tempStr = sarr->GetAt(1);
	strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
	tempStr.ReleaseBuffer();
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;
	pTailEntity = pEntity;

	//[Size]<size>
	NewAEntity(&pEntity,"size");
	NewAEntityObj(&pEntityObj);
	sprintf(pEntityObj->EntityObj, "%d", file.GetLength());
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;
	pTailEntity = pEntity;

	//[BlockNum]<blocknum>
	NewAEntity(&pEntity,"blocknum");
	NewAEntityObj(&pEntityObj);
	blocknum = (file.GetLength() + DN_BLK_LEN-1)/DN_BLK_LEN;
	sprintf(pEntityObj->EntityObj, "%d", blocknum);
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;
	pTailEntity = pEntity;
TRACE("block num is %d\n", blocknum);
	//[TimeOut]<timeout>
	NewAEntity(&pEntity,"timeout");
	NewAEntityObj(&pEntityObj);
	strcpy(pEntityObj->EntityObj,"3000");
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;

	pTailEntity = pEntity;

	//[ModifyTime]<modifytime>
	NewAEntity(&pEntity,"modifytime");
	NewAEntityObj(&pEntityObj);
	file.GetStatus(fs);
	sprintf(formatStr,	 "%d-%d-%d %d:%d:%d", 
						 fs.m_mtime.GetYear(), fs.m_mtime.GetMonth(), 
						 fs.m_mtime.GetDay(), fs.m_mtime.GetHour(),
						 fs.m_mtime.GetMinute(), fs.m_mtime.GetSecond() );
	strcpy(pEntityObj->EntityObj, formatStr);
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;

	if(!SendToUsb(&LinuxCmd, RSP_PUT, true))
	{
		AfxMessageBox("������ȷ���������豸!");
		//AfxMessageBox("������ȷ����USB�豸!");
		DownLoadDlg.SendMessage(WM_CLOSE);
		return FALSE;
	}

	int len;
	i = 0;
	bAlowDownLoad = true;

	while(((len = file.Read(filebuf,DN_BLK_LEN)) > 0) && bAlowDownLoad)
	{
		strcpy(LinuxCmd.CmdName, "putfile");
		strcpy(LinuxCmd.CmdPara, "");
		LinuxCmd.ConParaNum = 0;
		LinuxCmd.EntityNum = 0;
		LinuxCmd.Entity = NULL;

		//[FileName]<filename>
		NewAEntity(&pEntity,"file");
		LinuxCmd.Entity = pTailEntity = pEntity;
		NewAEntityObj(&pEntityObj);
		tempStr = sarr->GetAt(1);
		strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
		tempStr.ReleaseBuffer();
		pEntity->EntityObj = pEntityObj;

		//[BlockNo]<blockno>
		NewAEntity(&pEntity,"blockno");
		NewAEntityObj(&pEntityObj);
		sprintf(pEntityObj->EntityObj,"%d",i++);
		pEntity->EntityObj = pEntityObj;
		pTailEntity->next = pEntity;
		pTailEntity = pEntity;

		//[Size]<size>
		NewAEntity(&pEntity, "blocksize");
		NewAEntityObj(&pEntityObj);
		sprintf(pEntityObj->EntityObj,"%d",len);
		pEntity->EntityObj = pEntityObj;
		pTailEntity->next = pEntity;
		pTailEntity = pEntity;
		if(!SendToUsb(&LinuxCmd, RSP_PUT_FILE, false))
			return false;

		if(!SendToUsb(filebuf, len, RSP_FILE_DATA, true))
		{
			return false;
		}

		CopyPersent = (i * 100) / blocknum;
		
		if(bAlowDownLoad)
			DownLoadDlg.SendMessage(DOWNLOAD_PROGRESS, CopyPersent, NULL);
	}
	file.Close();

	return TRUE;
}

void Ini_UpFile(UpFileStru *pUpFile)
{
	pUpFile->FileName = "";
	pUpFile->FileSize = 0;
	pUpFile->BlockNum = 0;
	pUpFile->CurBlock = 0;
	pUpFile->TimeOut = 3000;
	pUpFile->hfile.m_hFile = 0;
}

//
//�������ؽ���
//
UINT ExeDownloadFile(LPVOID para)
{
	UINT rtnValue;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	rtnValue = DownloadFile(para);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return rtnValue;
}

//
//�����ļ�
//
//	������
//		Ŀ��Ŀ¼��Ŀ���ļ�������λ��Ŀ¼��
//
UINT UploadFile(LPVOID para)
{
	CStringArray *sarr = (CStringArray*)para;
	CString FileName;
	int CopyPersent = 0;
	CUpLoadDlg tempDlg;

	LinuxCmdStru1 LinuxCmd;
	EntityStru1 *pEntity,*pTailEntity;
	EntityObjStru1 *pEntityObj;

	if(sarr->GetSize() < 3)
		return false;

	strcpy(LinuxCmd.CmdName, "get");
	strcpy(LinuxCmd.CmdPara, "");
	LinuxCmd.ConParaNum = 0;
	LinuxCmd.EntityNum = 0;
	LinuxCmd.Entity = NULL;
	CFile file;
	CString tempStr;

	//[Path]<path>
	NewAEntity(&pEntity, "path");
	LinuxCmd.Entity = pTailEntity = pEntity;
	NewAEntityObj(&pEntityObj);
	pEntity->EntityObj = pEntityObj;
	tempStr = sarr->GetAt(2);
	strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
	tempStr.ReleaseBuffer();

	//[File]<filename>
	NewAEntity(&pEntity, "file");
	NewAEntityObj(&pEntityObj);
	tempStr = sarr->GetAt(1);
	strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
	tempStr.ReleaseBuffer();
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;
	pTailEntity = pEntity;
	Ini_UpFile(&mUpFile);
	mUpFile.PCPath = sarr->GetAt(0);
	mUpFile.FileName = sarr->GetAt(1);

	//[timeout]<timeout>
	NewAEntity(&pEntity, "timeout");
	NewAEntityObj(&pEntityObj);
	strcpy(pEntityObj->EntityObj, "3000");
	pEntity->EntityObj = pEntityObj;
	pTailEntity->next = pEntity;
	pTailEntity = pEntity;
//	SendToUsb(&LinuxCmd, PRIORITY_FILE, RSP_GET, 3000);
	WaitFileCon = false;
	SendToUsb(&LinuxCmd, RSP_GET, true);
	if(!WaitFileConfirm())
	{
		AfxMessageBox("δ�ҵ���������ļ�");
//		AfxMessageBox("������ȷ����USB�豸!");
		UpLoadDlg.PostMessage(WM_CLOSE, NULL, NULL);
		return FALSE;
	}
	
	bAlowUpLoad = true;
//	pFrame->SendMessage(FILE_COPY_PROGRESS, CopyPersent,(LPARAM)"file");
	while((mUpFile.CurBlock < mUpFile.BlockNum) && bAlowUpLoad)
	{
		strcpy(LinuxCmd.CmdName, "getfile");
		strcpy(LinuxCmd.CmdPara, "");
		LinuxCmd.ConParaNum = 0;
		LinuxCmd.EntityNum = 0;
		LinuxCmd.Entity = NULL;

		//[File]<file>
		NewAEntity(&pEntity, "file");
		LinuxCmd.Entity = pTailEntity = pEntity;
		NewAEntityObj(&pEntityObj);
		pEntity->EntityObj = pEntityObj;
		tempStr = sarr->GetAt(1);
		strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
		tempStr.ReleaseBuffer();

		//[BlockNo]<blockno>
		NewAEntity(&pEntity, "blockno");
		NewAEntityObj(&pEntityObj);
		tempStr.Format("%d",mUpFile.CurBlock);
		strcpy(pEntityObj->EntityObj, tempStr.GetBuffer(tempStr.GetLength()));
		tempStr.ReleaseBuffer();
		pEntity->EntityObj = pEntityObj;
		pTailEntity->next = pEntity;
		pTailEntity = pEntity;
		WaitFileCon = false;
		if(!SendToUsb(&LinuxCmd, RSP_WAIT_FILE_DATA, true))
		{
			mUpFile.hfile.Close();
			return FALSE;
		}

		CopyPersent = ((mUpFile.CurBlock+1) * 100) / mUpFile.BlockNum;
		UpLoadDlg.SendMessage(UPLOAD_PROGRESS, CopyPersent, NULL);
		mUpFile.CurBlock++;
	}
	mUpFile.hfile.Close();
	return TRUE;
}

//
//�������ؽ���
//
UINT ExeUploadFile(LPVOID para)
{
	UINT rtnValue;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	rtnValue = UploadFile(para);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return rtnValue;
}
