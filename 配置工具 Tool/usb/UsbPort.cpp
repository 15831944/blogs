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
//UsbXmtStru* XmtFileMsg = NULL;  //文件通讯缓冲头指针，仅用在传送连续
								//的文件时，其他时候都用数据缓冲
//UsbXmtStru* XmtFileTail= NULL;  //文件通讯缓冲尾指针
UsbXmtStru* XmtDataMsg = NULL;  //采集数据缓冲头指针
UsbXmtStru* XmtDataTail= NULL;	//采集数据缓冲尾指针
bool bSystemIsRuning = false;   //系统运行状态
int DataCtrlType = STREAMCTRL;  //数据控制方式，现在用流控制方式
int WaitConfirmType = 0;        //标志等待确认的命令

int WaitCmdType = WAIT_CMD;     //等待的命令类型，是标准命令还是文件块数据
int WaitFileLen;                //希望收到的文件的块的长度

#define MAX_RCV_LEN 4096
unsigned char RcvBuf[MAX_RCV_LEN];     //暂时先用4096，以后根据实际传输块大小再修改
int RcvGet = 0,RcvPut = 0;        //收缓冲区收发指针
unsigned char* RcvPtr;			//接受指针，用来标记当前接收到RcvBuf中的偏移量
TimeOutStru mWaitTimeOut;

UpFileStru mUpFile;
//extern UpSRAMStru mSRAMFile;
bool bAlowUpLoad, bAlowDownLoad;
extern BOOL PcUsbComm(HUFTP hUFTP, TCHAR *msg, DWORD len,bool bNeedRequest);
extern BOOL Uftp_GetSimple(HUFTP hUFTP);
extern bool WaitSramFileCon;
/******************************************************
	注：下面没有具体说明应用范围的函数就是可以
		用在所有地方的
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
	应用范围：流控制和块控制的应用
	功能：获得usb口缓存的字节数
	参数：无
	返回：I、 流控制方式：usb口缓存的字节数
		  II、块控制方式：usb口中缓存的块数
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
	应用范围：流控制的应用
	功能：从usb口缓存中读出指定数目的字节
	参数：返回数据缓冲区起址，希望从usb缓存区中读出的byte数
	返回：如果usb缓存区有希望读取的数量的bytes，返回希望数量
	      值，否则返回实际读出的数量
********************************************************/
int ReadFromUsb(unsigned char *RcvMsg, int Len)
{
	return Len;
}

/*********************************************************
	应用范围：流控制和块控制的应用
	功能：I、流控制方式，读出usb口缓存中所有的字节
		  II、块控制方式，读出usb口缓存中一块数据
	参数：返回数据缓冲区起址
	返回：实际读出的数量
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
	功能：从usb口数据缓冲区里面读一包数据出来，如果等待的是普通命令，
		则根据'$'和'\n'来判断一包数据，否则根据文件的块长度来确定
		一包数据。
	参数：返回数据缓冲区起址
	返回：实际读到的字节数
	注意：如果发现usb口缓冲数据缓冲区里的数据不到1包的话，则返回-1；
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
	功能：向usb口发送指定长度的字节
	参数：I - 发送缓冲区起址
	      II - 发送长度
	返回：实际发送字节数
	注意：发送的数据都是以字节串的方式发送的
**********************************************************/
int WriteToUsb(char *msg,int len)
{
	return len;
}

/*********************************************************
	功能：向usb口发送字符串
	参数：发送的字符串
	返回：实际发送字节数
	注意：发送的数据都是以字节串的方式发送的
**********************************************************/
int WriteToUsb(CString str)
{
	return 0;
}

/*********************************************************
	功能：usb口通讯主线程，所有有关usb口的通讯都是由它来
		  实现的，系统初始化后即把它调起，知道系统结束，他
		  才被释放掉。
		  主要支持功能：
			1、采集mk中的模拟量，遥信量，累加量
			2、对mk时钟的设定
			3、对mk方式字的下载和上载
			4、对mk和pc进行文件的相互访问
			5、复位系统
			6、查看和杀死系统进程
			7、设置mk网络参数
	注意：MainThread只管收,不管发,他的发是通过调用SendDataToUsb
		函数来实现的,至于发什么,MainThread并不知道
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
			AfxMessageBox("命令处理时发现错误，退出主线程");
			break;
		}
		Sleep(200);
	}
	return TRUE;
}

/**********************************************************
	功能：确定当前要向usb口中发的数据
		  为主进程提供当前要发的数据，主进程所要向usb口发的数
		  据全部从这儿发出去
	参数：无
	注意：这里要发的数据是从file和data两个链表所决定的。
		file链表优先级高于data
		两者的数据来源是根据MainThread收到数据后，发到相应的处
		理函数，进行处理后，根据需要发给这2个链表的
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
				AfxMessageBox("发送失败，请重新发送");
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
		AfxMessageBox("等待超时,请重新召唤!");
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
		//按优先级高在前的顺序把新节点插入到发送链表中
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
		AfxMessageBox("你输入了错误的发送数据的类型，请确认");
		break;
	}
}

bool WaitFileData(unsigned char *msg, int len)
{
	//暂不考虑写文件失败
	if(!mUpFile.hfile.m_hFile)
		return false;
	mUpFile.hfile.Write(msg,len);
	WaitFileCon = true;

	return true;
}

//
//释放掉LinuxCmdStru结构体
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
	功能：处理命令
	参数：I、 命令起址
		  II、命令长度
	返回：成功返回TRUE,失败返回FALSE
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
			AfxMessageBox("翻译为Linux命令时出现错误!");
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
	AfxMessageBox("系统收到复位命令，将在5秒内复位");
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
	row_col = (row_col & 0xff00) | col;	//1为列号

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
	应用范围：应用于除文件传输外的其他所有协议格式的翻译
	功能：把给出的字符串翻译成标准的linux命令结构
	参数：I、  字符串起址
		  II、 长度
		  III、返回linux结构的指针
	返回：如果是个错误的命令格式返回FALSE，正确的返回TRUE
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
	//初始化LinuxCmd
	LinuxCmd->Entity = NULL;

	//查找命令名
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

	//查找命令参数和普通参数
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

	//查找实体
	EntityStru *pEntity,*pTempEntity;
	EntityObjStru *pEntityObj,*pTempEntityObj;
	int StartPos1,Pos1;  //用来确定每个实体里面的实体对象
	int StartPos2,Pos2;  //用来确定实体里的对象单位
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
			AfxMessageBox("[]内不能为空!");
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
				AfxMessageBox("没有找到匹配的>!");
				return FALSE;
			}
			EntityStr = str.Mid(StartPos1+1,Pos1-StartPos1-1);
			if(str.GetLength() <= 0)
			{
				delete pEntity;
				AfxMessageBox("<>内不能为空!");
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
			if(pEntity->EntityObj == NULL)  //第一个<...>
			{
				pEntity->EntityObj = pEntityObj;
				pTempEntityObj = pEntityObj;
			}
			else                            //后面的<...>
			{
				pTempEntityObj->next = pEntityObj;
				pTempEntityObj = pEntityObj;
			}
			StartPos1 = str.Find("<",Pos1+1); //找完了一个<...>,
			                                  //继续往下找
			if(str.Find("[",Pos1+1) < 0)
				continue;
			if(StartPos1 > str.Find("[",Pos1+1))
				StartPos1 = -1;
		}  //找完了<...>
//		pTempEntityObj->next = NULL;
		if(LinuxCmd->Entity == NULL)
		{
			LinuxCmd->Entity = pEntity;        //第一个[...]<...>...
			pTempEntity = pEntity;
		}
		else
		{
			pTempEntity->next = pEntity;       //后面的[...]<...>...
			pTempEntity = pEntity;
		}
		StartPos = str.Find("[",Pos+1);        //找完了一个[...]<...>..
		                                       //继续找
	} //全找完了
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
	功能：把struct LinuxCmdStru结构的数据翻译成字符串，
			以每1024个为单位发送给SendDataToUsb()函数，
			然后通过SendDataToUsb()函数通过usb口发出
	参数：需要发送的以struct LinuxCmdStru为结构的数据
	返回：无

	注释：这个函数在上位机的服务对象只有文件控制部分
		  最初的usb发送数据的接口，现在已经不用了
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
//下载文件
//
//参数说明：
//
//	目标目录，目标文件名，上位机目录名
//
const int DN_BLK_LEN = 3069;//4093;//4093是目前支持的最大长度，除此之外还有3个字节的type和len信息
//#define __DEBUG

UINT DownloadFile(LPVOID para)
{
	CStringArray *sarr = (CStringArray*)para;
	int i = 0;
	CString FileName;
	char filebuf[5060];//[1060];	//实际用到1024

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
		AfxMessageBox("请先正确连接网络设备!");
		//AfxMessageBox("请先正确连接USB设备!");
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
//调起下载进程
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
//上载文件
//
//	参数：
//		目标目录，目标文件名，下位机目录名
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
		AfxMessageBox("未找到相关配置文件");
//		AfxMessageBox("请先正确连接USB设备!");
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
//调起上载进程
//
UINT ExeUploadFile(LPVOID para)
{
	UINT rtnValue;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	rtnValue = UploadFile(para);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return rtnValue;
}
