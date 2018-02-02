// ReadPzkIni.cpp: implementation of the CReadPzkIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "MyString.h"
#include "MyFun.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//数组记录每种故障有多少 
//行：故障类型 列：多少个数
int NumberMax[7][1]={0};


/********************** 绍兴集中式 2015.7.15 lizhen *********/
int SXJZS_FACT_LINE;//绍兴集中式线路数 实际最大线路数


int SXJZS_Select[SWITCH_KIND][SELECT];//绍兴集中式 读取prot_select里面的数据到数组
int SXJZS_FACT_SELECT[SELECT];//实际的值大小

//Prot_Select0=0,1,2,3; 
//Prot_Select1=4;

//其中SXJZS_Select[0][0]存放0  [0][1]存放1 [0][2]存放2 [0][3]存放3
// SXJZS_Select[1][0]存放4

//SXJZS_FACT_SELECT[0]存放3 因为第一个有3+1=4个有效值
//SXJZS_FACT_SELECT[1]存放0 因为第一个有0+1=1个有效值

int SwitchTypeNum;//开关类型多少个 根据Prot_Select后面的数字进行来判断，方便保存时的计数

/******************看门狗******2015.7.16 lizhen**************/


int KMG_Select[KMG_SWITCH_KIND][KMG_SELECT];//看门狗 读取prot_select里面的数据到数组
int KMG_FACT_SELECT[KMG_SELECT];//实际的值大小
int KMG_SwitchTypeNum;//开关类型多少个 根据Prot_Select后面的数字进行来判断，方便保存时的计数


int hang=0;//文本有多少行
CString Note[1000];//存放注释

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool flt_3I0=false;
bool flt1_Current=false;
bool flt2_Current=false;
bool byd_ZeroU=false;
bool byd_ZeroI=false;
bool byd_Voltage=false;
bool byd_Current=false;


int step1=0;
int step2=0;
int step3=0;
int step4=0;
int step5=0;
int step6=0;
int step7=0;
CReadPzkIni::CReadPzkIni()
{
	IniFileOpened = false;
	EverModified = false;
}

CReadPzkIni::~CReadPzkIni()
{
	if(IniFileOpened)
		ReleaseBuf();
}

bool CReadPzkIni::OpenFile(CString FileName)
{
	int i;
	if (IniFileOpened)
		if(EverModified)
		{
			i = AfxMessageBox("文件已被修改，确定存盘吗？",MB_YESNOCANCEL);

			if(i == IDYES)
			{
				if (!SaveToIni())
					msgbox("保存失败，请重新保存");
				else
					mStdioFile.Close();
			}
			else if(i == IDCANCEL)
				return true;
		}

	CFileFind findfile;
	if(!findfile.FindFile(FileName))
	{
		AfxMessageBox("不存在此文件!");
		return false;
	}
	if (FileName == "")
		return false;
	IniFileName = FileName;
	return ReadFromIntFile();
}

bool CReadPzkIni::OpenTempFile(CString FileName)
{
	int i;
	if (IniFileOpened)
		if(EverModified)
		{
			i = AfxMessageBox("文件已被修改，确定存盘吗？",MB_YESNOCANCEL);

			if(i == IDYES)
			{
				if (!SaveToIni())
					msgbox("保存失败，请重新保存");
				else
					mStdioFile.Close();
			}
			else if(i == IDCANCEL)
				return true;
		}
	IniFileName = FileName;
	ReadFromIntFile();
	IniFileName = "";
	EverModified = true;
	return true;
}

bool CReadPzkIni::ReadFromIntFile()
{
	CString LineString;
	DWORD FileLen;

	int posi,posi1;
	CString name;

	CString SectionName;
	CString KeyName;
	CString KeyStr;
	int SectionNo=0;
//	int KeyNum = 0;
	CString KeyNote;//注释
	int CurNum=0;  //表示所操作对象当前的位置

	if(!mStdioFile.Open(IniFileName,CFile::modeRead,NULL))
		return false;
	FileLen = mStdioFile.GetLength();

	IniFileOpened = true;
//	int i = 0;

	hang=0;//文本行数
	while(mStdioFile.ReadLineWithout2SideSpace(&LineString))
	{
		hang++;
		if(LineString.IsEmpty()) //" "
		{
			continue;
		}
		else if(LineString.Left(1) == Remark) //"#";
		{
			continue;
		}
		else if(LineString.Left(1) == Demo) //"%"
		{
			continue;
		}
		else if(LineString.Left(1) == BeginBorder)//LineString.left right mid分别怎么用？
		{
			posi = LineString.Find(EndBorder);
			if(posi<0)
				return false;
			SectionName = LineString.Mid(1,posi-1);
			SectionName.TrimLeft();
			SectionName.TrimRight();
			//msgbox(SectionName);
			SectionNo = GetSecNo(SectionName,&CurNum);
		
			posi = LineString.Find("#");
			if(posi > 0)
			{
				KeyNote = LineString.Right(LineString.GetLength()-posi-1);//为啥再减一
				KeyNote.TrimLeft();
				KeyNote.TrimRight();//此时keynote里面存放的是注释的数据
				if(hang<1000)
					Note[hang]=KeyNote;
				//AfxMessageBox(KeyNote);
			}
			
		}
		else
		{
			posi = LineString.Find("=");
			if(posi < 0)
				return false;
			KeyName = LineString.Left(posi);
			KeyName.TrimLeft();
			KeyName.TrimRight();

			posi1 = LineString.Find(";");
			KeyStr = LineString.Mid(posi+1,posi1-posi-1);
			KeyStr.TrimLeft();KeyStr.TrimRight();

			posi = LineString.Find("#");
			if(posi > 0)
			{
				KeyNote = LineString.Right(LineString.GetLength()-posi-1);
				KeyNote.TrimLeft();
				KeyNote.TrimRight();//此时keynote里面存放的是注释的数据
				if(hang<1000)
					Note[hang]=KeyNote;
			//		CString cs;
	//cs.Format("%d",hang);
//	AfxMessageBox(cs);
			}

	//		AfxMessageBox(KeyStr);
/*			switch(SectionNo)
			{
			case Sec_Info:
				Get_Infomation(KeyName, KeyStr);
				break;
			case Sec_300_Cfg:
				Get300Cfg(KeyName, KeyStr, CurNum);
				break;
			case Set_300_Pro:
				Get300Pro(KeyName, KeyStr, CurNum);
				break;
			default:
				break;
			}*/
			switch(SectionNo)//ReadFromIntFile干嘛用的？根据sectionno把sectionname下边的内容读上来
			{
			case Sec_FileName://100
				GetFileName(KeyName, KeyStr);
				break;
			case Sec_Info://1
				GetSecInfo(KeyName, KeyStr);
				break;
			case Sec_Line://2
				GetSecLine(KeyName, KeyStr, CurNum);
				break;
			case Sec_Config://3
				GetConfig(KeyName, KeyStr);
				break;
			case Sec_DelayTime://4
				GetDelayTime(KeyName, KeyStr);
				break;
			case Sec_LV_Prot://5
				GetLVProt(KeyName, KeyStr);
				break;
			case Sec_Auto_Bzt://8
				GetAutoBzt(KeyName, KeyStr);
				break;
			case Sec_Ctrl_time://9
				GetCtrl(KeyName, KeyStr);
				break;
			case Sec_Bzt://6
				GetBzt(KeyName, KeyStr);
				break;
			case Sec_Unit://7
				GetUnit(KeyName, KeyStr, CurNum);
				break;

			case Zj_Sec_Config://10
				GetZjConfig(KeyName, KeyStr);
				break;
			case Zj_Sec_DelayTime://11
				GetZjDelayTime(KeyName, KeyStr);
				break;
			case Zj_Sec_Unit://12
				GetZjUnit(KeyName, KeyStr, CurNum);
				break;
			case Zj_Sec_Bzt://13
				GetZjBzt(KeyName, KeyStr);
				break;

			case Sec_enable://15
				GetPlcenable(KeyName, KeyStr);
				break;
			case Sec_value://16
				GetLimitvalue(KeyName, KeyStr);
				break;
			case Sec_type://17
				GetModetype(KeyName, KeyStr);
				break;
			case Sec_time://18
				GetPlctime(KeyName, KeyStr);
				break;
			case Sec_jxchz://19
				GetJxchz(KeyName, KeyStr);
				break;
			case Sec_cxchz://20
				GetCxchz(KeyName, KeyStr);
				break;
			case Sec_ControlW://21
				GetControlW(KeyName,KeyStr);
				break;
			case Sec_prot_general://22
				Getprot_general(KeyName,KeyStr);
				break;
			case 23://绍兴集中式 prot_select
				Getprot_select(KeyName,KeyStr);
				break;
			default:
				break;
			}
		}//end switch
	}//end while
	mStdioFile.Close();
//	CString cs;
//	cs.Format("%d",hang);
//	AfxMessageBox(cs);
	return true;
}

bool CReadPzkIni::WriteToIni()
{
//	DWORD Position;
	CString strr;
	CString LineString;
	CString LineString_next;
	DWORD FileLen;

	int posi,posi1;
	CString name;

	CString SectionName;
	CString KeyName;
	CString KeyStr;
	int SectionNo=0;

	int CurNum=0;  //表示所操作对象当前的位置

//	Position = mStdioFile.GetPosition();

	if(!mStdioFile_tmp.Open("mzkprot_new.ini",CFile::modeWrite|CFile::modeCreate,NULL))
		return false;
	mStdioFile_tmp.SeekToBegin();
	
	if(!mStdioFile.Open(IniFileName,CFile::modeReadWrite,NULL))
		return false;

	FileLen = mStdioFile.GetLength();

	IniFileOpened = true;
    mStdioFile.SeekToBegin();
	while(mStdioFile.ReadLineWithout2SideSpace(&LineString))
	{
		
	//	mStdioFile.ReadLineWithout2SideSpace(&LineString_next);
	//	Position = mStdioFile.GetPosition();
	//	strr.Format("%d %ld",LineString.GetLength(),mStdioFile.GetPosition());
	//	AfxMessageBox("read"+LineString);
	//		AfxMessageBox("read_next"+LineString_next);
		if(LineString.IsEmpty()) //" "
		{
			mStdioFile_tmp.WriteString("\n");
			continue;
		}
		else if(LineString.Left(1) == Remark) //"#";
		{
			mStdioFile_tmp.WriteString(LineString+"\n");
			continue;
		}
		else if(LineString.Left(1) == Demo) //"%"
		{
			mStdioFile_tmp.WriteString(LineString+"\n");
			continue;
		}
		else if(LineString.Left(1) == BeginBorder)
		{
			
			posi = LineString.Find(EndBorder);
			if(posi<0)
				return false;
			SectionName = LineString.Mid(1,posi-1);
			SectionName.TrimLeft();
			SectionName.TrimRight();
			//msgbox(SectionName);
			//mStdioFile_tmp.WriteString("["+SectionName+"]"+"\n");

			SectionNo = GetSecNo(SectionName,&CurNum);
			Write_to(LineString,SectionName);
		}
		else
		{
			posi = LineString.Find("=");
			if(posi < 0)
				return false;
			KeyName = LineString.Left(posi);
			KeyName.TrimLeft();
			KeyName.TrimRight();

			posi1 = LineString.Find(";");
			KeyStr = LineString.Mid(posi+1,posi1-posi-1);
			KeyStr.TrimLeft();KeyStr.TrimRight();
			
			
			switch(SectionNo)
			{	

			case Sec_FileName://100
				mStdioFile_tmp.WriteString("FileName=mzkprot.ini;\n");
				break;
			case Sec_Info://1
				SetSecInfo(KeyName, &KeyStr);
				Write_to(LineString,KeyName, KeyStr);
				break;
			case Sec_Line://2
				SetSecLine(KeyName, &KeyStr, CurNum);
				Write_to(LineString,KeyName, KeyStr);
				break;
			case Sec_ControlW://21
				SetControlW(KeyName,&KeyStr);
				Write_to(LineString,KeyName, KeyStr);
				
				break;
			case Sec_prot_general://22
				Setprot_general(KeyName,&KeyStr);
				Write_to(LineString,KeyName, KeyStr);
				break;
			}
		}//end switch
	}//end while
	//AfxMessageBox("写入成功");
	mStdioFile.Close();

	return true;
}


bool CReadPzkIni::Write_to(CString LineString, CString SectionName)
{
	int posi;
	bool note = false;
	CString KeyNote;
	posi = LineString.Find("#");
	if(posi > 0)
	{
		KeyNote = LineString.Right(LineString.GetLength()-posi-1);
		KeyNote.TrimLeft();
		KeyNote.TrimRight();
	//	AfxMessageBox("keyNote"+KeyNote);
		note = true;
	}
	if(note == false)
		mStdioFile_tmp.WriteString("["+SectionName+"]"+"\n");
	else
		mStdioFile_tmp.WriteString("["+SectionName+"] #"+KeyNote+"\n");
	return true;
}




bool CReadPzkIni::Write_to(CString LineString, CString KeyName, CString KeyStr)
{
//	DWORD current_position;
	int key_len;
	int posi;
	bool note = false;
	CString KeyNote;
	posi = LineString.Find("#");
	if(posi > 0)
	{
		KeyNote = LineString.Right(LineString.GetLength()-posi-1);
		KeyNote.TrimLeft();
		KeyNote.TrimRight();
	//	AfxMessageBox("keyNote"+KeyNote);
		note = true;
	}

//	CString str;
//	DWORD Position;
//	Position = mStdioFile.GetPosition();
//	current_position = Position - LineString.GetLength()-2;
//	mStdioFile.Seek(current_position,CFile::begin);


//	AfxMessageBox("write"+KeyName);
//	AfxMessageBox("write"+KeyStr);
//	AfxMessageBox(KeyNote);
//	if(note == false)
//		mStdioFile.WriteString(KeyName+"="+KeyStr+";"+"\n");
//	else
//		mStdioFile.WriteString(KeyName+"="+KeyStr+";"+"#"+KeyNote+"\n");

//	key_len=KeyName.GetLength()+KeyStr.GetLength();
//	mStdioFile.Seek(current_position+key_len+4,CFile::begin);
	// 4= "=" ";" \n \r

	if(note == false)
		mStdioFile_tmp.WriteString(KeyName+"="+KeyStr+";"+"\n");
	else
		mStdioFile_tmp.WriteString(KeyName+"="+KeyStr+";"+"#"+KeyNote+"\n");

	//key_len=KeyName.GetLength()+KeyStr.GetLength();
	//mStdioFile_tmp.Seek(key_len+4,CFile::current);
	return true;
}

bool CReadPzkIni::SetSecInfo(CString KeyName,CString *KeyStr)
{
	if(!IniFileOpened)
		return false;
	if(KeyName == "Version")
		*KeyStr=ProtFile.Cfg.Version;
	else if(KeyName == "Date")
		*KeyStr=ProtFile.Cfg.CreateTime;

	
	else if(KeyName == "Byd_SOEEnble")
		*KeyStr=ProtFile.Cfg.Byd_SOEEnble;
	else if(KeyName == "Flt_YXEnble")
		*KeyStr=ProtFile.Cfg.Flt_YXEnble;
	else if(KeyName == "Flt_RepEnble")
		*KeyStr=ProtFile.Cfg.Flt_RepEnble;
	
	
	
	else if(KeyName == "Prot_YXEnable")
		(*KeyStr).Format("%d",ProtFile.Cfg.Prot_YXEnable);
	else if(KeyName == "Prot_MsgEnable")
		(*KeyStr).Format("%d",ProtFile.Cfg.Prot_MsgEnable);
	else if(KeyName == "ProtLineNum")
		(*KeyStr).Format("%d",ProtFile.Cfg.LineNum);
	else if(KeyName == "ProtNumPerLine")
		(*KeyStr).Format("%d",ProtFile.Cfg.PNPL);
	else if(KeyName == "Switch_Remote")
		(*KeyStr).Format("%d",ProtFile.Cfg.Switch_Remote);
	else if(KeyName == "FixActTime")
		(*KeyStr).Format("%d",ProtFile.Cfg.FixActTime);
	else if(KeyName == "Switch_Local")
		(*KeyStr).Format("%d",ProtFile.Cfg.Switch_Local);
	else if(KeyName == "V_ConnectMode")
		(*KeyStr).Format("%d",ProtFile.Cfg.V_ConnectMode);
	
	return true;

}

bool CReadPzkIni::SetSecLine(CString KeyName, CString *KeyStr, int CurNum)
{
	int ProtNo;
	CString str;

	if(!IniFileOpened)
		return false;

	str.Format("prot_Line%d",CurNum);
	
	//protect function
	if(KeyName.Find("Line_Switch") >= 0)
	{
		(*KeyStr).Format("%d",ProtFile.Line[CurNum].LineCfg.Line_Switch);

	}
	if(KeyName.Find("prot_Type") >=0)
	{
	
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Type")));
		if(ProtNo >=_Max_Prot_Line)
			return false;
		(*KeyStr).Format("%d",ProtFile.Line[CurNum].ProtItem[ProtNo].Type);
	}
	else if(KeyName.Find("prot_Name") >= 0)
	{
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Name")));
			if(ProtNo >=_Max_Prot_Line)
			return false;
		*KeyStr = ProtFile.Line[CurNum].ProtItem[ProtNo].Name ;
	}
	else if(KeyName.Find("prot_Enable") >=0)
	{
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Enable")));
		if(ProtNo >=_Max_Prot_Line)
			return false;
			(*KeyStr).Format("%d",ProtFile.Line[CurNum].ProtItem[ProtNo].Enable);
	}
	else if(KeyName.Find("prot_Value") >=0)
	{
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Value")));
		if(ProtNo >=_Max_Prot_Line)
			return false;
		(*KeyStr).Format("%.2lf",ProtFile.Line[CurNum].ProtItem[ProtNo].Value);
	}
	else if(KeyName.Find("prot_Time") >=0)
	{
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Time")));
		if(ProtNo >=_Max_Prot_Line)
			return false;
		(*KeyStr).Format("%.2lf",ProtFile.Line[CurNum].ProtItem[ProtNo].Time);
	}
	else if(KeyName.Find("prot_Unit") >=0)
	{
		ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Unit")));
		if(ProtNo >=_Max_Prot_Line)
			return false;
		*KeyStr = ProtFile.Line[CurNum].ProtItem[ProtNo].Unit;
	}

	return true;
}


bool CReadPzkIni::SetControlW(CString KeyName, CString *KeyStr) 
{
	int KeyNo;
	CString keysign;
	keysign = "ControlByte";
	if(!IniFileOpened)
		return false;
	if(KeyName == "ControlW_Len")
		(*KeyStr).Format("%d",ProtFile.Cfg.ControlW_Len);
	else if(KeyName.Find("ControlByte") >= 0)
	{
		KeyNo = myatoi(KeyName.Right(KeyName.GetLength() - keysign.GetLength()));
		(*KeyStr).Format("%d",ProtFile.Cfg.ControlWByte[KeyNo]);
	}
	else
		return false;
	
	return true;
}


bool CReadPzkIni::Setprot_general(CString KeyName, CString *KeyStr)
{
	if(!IniFileOpened)
		return false;
	
	if(KeyName == "ProtLineNum")
		(*KeyStr).Format("%d",ProtFile.Cfg.LineNum);
	else if(KeyName == "ProtNumPerLine")
		(*KeyStr).Format("%d",ProtFile.Cfg.PNPL);
	else if(KeyName == "Switch_Remote")
		(*KeyStr).Format("%d",ProtFile.Cfg.Switch_Remote);
	else if(KeyName == "FixActTime")
		(*KeyStr).Format("%d",ProtFile.Cfg.FixActTime);
	else if(KeyName == "Switch_Local")
		(*KeyStr).Format("%d",ProtFile.Cfg.Switch_Local);
	else if(KeyName == "V_ConnectMode")
		(*KeyStr).Format("%d",ProtFile.Cfg.V_ConnectMode);
	else
		return false;
	
	return true;
}


int CReadPzkIni::GetSecNo(CString SectionName,int *CurNum)
{
	//	mStdioFile.Seek( 0, CFile::current);
	int SectionNo = 0;
	if(SectionName == FileName)
		SectionNo = Sec_FileName;//=100
	else
	{
		if(FileType == PROTECT_FILE)
		{
			if(SectionName == InfoSign)
				SectionNo = Sec_Info;
			if(SectionName == ControlW)
				SectionNo = Sec_ControlW;
            if(SectionName == prot_general)
				SectionNo = Sec_prot_general;
			else if(SectionName.Find(LineSign) >=0)
			{
				SectionNo = Sec_Line;
				*CurNum = myatoi(SectionName.Right(SectionName.GetLength() - LineSign.GetLength()));
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
		}

		else if(FileType == FAULT_FILE)
		{
			if(SectionName == InfoSign)
				SectionNo = Sec_Info;
			
			if(SectionName == "Byd_Current")
			{
				byd_Current=true;
				SectionNo = Sec_Line;
				*CurNum = 0;
				step1=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			if(SectionName == "Byd_Voltage")
			{
				byd_Voltage=true;
				SectionNo = Sec_Line;
				//*CurNum = 1;
				if(byd_Current==true)
					*CurNum=1;
				else
					*CurNum=0;

				step2=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			if(SectionName == "Byd_ZeroI")
		    {
				byd_ZeroI=true;
				SectionNo = Sec_Line;
				//*CurNum = 2;
				if((byd_Current && byd_Voltage)==true)//两者都为真
					*CurNum=2;
				else if((byd_Current||byd_Voltage)==false)//两者都为假
					*CurNum=0;
				else if((byd_Current||byd_Voltage)==true)//某一个为真
					*CurNum=1;
				step3=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			if(SectionName == "Byd_ZeroU")
			{
				byd_ZeroU=true;
				SectionNo = Sec_Line;
			//	*CurNum = 3;
				if((byd_Current || byd_Voltage || byd_ZeroI )==false)//三者都为假
					*CurNum=0;
				else
					*CurNum=(*CurNum)++;

				step4=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			if(SectionName == "Flt_Current")
			{
				flt1_Current=true;
				SectionNo = Sec_Line;
			//	*CurNum = 4;
				if((byd_Current || byd_Voltage || byd_ZeroI || byd_ZeroU)==false)//四者都为假
					*CurNum=0;
				else
					*CurNum=(*CurNum)++;
				step5=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			
			if(SectionName == "Flt_Current2")
			{
				flt2_Current=true;
				SectionNo = Sec_Line;
			//	*CurNum = 4;
				if((byd_Current || byd_Voltage || byd_ZeroI || byd_ZeroU||flt1_Current)==false)//五者都为假
					*CurNum=0;
				else
					*CurNum=(*CurNum)++;
				step6=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
			if(SectionName == "Flt_3I0")
			{	
				flt_3I0=true;
				SectionNo = Sec_Line;
				if((byd_Current || byd_Voltage || byd_ZeroI || byd_ZeroU||flt1_Current || flt2_Current)==false)//6者都为假
					*CurNum=0;
				else
					*CurNum=(*CurNum)++;
				step7=*CurNum;
				if (*CurNum >= _Max_Prot_Line )
					return -1;
			}
		}
		else if(FileType == SXPLC_FILE)
		{
			if(SectionName == ConfigSign)
				SectionNo = Sec_Config;
			else if(SectionName == DelayTimeSign)
				SectionNo = Sec_DelayTime;
			else if(SectionName == LV_ProtSign)
				SectionNo = Sec_LV_Prot;
			else if(SectionName == AutoBzkSign)
				SectionNo = Sec_Auto_Bzt;
			else if(SectionName == RecloseSign)
				SectionNo = Sec_Bzt;
			else if(SectionName == CtrlTimeSign)
				SectionNo = Sec_Ctrl_time;
			else if(SectionName.Find(UnitSign) >=0)
			{
				SectionNo = Sec_Unit;
				*CurNum = myatoi(SectionName.Right(SectionName.GetLength() - UnitSign.GetLength()));
				if (*CurNum >= 32 )
					return -1;
			}
		}

		else if(FileType == ZJPLC_FILE)
		{
			if(SectionName == ConfigSign)
				SectionNo = Zj_Sec_Config;
			else if(SectionName == DelayTimeSign)
				SectionNo = Zj_Sec_DelayTime;
			else if(SectionName.Find(UnitSign) >=0)
			{
				SectionNo = Zj_Sec_Unit;
				*CurNum = myatoi(SectionName.Right(SectionName.GetLength() - UnitSign.GetLength()));
				if (*CurNum >= 32 )
					return -1;
			}
			else if(SectionName.Find(BZTCONFIG) >= 0)
				SectionNo = Zj_Sec_Bzt;
		}
		else if(FileType == JZSLG_FILE)
		{
			 if (SectionName == InfoSign)
				SectionNo = Sec_Info;
			 else if (SectionName == Plcenable)
			 {
				SectionNo = Sec_enable;
			 }else if (SectionName == Limitvalue)
			 {
				SectionNo = Sec_value;
			 }else if (SectionName == Modetype)
			 {
				SectionNo = Sec_type;
			 }else if (SectionName == Plctime)
			 {
				 SectionNo = Sec_time;
			 }else if (SectionName == Jxchz)
			 {
				 SectionNo = Sec_jxchz;
			 }else if (SectionName == Cxchz)
			 {
				SectionNo = Sec_cxchz;
			 }
		}
		else if(FileType == MLPLC_FILE)
		{
			 if (SectionName == InfoSign)
				SectionNo = Sec_Info;
			 else if (SectionName == Plcenable)
				SectionNo = Sec_enable;
			 else if (SectionName == Limitvalue)
				SectionNo = Sec_value;
			 else if (SectionName == Modetype)
				SectionNo = Sec_type;
			 else if (SectionName == Plctime)
			 	SectionNo = Sec_time;
			 else if (SectionName == Jxchz)
				SectionNo = Sec_jxchz;
			 else if (SectionName == Cxchz)
				SectionNo = Sec_cxchz;
		}
		else if(FileType == SXJZS_FILE)//绍兴集中式
		{
			if(SectionName == InfoSign)//[INFO]
				SectionNo = Sec_Info;
			else if(SectionName.Find(LineSign) >=0)
			{
				SectionNo = Sec_Line;
				*CurNum = myatoi(SectionName.Right(SectionName.GetLength() - LineSign.GetLength()));
				SXJZS_FACT_LINE = *CurNum;	
				if (*CurNum >= _Max_SXJZS_Line )
					return -1;
			}
			else if(SectionName.Find("Prot_Select") >=0)
			{
				SectionNo = 23;
			}
			else
				SectionNo = Sec_None;
		}
		else if(FileType == KMG_FILE )//看门狗 GetSecNo
		{
			if(SectionName == InfoSign)//[INFO]
				SectionNo = Sec_Info;//=1
			
			else if(SectionName.Find("Prot_Select") >=0)//SectionName.Find的值是多少？
			{
				SectionNo = 23;
			}
			if(SectionName == "prot_Line0")
			{
				SectionNo = Sec_Line;
				*CurNum = 0;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}
			if(SectionName == "Byd_Current")
			{
				SectionNo = Sec_Line;//=2
				*CurNum = 1;
				if (*CurNum >= _Max_KMG_Line )//这个条件？				
					return -1;
			}
			if(SectionName == "Byd_Voltage")
			{
				SectionNo = Sec_Line;
				*CurNum = 2;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}
			if(SectionName == "Byd_ZeroI")
			{
				SectionNo = Sec_Line;
				*CurNum = 3;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}
			if(SectionName == "Byd_ZeroU")
			{
				SectionNo = Sec_Line;
				*CurNum = 4;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}
			if(SectionName == "Byd_OverI")
			{
				SectionNo = Sec_Line;
				*CurNum = 5;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}

			if(SectionName == "Flt_Current")
			{
				SectionNo = Sec_Line;
				*CurNum = 6;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}

			if(SectionName == "Flt_3I0")
			{
				SectionNo = Sec_Line;
				*CurNum = 7;
				if (*CurNum >= _Max_KMG_Line )
					return -1;
			}
		}
		else if(FileType == SXYJ_FILE )
		{
			CString s;
			if(SectionName == InfoSign)//[INFO]
			{
				SectionNo = Sec_Info;
			}
			else if (SectionName.Find("Label_") >=0)
			{	
				SectionNo = Sec_Line;
				*CurNum = myatoi(SectionName.Right(SectionName.GetLength() - 6));
			//	s.Format("%d",*CurNum);
			//	AfxMessageBox(s);
				if (*CurNum >= _Max_SXYJ_Line )
					return -1;
			}


		}
	}
	return SectionNo;
}


bool CReadPzkIni::Get_Infomation(CString KeyName,CString KeyStr)
{
	if(!IniFileOpened)
		return false;
	
	if(KeyName == "SetInputs")
		mPzk300NormalCfg.num = myatoi(KeyStr);
	else if(KeyName == "ProtectInputs")
		mPzk300ProCfg.num = myatoi(KeyStr);
	else
		return false;

	return true;

	
}

bool CReadPzkIni::GetFileName(CString KeyName, CString KeyStr)
{
	int i,j;
	if(!IniFileOpened)
		return false;

	if(KeyName == "FileName")
	//	FileType = myatoi(KeyStr);
	{
		MLValid = 0;
		if(KeyStr.Compare("mzkprot.ini") == 0)
			FileType = PROTECT_FILE;
		else if(KeyStr.Compare("sx_plc.ini") == 0)
			FileType = SXPLC_FILE;
		else if(KeyStr.Compare("zj_plc.ini") == 0)
			FileType = ZJPLC_FILE;
		else if(KeyStr.Compare("pzk36b_mlplc.ini") == 0)
			FileType = MLPLC_FILE;
		else if(KeyStr.Compare("fault.ini") == 0)
			FileType = FAULT_FILE;
		else if(KeyStr.Compare("protplc.ini")==0)
			FileType = SXJZS_FILE;
		else if(KeyStr.Compare("kmgprotflt.ini")==0)
			FileType = KMG_FILE;
		else if(KeyStr.Compare("sxyj.ini")==0)
			FileType = SXYJ_FILE;
		else if(KeyStr.Compare("pzk36b_plc.ini") == 0)
		{
			FileType = JZSLG_FILE;
			for (i=1;i<4;i++)
			{
				for (j=1;j<12;j++)
				{
					pzkcx[i][j].istrue = 0;
				}
			}
		}
		else
			FileType = 0;
	}
	else
		return false;

	return true;
}

bool CReadPzkIni::GetSecInfo(CString KeyName, CString KeyStr) //有些选项已不再使用
{
	
	if(!IniFileOpened)
		return false;
	if(FileType == SXJZS_FILE)
	{
		if(KeyName == "Version")
		{	
			SXJZSFile.Cfg.Version = KeyStr;
			SXJZSFileTemp.Cfg.Version = KeyStr;
		}
		else if(KeyName == "Date")
		{	SXJZSFile.Cfg.CreateTime = KeyStr;
			SXJZSFileTemp.Cfg.CreateTime = KeyStr;
		}
		else if(KeyName == "Prot_YXEnable")
		{
			SXJZSFile.Cfg.Prot_YXEnable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.Prot_YXEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Prot_MsgEnable")
		{
			SXJZSFile.Cfg.Prot_MsgEnable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.Prot_MsgEnable = myatoi(KeyStr);
		}
		else if(KeyName == "FixActTime")
		{
			SXJZSFile.Cfg.FixActTime = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.FixActTime = myatoi(KeyStr);
		}

		/*
		else if(KeyName == "ZXCHZTime")
		{
			SXJZSFile.Cfg.ZXCHZTime = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.ZXCHZTime = myatoi(KeyStr)+2;
		}
		else if(KeyName == "FZXCHZTime")
		{
			SXJZSFile.Cfg.FZXCHZTime = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.FZXCHZTime = myatoi(KeyStr);
		}
		*/
	/*
		else if(KeyName == "Byd_SOEEnable")
		{
			SXJZSFile.Cfg.Byd_SOEEnable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.Byd_SOEEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Flt_YXEnable")
		{	
			SXJZSFile.Cfg.Flt_YXEnable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.Flt_YXEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Flt_RepEnable")
		{
			SXJZSFile.Cfg.Flt_RepEnable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.Flt_RepEnable = myatoi(KeyStr);
		}
*/		
		else if(KeyName == "PLC_Enable")
		{
			SXJZSFile.Cfg.PLC_Enable = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.PLC_Enable = myatoi(KeyStr);
		}

		else if(KeyName == "ProtLineNum")
		{	
			SXJZSFile.Cfg.ProtLineNum = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.ProtLineNum = myatoi(KeyStr);
		}
		else if(KeyName == "ProtNumPerLine")
		{
			SXJZSFile.Cfg.ProtNumPerLine = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.ProtNumPerLine = myatoi(KeyStr);
		}
		else if(KeyName == "MxType")
		{
			SXJZSFile.Cfg.MxType = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.MxType = myatoi(KeyStr);
		}
		else if(KeyName == "LeftDTUNum")
		{
			SXJZSFile.Cfg.LeftDTUNum = myatoi(KeyStr);
			SXJZSFileTemp.Cfg.LeftDTUNum = myatoi(KeyStr);
		//	CString cs;
		//	cs.Format(".....%d .. ",SXJZSFileTemp.Cfg.LeftDTUNum);
		//	AfxMessageBox(cs);
		}
		else
			return false;	
	}	
	
	if(FileType == PROTECT_FILE || FileType == FAULT_FILE)
	{
		if(KeyName == "Version")
			ProtFile.Cfg.Version = KeyStr;
		else if(KeyName == "Date")
		    ProtFile.Cfg.CreateTime = KeyStr;
		else if(KeyName == "Byd_SOEEnble")
			ProtFile.Cfg.Byd_SOEEnble = myatoi(KeyStr);
		else if(KeyName == "Flt_YXEnble")
			ProtFile.Cfg.Flt_YXEnble = myatoi(KeyStr);
		else if(KeyName == "Flt_RepEnble")
			ProtFile.Cfg.Flt_RepEnble = myatoi(KeyStr);
		else if(KeyName == "Prot_YXEnable")
			ProtFile.Cfg.Prot_YXEnable = myatoi(KeyStr);
		else if(KeyName == "Prot_MsgEnable")
			ProtFile.Cfg.Prot_MsgEnable = myatoi(KeyStr);
		else if(KeyName == "ProtLineNum")
			ProtFile.Cfg.LineNum = myatoi(KeyStr);
		else if(KeyName == "ProtNumPerLine")
			ProtFile.Cfg.PNPL = myatoi(KeyStr);
		else if(KeyName == "Switch_Remote")
			ProtFile.Cfg.Switch_Remote = myatoi(KeyStr);
		else if(KeyName == "FixActTime")
			ProtFile.Cfg.FixActTime = myatoi(KeyStr);
		else if(KeyName == "Switch_Local")
			ProtFile.Cfg.Switch_Local = myatoi(KeyStr);
		else if(KeyName == "V_ConnectMode")
			ProtFile.Cfg.V_ConnectMode = myatoi(KeyStr);
		else	
			return false;
	}
	
	//看门狗文件
	if(FileType == KMG_FILE)//GetSecInfo
	{
		if(KeyName == "Version")
		{
			KMGFile.Cfg.Version = KeyStr;
			KMGFileTemp.Cfg.Version = KeyStr;	
		}
		else if(KeyName == "Date")
		{
		    KMGFile.Cfg.CreateTime = KeyStr;
			KMGFileTemp.Cfg.CreateTime = KeyStr;
		}
		else if(KeyName == "Prot_YXEnable")
		{
			KMGFile.Cfg.Prot_YXEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Prot_YXEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Prot_MsgEnable")
		{
			KMGFile.Cfg.Prot_MsgEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Prot_MsgEnable = myatoi(KeyStr);	
		}	
		else if(KeyName == "Byd_YXEnable")
		{
			KMGFile.Cfg.Byd_SOEEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Byd_SOEEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Flt_YXEnable")
		{
			KMGFile.Cfg.Flt_YXEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Flt_YXEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Flt_RepEnable")
		{
			KMGFile.Cfg.Flt_RepEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Flt_RepEnable = myatoi(KeyStr);
		}
		else if(KeyName == "Flt_RcwEnable")
		{
			KMGFile.Cfg.Flt_RcwEnable = myatoi(KeyStr);
			KMGFileTemp.Cfg.Flt_RcwEnable = myatoi(KeyStr);
		}
		else if(KeyName == "V_ConnectMode")
		{
			KMGFile.Cfg.V_ConnectMode = myatoi(KeyStr);
			KMGFileTemp.Cfg.V_ConnectMode = myatoi(KeyStr);
		}
		else if(KeyName == "FixActTime")
		{
			KMGFile.Cfg.FixActTime = myatoi(KeyStr);
			KMGFileTemp.Cfg.FixActTime = myatoi(KeyStr);
		}
		else if(KeyName == "ProtNumPerLine")
		{
			KMGFile.Cfg.ProtNumPerLine = myatoi(KeyStr);
			KMGFileTemp.Cfg.ProtNumPerLine = myatoi(KeyStr);
		}
		else
			return false;
	}

//	CString cc;

	if(FileType == SXYJ_FILE)
	{
		
		if(KeyName == "ProtLineNum")
		{
			SXYJFile.Cfg.ProtLineNum = myatoi(KeyStr);
			SXYJFileTemp.Cfg.ProtLineNum = myatoi(KeyStr);
		}
		else if(KeyName == "DeviceName")
		{
			SXYJFile.Cfg.DeviceName = (KeyStr);
			SXYJFileTemp.Cfg.DeviceName = (KeyStr);
		}
//	cc.Format("%d",myatoi(KeyStr));
//	AfxMessageBox(cc);
	}


	return true;
}

bool CReadPzkIni::GetControlW(CString KeyName, CString KeyStr) 
{
	int KeyNo;
	CString keysign;
	keysign = "ControlByte";
	if(!IniFileOpened)
		return false;
	if(KeyName == "ControlW_Len")
		ProtFile.Cfg.ControlW_Len = myatoi(KeyStr);
	else if(KeyName.Find("ControlByte") >= 0)
	{
		KeyNo = myatoi(KeyName.Right(KeyName.GetLength() - keysign.GetLength()));
		ProtFile.Cfg.ControlWByte[KeyNo] = myatoi(KeyStr);
	}
	else
		return false;
	
	return true;
}
bool CReadPzkIni::Getprot_general(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "ProtLineNum")
		ProtFile.Cfg.LineNum = myatoi(KeyStr);
	else if(KeyName == "ProtNumPerLine")
		ProtFile.Cfg.PNPL = myatoi(KeyStr);
	else if(KeyName == "Switch_Remote")
		ProtFile.Cfg.Switch_Remote = myatoi(KeyStr);
	else if(KeyName == "FixActTime")
		ProtFile.Cfg.FixActTime = myatoi(KeyStr);
	else if(KeyName == "Switch_Local")
		ProtFile.Cfg.Switch_Local = myatoi(KeyStr);
	else if(KeyName == "V_ConnectMode")
		ProtFile.Cfg.V_ConnectMode = myatoi(KeyStr);
	else
		return false;
	
	return true;
}

bool CReadPzkIni::Getprot_select(CString KeyName, CString KeyStr)//绍兴集中式选线
{
	int ProtNo;
	int i,j;
	if(!IniFileOpened)
		return false;

	//CString cs;
	if(FileType == SXJZS_FILE)
	{
		if(KeyName.Find("Prot_Select") >=0)
		{	
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Prot_Select")));
			SwitchTypeNum = ProtNo;//开关类型多少个 根据Prot_Select后面的数字进行来判断
			SXJZSFile.SXJZSSelct[ProtNo]=KeyStr;//将keystr保存起来，一般是不动的

			KeyStr.TrimLeft();
			KeyStr.TrimRight();	
			for(i=0,j=0;i<KeyStr.GetLength();j++)
			{
				SXJZS_Select[ProtNo][j]=myatoi(KeyStr.Mid(i,i+2));;
				i=i+2;
				//cs.Format("%d",SXJZS_Select[ProtNo][j]);
				//AfxMessageBox(cs);
				SXJZS_FACT_SELECT[ProtNo]=j;
			}
		}
	}
	if(FileType == KMG_FILE)//Getprot_select
	{
		if(KeyName.Find("Prot_Select") >=0)
		{	
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Prot_Select")));
			KMG_SwitchTypeNum = ProtNo;//开关类型多少个 根据Prot_Select后面的数字进行来判断
			KMGFile.KMGSelct[ProtNo]=KeyStr;//将keystr保存起来，一般是不动的

			KeyStr.TrimLeft();
			KeyStr.TrimRight();	
			for(i=0,j=0;i<KeyStr.GetLength();j++)
			{
				KMG_Select[ProtNo][j]=myatoi(KeyStr.Mid(i,i+2));;
				i=i+2;
				//cs.Format("%d",SXJZS_Select[ProtNo][j]);
				//AfxMessageBox(cs);
				KMG_FACT_SELECT[ProtNo]=j;
			}
		}
	}

	return true;
}


bool CReadPzkIni::GetSecLine(CString KeyName, CString KeyStr, int CurNum)
{
	int ProtNo;
	CString str;

	if(!IniFileOpened)
		return false;

	str.Format("prot_Line%d",CurNum);

/*
	if(KeyName == "Line_Sbo")
		ProtFile.Line[CurNum].LineCfg.Line_Sbo = myatoi(KeyStr);
	else if(KeyName == "Line_Switch")
		ProtFile.Line[CurNum].LineCfg.Line_Switch = myatoi(KeyStr);
	else if(KeyName == "Line_Switch_Remote")
		ProtFile.Line[CurNum].LineCfg.Line_Switch_Remote = myatoi(KeyStr);
	else if(KeyName == "Line_Switch_Local")
		ProtFile.Line[CurNum].LineCfg.Line_Switch_Local = myatoi(KeyStr);
	else if(KeyName == "V_ConnectMode")
		ProtFile.Line[CurNum].LineCfg.V_ConnectMode = myatoi(KeyStr);
		*/	
	if(FileType == FAULT_FILE || FileType == PROTECT_FILE)
	{//fault function
		if(KeyName.Find("LineNum") >=0)
		{
			ProtFile.Line[CurNum].LineCfg.LineNum = myatoi(KeyStr);
		//	number[CurNum]=myatoi(KeyStr);
		}
		if(KeyName.Find("Byd_Type") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Type")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("Byd_Line") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Line")));

			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Name = KeyStr;
		
		//ProtNo 代表keyname中的 数字，线路序号
		
			NumberMax[CurNum][0]=ProtNo;

		//	CString ss;
		//	ss.Format("%d",CurNum);
		//	AfxMessageBox(ss);
		//	AfxMessageBox(KeyStr);
		}
		else if(KeyName.Find("Byd_Enable") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Enable")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Enable = (myatoi(KeyStr) == 0)? false : true;
		}
		else if(KeyName.Find("Byd_Value1") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Value") -1));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Value1 = myatof(KeyStr);

		}
		else if(KeyName.Find("Byd_Value2") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Value") -1));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Value2 = myatof(KeyStr);
		}
		else if(KeyName.Find("Byd_Time") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Time")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Time = myatof(KeyStr);
		}
		else if(KeyName.Find("Byd_Unit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Unit")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Unit = KeyStr;
		}

		//[Flt_3I0]  [Flt_Current2] [Flt_Current1]

			else if(KeyName.Find("Flt_Line") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Line")));
				if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Name = KeyStr;
		
			NumberMax[CurNum][0]=ProtNo;//故障文件中用于统计多少个
		}

		else if(KeyName.Find("Flt_Enable") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Enable")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Enable = (myatoi(KeyStr) == 0)? false : true;
		}

		else if(KeyName.Find("Flt_Value") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Value")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Value1 = myatof(KeyStr);
		}

		else if(KeyName.Find("Flt_Time") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Time")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Time = myatof(KeyStr);
		}

		else if(KeyName.Find("Flt_Unit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Unit")));
			if(ProtNo >=_Max_Prot_Line)
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Unit = KeyStr;
		}
	
		//protect function
		if(KeyName.Find("Line_Switch") >= 0)
		{
			ProtFile.Line[CurNum].LineCfg.Line_Switch = myatoi(KeyStr);

		}
		if(KeyName.Find("prot_Type") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Type")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("prot_Name") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Name")));
				if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Name = KeyStr;
		}
		else if(KeyName.Find("prot_Enable") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Enable")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Enable = 
				myatoi(KeyStr);
		}
		else if(KeyName.Find("prot_Value") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Value")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Value = myatof(KeyStr);
		}
		else if(KeyName.Find("prot_Time") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Time")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Time = myatof(KeyStr);
		}
		else if(KeyName.Find("prot_Unit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Unit")));
			if(ProtNo >=_Max_Prot_Line)
		//	if (ProtNo >= 32 )
				return false;
			ProtFile.Line[CurNum].ProtItem[ProtNo].Unit = KeyStr;
		}
	}
	
	if(FileType == SXJZS_FILE)
	{
		if(KeyName.Find("Switch_Type") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("SBO_Num") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
		}
		else if(KeyName.Find("Switch_Num") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.Switch_Num = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.Switch_Num = myatoi(KeyStr);
		}
		else if(KeyName.Find("Line_Type") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.Line_Type = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.Line_Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("CxLogicFlag") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.CxLogicFlag = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.CxLogicFlag = myatoi(KeyStr);
		}
		else if(KeyName.Find("CHZ_Enable") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.CHZ_Enable = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.CHZ_Enable = myatoi(KeyStr);
		}
		else if(KeyName.Find("PHaveV_Flag") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.PHaveV_Flag = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.PHaveV_Flag = myatoi(KeyStr);
		}
		else if(KeyName.Find("PSwitchStatus") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.PSwitchStatus = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.PSwitchStatus = myatoi(KeyStr);
		}
		else if(KeyName.Find("Line_Name") >=0)
		{
			SXJZSFile.Line[CurNum].LineCfg.Line_Name = KeyStr;
			SXJZSFileTemp.Line[CurNum].LineCfg.Line_Name = KeyStr;
		}
		else if(KeyName.Compare("ZXCHZTime")==0)
		{
			SXJZSFile.Line[CurNum].LineCfg.ZXCHZTime = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.ZXCHZTime = myatoi(KeyStr);
		//	CString cs;
		//	cs.Format("aaaaa??? == %d",SXJZSFile.Line[CurNum].LineCfg.ZXCHZTime);
		//	AfxMessageBox(cs);
		}
		else if(KeyName.Compare("FZXCHZTime")==0)
		{
			SXJZSFile.Line[CurNum].LineCfg.FZXCHZTime = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].LineCfg.FZXCHZTime = myatoi(KeyStr);
		}

		
		else if(KeyName.Find("prot_Type") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Type")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Type = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Type = myatoi(KeyStr);
		}
	
		else if(KeyName.Find("prot_Name") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Name")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Name = KeyStr;
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Name = KeyStr;
		}
		
		else if(KeyName.Find("prot_Enable") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Enable")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Enable = myatoi(KeyStr);
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Enable = myatoi(KeyStr);
		}
		else if(KeyName.Find("prot_Value") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Value")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Value = myatof(KeyStr);
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Value = myatof(KeyStr);
		}
		else if(KeyName.Find("prot_Time") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Time")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Time = myatof(KeyStr);
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Time = myatof(KeyStr);
		}		
		
		else if(KeyName.Find("prot_Unit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Unit")));
			if(ProtNo >=_Max_SXJZS_Line)
				return false;
			SXJZSFile.Line[CurNum].SXJZSItem[ProtNo].Unit = KeyStr;
			SXJZSFileTemp.Line[CurNum].SXJZSItem[ProtNo].Unit = KeyStr;
		}
	}

	if(FileType == KMG_FILE)//?2017-4-19 GetSecLine
	{
		if(KeyName.Find("Switch_Type") >=0)
		{
			KMGFile.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("SBO_Num") >=0)
		{
			KMGFile.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
		}

		else if(KeyName.Find("Byd_Line") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Line0")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Line = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Line = myatoi(KeyStr);
		}
		else if(KeyName.Find("Byd_Enable") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Line")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
		}
		else if(KeyName.Find("Byd_Value1") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Value")-1));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
		}
		else if(KeyName.Find("Byd_Value2") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Value")-1));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Value2 = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Value2 = myatof(KeyStr);
		}
		else if(KeyName.Find("Byd_Time") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Time")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
		}
		else if(KeyName.Find("Byd_Unit") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Byd_Unit")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
		}
		

		else if(KeyName.Find("Flt_Line") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Line")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Line = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Line = myatoi(KeyStr);
		}
		else if(KeyName.Find("Flt_Enable") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Enable")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
		}
		else if(KeyName.Find("Flt_Value") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Value")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
		}
		
		else if(KeyName.Find("Flt_Time") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Time")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
		}
		else if(KeyName.Find("Flt_Unit") >= 0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("Flt_Unit")));

			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
		}
		else if(KeyName.Find("Switch_Type") >=0)
		{
			KMGFile.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].LineCfg.Switch_Type = myatoi(KeyStr);
		}
		else if(KeyName.Find("SBO_Num") >=0)
		{
			KMGFile.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].LineCfg.SBO_Num = myatoi(KeyStr);
		}
		else if(KeyName.Find("Switch_Num") >=0)
		{
			KMGFile.Line[CurNum].LineCfg.Switch_Num = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].LineCfg.Switch_Num = myatoi(KeyStr);
		}
		else if(KeyName.Find("prot_Type") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Type")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Type = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Type = myatoi(KeyStr);
		}
	
		else if(KeyName.Find("prot_Name") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Name")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Name = KeyStr;
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Name = KeyStr;
		}
		
		else if(KeyName.Find("prot_Enable") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Enable")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Enable = myatoi(KeyStr);
		}
		else if(KeyName.Find("prot_Value") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Value")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Value1 = myatof(KeyStr);
		}
		else if(KeyName.Find("prot_Time") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Time")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Time = myatof(KeyStr);
		}		
		
		else if(KeyName.Find("prot_Unit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("prot_Unit")));
			if(ProtNo >=_Max_KMG_Line)
				return false;
			KMGFile.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
			KMGFileTemp.Line[CurNum].KMGItem[ProtNo].Unit = KeyStr;
		}
	}

	CString cs;
	if(FileType == SXYJ_FILE)
	{
	//	AfxMessageBox("aaa");
		if(KeyName == "LineName")
		{
			SXYJFile.Line[CurNum].LineCfg.LineName = KeyStr;
			SXYJFileTemp.Line[CurNum].LineCfg.LineName = KeyStr;
			
		}
		else if(KeyName == "YxNum")
		{
			SXYJFile.Line[CurNum].LineCfg.YxNum = myatoi(KeyStr);
			SXYJFileTemp.Line[CurNum].LineCfg.YxNum = myatoi(KeyStr);
		}
		else if(KeyName == "YcNum")
		{
			SXYJFile.Line[CurNum].LineCfg.YcNum = myatoi(KeyStr);
			SXYJFileTemp.Line[CurNum].LineCfg.YcNum = myatoi(KeyStr);
		}
		else if(KeyName.Find("YxNo") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YxNo")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYXItem[ProtNo].dot = (KeyStr);
			SXYJFileTemp.Line[CurNum].SXYJYXItem[ProtNo].dot = (KeyStr);
		
		}
		else if(KeyName.Find("YxName") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YxName")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYXItem[ProtNo].Name = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYXItem[ProtNo].Name = KeyStr;

		}

		else if(KeyName.Find("YcNo") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YcNo")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYCItem[ProtNo].dot = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYCItem[ProtNo].dot = KeyStr;
		}
		else if(KeyName.Find("YcName") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YcName")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYCItem[ProtNo].Name = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYCItem[ProtNo].Name = KeyStr;
		}
		else if(KeyName.Find("YcUnit") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YcUnit")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYCItem[ProtNo].Unit = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYCItem[ProtNo].Unit = KeyStr;
		}
		else if(KeyName.Find("YcScale") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YcScale")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYCItem[ProtNo].Scale = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYCItem[ProtNo].Scale = KeyStr;
		}
		else if(KeyName.Find("YcDivi") >=0)
		{
			ProtNo = myatoi(KeyName.Right(KeyName.GetLength() - strlen("YcDivi")));
			if(ProtNo >=_Max_SXYJ_Line)
				return false;
			SXYJFile.Line[CurNum].SXYJYCItem[ProtNo].Divied = KeyStr;
			SXYJFileTemp.Line[CurNum].SXYJYCItem[ProtNo].Divied = KeyStr;
		}

	}



	return true;
}

bool CReadPzkIni::GetConfig(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "PlcEnable")
		PlcFile.Cfg.PlcEnable = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "UnitTotal")
		PlcFile.Cfg.UnitTotal = myatoi(KeyStr);
	else if(KeyName == "InNum")
		PlcFile.Cfg.InNum = myatoi(KeyStr);
	else if(KeyName == "OutNum1")
		PlcFile.Cfg.OutNum1 = myatoi(KeyStr);
	else if(KeyName == "OutNum2")
		PlcFile.Cfg.OutNum2 = myatoi(KeyStr);
	else if(KeyName == "RecloseCheckVol")
		PlcFile.Cfg.RecloseCheckVol = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "BztCheckVol")
		PlcFile.Cfg.BztCheckVol = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "LogicVol")
		PlcFile.Cfg.LogicVol = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetDelayTime(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "InRecloseTime")
		PlcFile.Delay.InRecloseTime = myatoi(KeyStr);
	else if(KeyName == "OutRecloseTime")
		PlcFile.Delay.OutRecloseTime = myatoi(KeyStr);
	else if(KeyName == "InReclose2Time")
		PlcFile.Delay.InReclose2Time = myatoi(KeyStr);
	else if(KeyName == "ConnectTime")
		PlcFile.Delay.ConnectTime = myatoi(KeyStr);
	else if(KeyName == "t5")
		PlcFile.Delay.t5 = myatoi(KeyStr);
	else if(KeyName == "t6")
		PlcFile.Delay.t6 = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetLVProt(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "Enable1")
		PlcFile.LVProt.Enable1 = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "Delay1")
		PlcFile.LVProt.Delay1 = myatoi(KeyStr);
	else if(KeyName == "Value1")
		PlcFile.LVProt.Value1 = myatoi(KeyStr);
	else if(KeyName == "Enable2")
		PlcFile.LVProt.Enable2 = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "Delay2")
		PlcFile.LVProt.Delay2 = myatoi(KeyStr);
	else if(KeyName == "Value2")
		PlcFile.LVProt.Value2 = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetAutoBzt(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "Enable")
		PlcFile.AutoBzt.Enable = false;//(KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "Delay")
		PlcFile.AutoBzt.Delay = myatoi(KeyStr);
	else if(KeyName == "Value")
		PlcFile.AutoBzt.Value = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetCtrl(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "TripTime")
		PlcFile.CtrlTime.TripTime = myatoi(KeyStr);
	else if(KeyName == "CloseTime")
		PlcFile.CtrlTime.CloseTime = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetBzt(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "ConnectEnable")
		PlcFile.Bzt.ConnectEnable = (KeyStr.Compare("yes") == 0)? true : false;
	else
		return false;

	return true;
}

bool CReadPzkIni::GetUnit(CString KeyName, CString KeyStr, int CurNum)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "RecloseEnable")
	{
		if(KeyStr == "yes")
			PlcFile.Reclose.ReClose[CurNum] = true;
		else
			PlcFile.Reclose.ReClose[CurNum] = false;
	}
	else if(KeyName == "CheckVoltage")
	{
		if(KeyStr == "yes")
			PlcFile.Reclose.CheckVol[CurNum] = true;
		else
			PlcFile.Reclose.CheckVol[CurNum] = false;
	}
	else if(KeyName == "RecloseDelay")
	{
		PlcFile.Reclose.RecloseDelay[CurNum] = atoi(KeyStr);
	}
	else
		return false;

	return true;
}

bool CReadPzkIni::GetZjConfig(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "PlcEnable")
		ZjPlcFile.Cfg.PlcEnable = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "UnitTotal")
		ZjPlcFile.Cfg.UnitTotal = myatoi(KeyStr);
	else if(KeyName == "LogicVol")
		ZjPlcFile.Cfg.LogicVol = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetZjDelayTime(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "InRecloseTime")
		ZjPlcFile.Delay.InRecloseTime = myatoi(KeyStr);
	else if(KeyName == "PlcTime")
		ZjPlcFile.Delay.PlcTime = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetZjBzt(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "Enable1")
		ZjPlcFile.Bzt[0].Enable = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "Delay1")
		ZjPlcFile.Bzt[0].Delay = myatoi(KeyStr);
	else if(KeyName == "Enable2")
		ZjPlcFile.Bzt[1].Enable = (KeyStr.Compare("yes") == 0)? true : false;
	else if(KeyName == "Delay2")
		ZjPlcFile.Bzt[1].Delay = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::GetZjUnit(CString KeyName, CString KeyStr, int CurNum)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "RecloseEnable")
	{
		if(KeyStr == "yes")
			ZjPlcFile.Reclose.ReClose[CurNum] = true;
		else
			ZjPlcFile.Reclose.ReClose[CurNum] = false;
	}
	else
		return false;

	return true;
}

void ReadUnionData(Pzk300UnionStru *val, int datatype, CString KeyStr)
{
	switch(datatype)
	{
	case  NO_TYPE:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	case INT_TYPE:
		(*val).SetInt = myatoi(KeyStr);
		break;
	case FLOAT_TYPE:
		(*val).SetFloat = (float)atof(KeyStr);
		break;
	case STR_TYPE:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	default:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	}
}

bool CReadPzkIni::Get300Cfg(CString KeyName,CString KeyStr,int CurNum)
{
	if(!IniFileOpened)
		return false;

	if(KeyName == "ChinaName")
		mPzk300NormalCfg.NormalCfg[CurNum].ChinaName = KeyStr;
	else if(KeyName == "SetInputName")
		mPzk300NormalCfg.NormalCfg[CurNum].SetInputName = KeyStr;
	else if(KeyName == "SetInputValue")
	{
		ReadUnionData(&(mPzk300NormalCfg.NormalCfg[CurNum].SetInputValue), 
						mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataStyle,
						KeyStr);
	}
	else if(KeyName == "SetInputDataUnit")
	{
		mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataUnit = KeyStr;
	}
	else if(KeyName == "SetInputDataStyle")
		mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataStyle = myatoi(KeyStr);
	else if(KeyName == "SetInputDataHLimit")
	{
		ReadUnionData(&(mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataHLimit), 
						mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataStyle,
						KeyStr);
	}
	else if(KeyName == "SetInputDataLLimit")
	{
		ReadUnionData(&(mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataLLimit), 
						mPzk300NormalCfg.NormalCfg[CurNum].SetInputDataStyle,
						KeyStr);
	}
	else if(KeyName == "SetInputRemark")
		mPzk300NormalCfg.NormalCfg[CurNum].Remark = KeyStr;
	else
		return false;

	return true;
}

bool CReadPzkIni::Get300Pro(CString KeyName,CString KeyStr,int CurNum)
{
	if(!IniFileOpened)
		return false;

	Pzk300ProItemCfgStru *val;
	val = &(mPzk300ProCfg.ProcCfg[CurNum]);
	if(KeyName == "ProtectName")
		val->ProtectName = KeyStr;
	else if(KeyName == "ProtectEnable")
		val->ProtectEnable = myatoi(KeyStr);
	else if(KeyName == "ProtectValue")
		val->ProtectValue = myatoi(KeyStr);
	else if(KeyName == "ProtectValueUnit")
		val->ProtectValueUnit = KeyStr;
	else if(KeyName == "ProtectValueHLimit")
		val->ProtectValueHLimit = myatoi(KeyStr);
	else if(KeyName == "ProtectValueLLimit")
		val->ProtectValueLLimit = myatoi(KeyStr);
	else if(KeyName == "ProtectTime")
		val->ProtectTime = myatoi(KeyStr);
	else if(KeyName == "ProtectTimeUnit")
		val->ProtectTimeUnit = KeyStr;
	else if(KeyName == "ProtectTimeHLimit")
		val->ProtectTimeHLimit = myatoi(KeyStr);
	else if(KeyName == "ProtectTimeLLimit")
		val->ProtectTimeLLimit = myatoi(KeyStr);
	else
		return false;

	return true;
}

bool CReadPzkIni::SaveToIni(CString FileName)
{
	IniFileName = FileName;
	return SaveToIni();
}

bool CReadPzkIni::SaveToTempIni(CString FileName)
{
	CString saveFileName = IniFileName;
	IniFileName = FileName;
	if(!SaveToIni())
	{
		IniFileName = saveFileName;
		return false;
	}
	IniFileName = saveFileName;
	EverModified = true;
	return true;
}

CString GetFileNameFromType(int fileType)
{
	switch(fileType)
	{
	case PROTECT_FILE:
		return "mzkprot.ini";
	case SXPLC_FILE:
		return "sx_plc.ini";
	case ZJPLC_FILE:
		return "zj_plc.ini";
	case JZSLG_FILE:
		return "pzk36b_plc.ini";
	case MLPLC_FILE:
        return "pzk36b_mlplc.ini";
	case FAULT_FILE:
		return "fault.ini";
	case SXJZS_FILE:
		return "protplc.ini";
	case KMG_FILE:
		return "kmgprotflt.ini";
	case SXYJ_FILE:
		return "sxyj.ini";
	}
	return "";
}

CString CReadPzkIni::WriteSXJZSNote(int i)
{
	if(Note[i].IsEmpty())//注释为空
	{
		return	"";	
	}
	else
	{
		return Note[i];
	}
	//AfxMessageBox(note);
}

bool CReadPzkIni::SaveToIni()
{
	int i,j;
	CString filter;
	CString str1,str2;
	

	if (!IniFileOpened)
		return false;

//	if(IniFileName != "")
//		mStdioFile.Close();

	if(IniFileName == "")
	{
		filter = "All Supported Files(*.ini)|*.ini|";
		filter+= "All Files(*.*)|*.*||";
		CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,(LPCSTR)filter);
		if (dlg.DoModal() != IDOK)
			return false;
		IniFileName = dlg.GetPathName();
	}

	if(IniFileName == "")
	{
		AfxMessageBox("文件名为空,存盘失败,请重新保存!");
		return false;
	}
		
	CString expName = IniFileName.Right(3);
	expName.MakeLower();

	if(expName != "ini")
//	if((IniFileName.Find(".ini") < 0) && (IniFileName.Find(".INI") < 0))
		IniFileName += ".ini";

	
	if(FileType == FAULT_FILE || FileType == SXJZS_FILE)//绍兴集中式  // 故障文件重写
	{
		mStdioFile.Open(IniFileName,CFile::modeWrite|CFile::modeCreate,NULL);
	}
	
	if(FileType == KMG_FILE )//看门狗文件重写
	{
		mStdioFile.Open(IniFileName,CFile::modeWrite|CFile::modeCreate,NULL);
	}
	if(FileType == SXYJ_FILE)//绍兴液晶文件重写
	{
		mStdioFile.Open(IniFileName,CFile::modeWrite|CFile::modeCreate,NULL);
	}
	
	
	
	if(FileType == SXYJ_FILE)
	{
		mStdioFile.WriteString("####-------------------------------------------------------\n");
		mStdioFile.WriteString("####------绍兴液晶配置文件---------------------------------\n");
		mStdioFile.WriteString("####-------------------------------------------------------\n");	
		
		/////////////////////////////写FILENAME
	//	AfxMessageBox("aa");
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("ProtLineNum", SXYJFile.Cfg.ProtLineNum);
		WriteLine("DeviceName", SXYJFile.Cfg.DeviceName);
		WriteLine("");
		
		int i=0;
		int j=0;
		for(i=0;i<SXYJFile.Cfg.ProtLineNum;i++)
		{
			WriteLine("[Label_"+Str(i)+"]");
			WriteLine("LineName",SXYJFile.Line[i].LineCfg.LineName);
			WriteLine("YxNum",SXYJFile.Line[i].LineCfg.YxNum);
			WriteLine("YcNum",SXYJFile.Line[i].LineCfg.YcNum);
			WriteLine("");
			for(j=0;j<SXYJFile.Line[i].LineCfg.YxNum;j++)
			{	
				WriteLine("YxName"+Str(j),SXYJFile.Line[i].SXYJYXItem[j].Name);
				WriteLine("YxNo"+Str(j),SXYJFile.Line[i].SXYJYXItem[j].dot);
			}
			WriteLine("");
			for(j=0;j<SXYJFile.Line[i].LineCfg.YcNum;j++)
			{	
				WriteLine("YcName"+Str(j),SXYJFile.Line[i].SXYJYCItem[j].Name);
				WriteLine("YcDivi"+Str(j),SXYJFile.Line[i].SXYJYCItem[j].Divied);
				WriteLine("YcScale"+Str(j),SXYJFile.Line[i].SXYJYCItem[j].Scale);
				WriteLine("YcUnit"+Str(j),SXYJFile.Line[i].SXYJYCItem[j].Unit);
				WriteLine("YcNo"+Str(j),SXYJFile.Line[i].SXYJYCItem[j].dot);
			}
			WriteLine("");
		}

	}
	

	if(FileType == KMG_FILE)
	{
		mStdioFile.WriteString("####-------------------------------------------------------\n");
		mStdioFile.WriteString("####------分界开关控制器(看门狗)保护越限故障配置文件-------\n");
		mStdioFile.WriteString("####-------------------------------------------------------\n");	
		
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");//writestring 和writeline什么区别
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");
		
		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", KMGFile.Cfg.Version);
		WriteLine("Date", KMGFile.Cfg.CreateTime);
		WriteLine("");
		
		
		WriteLine("FixActTime", KMGFile.Cfg.FixActTime,WriteSXJZSNote(11));
		WriteLine("Prot_YXEnable", KMGFile.Cfg.Prot_YXEnable,WriteSXJZSNote(12));
		WriteLine("Prot_MsgEnable", KMGFile.Cfg.Prot_MsgEnable,WriteSXJZSNote(13));
		WriteLine("Flt_RcwEnable", KMGFile.Cfg.Flt_RcwEnable,WriteSXJZSNote(14));
		WriteLine("Byd_YXEnable", KMGFile.Cfg.Byd_SOEEnable,WriteSXJZSNote(15));
		WriteLine("Flt_YXEnable", KMGFile.Cfg.Flt_YXEnable,WriteSXJZSNote(16));
		WriteLine("Flt_RepEnable", KMGFile.Cfg.Flt_RepEnable,WriteSXJZSNote(17));
		WriteLine("V_ConnectMode", KMGFile.Cfg.V_ConnectMode,WriteSXJZSNote(18));
		WriteLine("ProtNumPerLine", KMGFile.Cfg.ProtNumPerLine,WriteSXJZSNote(19));
		WriteLine("");

		///////////////////////////[Prot_Select]
		int i;
		mStdioFile.WriteString("[Prot_Select]#"+WriteSXJZSNote(21)+"\n");
		for(i=0;i<=KMG_SwitchTypeNum;i++)
		{
			WriteLine("Prot_Select"+Str(i),KMGFile.KMGSelct[i]);
		}
		WriteLine("");
		mStdioFile.WriteString("##保护定值区设定\n");

		int index;//注释下标
		int j;
		for(i=0;i<8;i++)
		{
			if(i == 0 )
			{
				WriteLine("[prot_Line"+Str(i)+"]#"+WriteSXJZSNote(27));
				WriteLine("Switch_Type", KMGFile.Line[i].LineCfg.Switch_Type,WriteSXJZSNote(28));
			//	WriteLine("SBO_Num", KMGFile.Line[i].LineCfg.SBO_Num,WriteSXJZSNote(25));
			//	WriteLine("Switch_Num", KMGFile.Line[i].LineCfg.Switch_Num,WriteSXJZSNote(26));
				WriteLine("");
				for(j=0;j<KMGFile.Cfg.ProtNumPerLine;j++)//全部保存一遍 0-每条线路保护数
				{	
					WriteLine("prot_Type"+Str(j),KMGFile.Line[i].KMGItem[j].Type);
					WriteLine("prot_Name"+Str(j),KMGFile.Line[i].KMGItem[j].Name);
					WriteLine("prot_Enable"+Str(j),KMGFile.Line[i].KMGItem[j].Enable,WriteSXJZSNote(32));
					WriteLine("prot_Value"+Str(j),KMGFile.Line[i].KMGItem[j].Value1);
					WriteLine("prot_Time"+Str(j),KMGFile.Line[i].KMGItem[j].Time);
					WriteLine("prot_Unit"+Str(j),KMGFile.Line[i].KMGItem[j].Unit);
					WriteLine("");
				}
				mStdioFile.WriteString("##越限告警定值区设定\n");
			}	
			else if(i ==1 || i ==2 || i ==3 || i ==4 || i==5 )
			{
				if(i==1)
				{
					WriteLine("[Byd_Current]#"+WriteSXJZSNote(87));
				}
				else if(i==2)
				{
					WriteLine("[Byd_Voltage]#"+WriteSXJZSNote(96));
				}
				else if(i==3)
				{
					WriteLine("[Byd_ZeroI]#"+WriteSXJZSNote(105));
				}
				else if(i==4)
				{
					WriteLine("[Byd_ZeroU]#"+WriteSXJZSNote(114));
				}
				else if(i==5)
				{
					WriteLine("[Byd_OverI]#"+WriteSXJZSNote(123));
				}

				WriteLine("Byd_LineNum=1;#"+WriteSXJZSNote(88+(i-1)*9));
				for(j=0;j<=0;j++)
				{
					WriteLine("Byd_Line"+Str(j),KMGFile.Line[i].KMGItem[j].Line,WriteSXJZSNote(89));
					WriteLine("Byd_Enable"+Str(j),KMGFile.Line[i].KMGItem[j].Enable,WriteSXJZSNote(90));
					WriteLine("Byd_Value1"+Str(j),KMGFile.Line[i].KMGItem[j].Value1,WriteSXJZSNote(91+(i-1)*9));
					WriteLine("Byd_Value2"+Str(j),KMGFile.Line[i].KMGItem[j].Value2,WriteSXJZSNote(92+(i-1)*9));
					WriteLine("Byd_Time"+Str(j),KMGFile.Line[i].KMGItem[j].Time,WriteSXJZSNote(93));
					WriteLine("Byd_Unit"+Str(j),KMGFile.Line[i].KMGItem[j].Unit,WriteSXJZSNote(94));
					WriteLine("");
				}
				if(i==5)//?因为要写在Byd——over后边，所以需要加一个判定
					mStdioFile.WriteString("##故障检测定值区设定\n");
			}

			else if(i == 6 || i == 7)
			{
				if(i==6)
				{
					WriteLine("[Flt_Current]#"+WriteSXJZSNote(133));
				}
				else if(i==7)
				{
					WriteLine("[Flt_3I0]#"+WriteSXJZSNote(141));
				}
				WriteLine("Flt_LineNum=1;#"+WriteSXJZSNote(134+(i-6)*8));

				for(j=0;j<=0;j++)
				{
					WriteLine("Flt_Line"+Str(j),KMGFile.Line[i].KMGItem[j].Line,WriteSXJZSNote(135));
					WriteLine("Flt_Enable"+Str(j),KMGFile.Line[i].KMGItem[j].Enable,WriteSXJZSNote(136));
					WriteLine("Flt_Value"+Str(j),KMGFile.Line[i].KMGItem[j].Value1,WriteSXJZSNote(137+(i-6)*8));
					WriteLine("Flt_Time"+Str(j),KMGFile.Line[i].KMGItem[j].Time,WriteSXJZSNote(138));
					WriteLine("Flt_Unit"+Str(j),KMGFile.Line[i].KMGItem[j].Unit,WriteSXJZSNote(139));
					WriteLine("");
				}
			}
		}
	}


	if(FileType == SXJZS_FILE)
	{
	//	AfxMessageBox("SAVE");
		mStdioFile.WriteString("####-------------------------------------------------\n");
		mStdioFile.WriteString("####------绍兴集中式保护配置文件---------------------\n");
		mStdioFile.WriteString("####-------------------------------------------------\n");
		
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

			/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", SXJZSFile.Cfg.Version);
		WriteLine("Date", SXJZSFile.Cfg.CreateTime);
		WriteLine("");

        WriteLine("Prot_YXEnable", SXJZSFile.Cfg.Prot_YXEnable,WriteSXJZSNote(11));
		WriteLine("Prot_MsgEnable", SXJZSFile.Cfg.Prot_MsgEnable,WriteSXJZSNote(12));
		WriteLine("PLC_Enable", SXJZSFile.Cfg.PLC_Enable,WriteSXJZSNote(13));
		WriteLine("FixActTime", SXJZSFile.Cfg.FixActTime,WriteSXJZSNote(14));
		WriteLine("");

		WriteLine("ProtLineNum", SXJZSFile.Cfg.ProtLineNum,WriteSXJZSNote(16));
		WriteLine("MxType", SXJZSFile.Cfg.MxType,WriteSXJZSNote(17));
		WriteLine("LeftDTUNum", SXJZSFile.Cfg.LeftDTUNum,WriteSXJZSNote(18));
		WriteLine("ProtNumPerLine", SXJZSFile.Cfg.ProtNumPerLine,WriteSXJZSNote(19));
		WriteLine("");
	
		///////////////////////////[Prot_Select]
		int i;
		//WriteLine("[Prot_Select]");
		mStdioFile.WriteString("[Prot_Select]#"+WriteSXJZSNote(21)+"\n");
		for(i=0;i<=SwitchTypeNum;i++)
		{
			WriteLine("Prot_Select"+Str(i),SXJZSFile.SXJZSSelct[i]);
		}
		WriteLine("");

		///////////////////////////保护定值区设定
		int LineNo;
		int j;
		int index;//注释下标
		for(LineNo=0;LineNo<=SXJZS_FACT_LINE;LineNo++)
		{
			
			index=(22+SwitchTypeNum+1+1+1);

			WriteLine("[prot_Line"+Str(LineNo)+"]");
			WriteLine("Switch_Type", SXJZSFile.Line[LineNo].LineCfg.Switch_Type,WriteSXJZSNote(index));
			WriteLine("SBO_Num", SXJZSFile.Line[LineNo].LineCfg.SBO_Num,WriteSXJZSNote(index+1));
			WriteLine("Switch_Num", SXJZSFile.Line[LineNo].LineCfg.Switch_Num,WriteSXJZSNote(index+2));
			WriteLine("Line_Type", SXJZSFile.Line[LineNo].LineCfg.Line_Type,WriteSXJZSNote(index+3));
			WriteLine("CxLogicFlag", SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag,WriteSXJZSNote(index+4));
			WriteLine("CHZ_Enable", SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable,WriteSXJZSNote(index+5));
			WriteLine("PHaveV_Flag", SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag,WriteSXJZSNote(index+6));
			WriteLine("PSwitchStatus", SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus,WriteSXJZSNote(index+7));
			WriteLine("ZXCHZTime", SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime,WriteSXJZSNote(index+8));
			WriteLine("FZXCHZTime", SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime,WriteSXJZSNote(index+9));
			WriteLine("Line_Name", SXJZSFile.Line[LineNo].LineCfg.Line_Name);
			WriteLine("");

			for(j=0;j<SXJZSFile.Cfg.ProtNumPerLine;j++)
			{
				
				WriteLine("prot_Type"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Type);
				WriteLine("prot_Name"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Name);
				WriteLine("prot_Enable"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Enable,WriteSXJZSNote(index+14));
				WriteLine("prot_Value"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Value);
				WriteLine("prot_Time"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Time,WriteSXJZSNote(index+16));
				WriteLine("prot_Unit"+Str(j),SXJZSFile.Line[LineNo].SXJZSItem[j].Unit);
				WriteLine("");
			}
		}
	}




	if(FileType == FAULT_FILE)
	{
	//	for(int i=0;i<6;i++)
		//{
		//	CString ss;
		//	ss.Format("%d",NumberMax[i][0]);
		//	AfxMessageBox(ss);
	//	}
	//	mStdioFile.WriteString("                                                    MZKCFG.INI\r\n");
		mStdioFile.WriteString("####-------------------------------------------------\n");
		mStdioFile.WriteString("#---------------故障配置文件-------------------------\n");
		mStdioFile.WriteString("####-------------------------------------------------\n");
		WriteLine("");

		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", ProtFile.Cfg.Version);
		WriteLine("Date", ProtFile.Cfg.CreateTime);//Flt_RepEnble mPzkIni.ProtFile.Cfg.Flt_RepEnble
        WriteLine("Byd_SOEEnble", ProtFile.Cfg.Byd_SOEEnble);
		WriteLine("Flt_YXEnble", ProtFile.Cfg.Flt_YXEnble);
		WriteLine("Flt_RepEnble", ProtFile.Cfg.Flt_RepEnble);
		WriteLine("");

		////////////////////////////写保护定制区设定





		/////////////////////////////写Line  需要重写
		for(i=0; i<7; i++)
		{
			switch(i)
			{
			    case 0:
				if(byd_Current==true)
				{	
					WriteLine("[Byd_Current]");
					WriteLine("Byd_LineNum",ProtFile.Line[step1].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step1].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step1][0];j++)
					{
						WriteLine("Byd_Line"+Str(j), ProtFile.Line[step1].ProtItem[j].Name);
						//WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						if(ProtFile.Line[step1].ProtItem[j].Enable == 255)//以前是 true但是不知道为什么没执行保存
							WriteLine("Byd_Enable"+Str(j), 255);
						else
							WriteLine("Byd_Enable"+Str(j), 0);

				        
				        WriteLine("Byd_Value1"+Str(j), ProtFile.Line[step1].ProtItem[j].Value1);
						WriteLine("Byd_Value2"+Str(j), ProtFile.Line[step1].ProtItem[j].Value2);
				        WriteLine("Byd_Time"+Str(j), ProtFile.Line[step1].ProtItem[j].Time);
				        WriteLine("Byd_Unit"+Str(j), ProtFile.Line[step1].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				case 1:
				if(byd_Voltage==true)
				{
					WriteLine("[Byd_Voltage]");
					WriteLine("Byd_LineNum",ProtFile.Line[step2].LineCfg.LineNum);
					//for(j = 0;j<ProtFile.Line[step2].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step2][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Byd_Line"+Str(j), ProtFile.Line[step2].ProtItem[j].Name);
				        if(ProtFile.Line[step2].ProtItem[j].Enable == 255)
							WriteLine("Byd_Enable"+Str(j), 255);
						else
							WriteLine("Byd_Enable"+Str(j), 0);
				        WriteLine("Byd_Value1"+Str(j), ProtFile.Line[step2].ProtItem[j].Value1);
						WriteLine("Byd_Value2"+Str(j), ProtFile.Line[step2].ProtItem[j].Value2);
				        WriteLine("Byd_Time"+Str(j), ProtFile.Line[step2].ProtItem[j].Time);
				        WriteLine("Byd_Unit"+Str(j), ProtFile.Line[step2].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				case 2:
				if(byd_ZeroI==true)
				{
					WriteLine("[Byd_ZeroI]");
					WriteLine("Byd_LineNum",ProtFile.Line[step3].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step3].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step3][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Byd_Line"+Str(j), ProtFile.Line[step3].ProtItem[j].Name);
				        if(ProtFile.Line[step3].ProtItem[j].Enable == 255)
							WriteLine("Byd_Enable"+Str(j), 255);
						else
							WriteLine("Byd_Enable"+Str(j), 0);
				        WriteLine("Byd_Value1"+Str(j), ProtFile.Line[step3].ProtItem[j].Value1);
						WriteLine("Byd_Value2"+Str(j), ProtFile.Line[step3].ProtItem[j].Value2);
				        WriteLine("Byd_Time"+Str(j), ProtFile.Line[step3].ProtItem[j].Time);
				        WriteLine("Byd_Unit"+Str(j), ProtFile.Line[step3].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				case 3:
				if(byd_ZeroU==true)
				{
					WriteLine("[Byd_ZeroU]");
					WriteLine("Byd_LineNum",ProtFile.Line[step4].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step4].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step4][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Byd_Line"+Str(j), ProtFile.Line[step4].ProtItem[j].Name);
				        if(ProtFile.Line[step4].ProtItem[j].Enable == 255)
							WriteLine("Byd_Enable"+Str(j), 255);
						else
							WriteLine("Byd_Enable"+Str(j), 0);
				        WriteLine("Byd_Value1"+Str(j), ProtFile.Line[step4].ProtItem[j].Value1);
						WriteLine("Byd_Value2"+Str(j), ProtFile.Line[step4].ProtItem[j].Value2);
				        WriteLine("Byd_Time"+Str(j), ProtFile.Line[step4].ProtItem[j].Time);
				        WriteLine("Byd_Unit"+Str(j), ProtFile.Line[step4].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				case 4:
				if(flt1_Current==true)
				{
					WriteLine("[Flt_Current]");
					WriteLine("Flt_LineNum",ProtFile.Line[step5].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step5].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step5][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Flt_Line"+Str(j), ProtFile.Line[step5].ProtItem[j].Name);
				        if(ProtFile.Line[step5].ProtItem[j].Enable == 255)
							WriteLine("Flt_Enable"+Str(j), 255);
						else
							WriteLine("Flt_Enable"+Str(j), 0);
				        WriteLine("Flt_Value"+Str(j), ProtFile.Line[step5].ProtItem[j].Value1);
				        WriteLine("Flt_Time"+Str(j), ProtFile.Line[step5].ProtItem[j].Time);
				        WriteLine("Flt_Unit"+Str(j), ProtFile.Line[step5].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;

				case 5:
				if(flt2_Current==true)
				{
					WriteLine("[Flt_Current2]");
					WriteLine("Flt_LineNum",ProtFile.Line[step6].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step5].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step6][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Flt_Line"+Str(j), ProtFile.Line[step6].ProtItem[j].Name);
				        if(ProtFile.Line[step6].ProtItem[j].Enable == 255)
							WriteLine("Flt_Enable"+Str(j), 255);
						else
							WriteLine("Flt_Enable"+Str(j), 0);
				        WriteLine("Flt_Value"+Str(j), ProtFile.Line[step6].ProtItem[j].Value1);
				        WriteLine("Flt_Time"+Str(j), ProtFile.Line[step6].ProtItem[j].Time);
				        WriteLine("Flt_Unit"+Str(j), ProtFile.Line[step6].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				case 6:
				if(flt_3I0==true)
				{
					WriteLine("[Flt_3I0]");
					WriteLine("Flt_LineNum",ProtFile.Line[step7].LineCfg.LineNum);
				//	for(j = 0;j<ProtFile.Line[step6].LineCfg.LineNum;j++)
					for(j = 0;j<=NumberMax[step7][0];j++)
					{
					//	WriteLine("Byd_Line"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
						WriteLine("Flt_Line"+Str(j), ProtFile.Line[step7].ProtItem[j].Name);
				        if(ProtFile.Line[step7].ProtItem[j].Enable == 255)
							WriteLine("Flt_Enable"+Str(j), 255);
						else
							WriteLine("Flt_Enable"+Str(j), 0);
				        WriteLine("Flt_Value"+Str(j), ProtFile.Line[step7].ProtItem[j].Value1);
				        WriteLine("Flt_Time"+Str(j), ProtFile.Line[step7].ProtItem[j].Time);
				        WriteLine("Flt_Unit"+Str(j), ProtFile.Line[step7].ProtItem[j].Unit);
				        WriteLine("");
					}
				}
					break;
				default:
					break;
			}
			
		}
	}

	if(FileType == PROTECT_FILE)
	{
		CString filepath = mStdioFile.GetFilePath();
		filepath.Replace("\\","\\\\");
		//AfxMessageBox(filepath);
		
		WriteToIni();

		CString filepath_tmp = mStdioFile_tmp.GetFilePath();
		filepath_tmp.Replace("\\","\\\\");
		//AfxMessageBox(filepath_tmp);
		mStdioFile_tmp.Close();

		CFile::Remove(filepath);
		CFile::Rename(filepath_tmp,filepath);
	}

/*	if(FileType == PROTECT_FILE)
	{

		mStdioFile.WriteString("####-------------------------------------------------\n");
		mStdioFile.WriteString("#---------------保护配置文件-------------------------\n");
		mStdioFile.WriteString("####-------------------------------------------------\n");
		WriteLine("");

		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", ProtFile.Cfg.Version);
		WriteLine("Date", ProtFile.Cfg.CreateTime);
		WriteLine("");

		////////////////////////////写保护定制区设定
		WriteLine("[ControlW]");
		WriteLine("ControlW_Len", 2);
		WriteLine("ControlByte0", ProtFile.Cfg.ControlWByte[0]);
		WriteLine("ControlByte1", ProtFile.Cfg.ControlWByte[1]);
        WriteLine("");




		////////////////////////////写保护通用设置
        WriteLine("[prot_general]");
		WriteLine("ProtLineNum", ProtFile.Cfg.LineNum);
		WriteLine("ProtNumPerLine", ProtFile.Cfg.PNPL);
		WriteLine("FixActTime", ProtFile.Cfg.FixActTime);
		WriteLine("Switch_Remote", ProtFile.Cfg.Switch_Remote);
		WriteLine("Switch_Local", ProtFile.Cfg.Switch_Local);
		WriteLine("V_ConnectMode", ProtFile.Cfg.V_ConnectMode);
		WriteLine("");

		/////////////////////////////写Line  需要重写
		for(i=0; i<ProtFile.Cfg.LineNum; i++)
		{
			WriteLine("[prot_Line"+Str(i)+"]");

			WriteLine("Line_Switch", ProtFile.Line[i].LineCfg.Line_Switch);

			WriteLine("");


			for(int j=0; j<ProtFile.Cfg.PNPL; j++)
			{
				WriteLine("prot_Type"+Str(j), ProtFile.Line[i].ProtItem[j].Type);
				WriteLine("prot_Name"+Str(j), ProtFile.Line[i].ProtItem[j].Name);
				WriteLine("prot_Enable"+Str(j), ProtFile.Line[i].ProtItem[j].Enable);				
				WriteLine("prot_Value"+Str(j), ProtFile.Line[i].ProtItem[j].Value);
				WriteLine("prot_Time"+Str(j), ProtFile.Line[i].ProtItem[j].Time);
				WriteLine("prot_Unit"+Str(j), ProtFile.Line[i].ProtItem[j].Unit);
				WriteLine("");
			}
		}
	}
*/
	else if(FileType == SXPLC_FILE)
	{
		mStdioFile.WriteString("#-------------- 绍兴PLC配置文件 ---------------------\n");
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

		/////////////////////////////写CONFIG
		PlcFile.Cfg.UnitTotal = 1 + PlcFile.Cfg.InNum + PlcFile.Cfg.OutNum1 + PlcFile.Cfg.OutNum2;
		WriteLine("[CONFIG]");
		WriteLine("PlcEnable", PlcFile.Cfg.PlcEnable);
		WriteLine("UnitTotal", PlcFile.Cfg.UnitTotal);
		WriteLine("InNum", PlcFile.Cfg.InNum);
		WriteLine("OutNum1", PlcFile.Cfg.OutNum1);
		WriteLine("OutNum2", PlcFile.Cfg.OutNum2);
		WriteLine("RecloseCheckVol", PlcFile.Cfg.RecloseCheckVol);
		WriteLine("BztCheckVol", PlcFile.Cfg.BztCheckVol);
		WriteLine("LogicVol", PlcFile.Cfg.LogicVol);
		WriteLine("");

		/////////////////////////////写DELAYTIME
		WriteLine("[DELAYTIME]");
		WriteLine("InRecloseTime", PlcFile.Delay.InRecloseTime);
		WriteLine("OutRecloseTime", PlcFile.Delay.OutRecloseTime);
		WriteLine("InReclose2Time", PlcFile.Delay.InReclose2Time);
		WriteLine("ConnectTime", PlcFile.Delay.ConnectTime);
		WriteLine("t5", PlcFile.Delay.t5);
		WriteLine("t6", PlcFile.Delay.t6);
		WriteLine("");

		/////////////////////////////写IN_LOSTV_PROTECT
		WriteLine("[IN_LOSTV_PROTECT]");
		WriteLine("Enable1", PlcFile.LVProt.Enable1);
		WriteLine("Delay1", PlcFile.LVProt.Delay1);
		WriteLine("Value1", PlcFile.LVProt.Value1);
		WriteLine("Enable2", PlcFile.LVProt.Enable2);
		WriteLine("Delay2", PlcFile.LVProt.Delay2);
		WriteLine("Value2", PlcFile.LVProt.Value2);
		WriteLine("");

		/////////////////////////////写AUTO_BZT
		WriteLine("[AUTO_BZT_PROTECT]");
		WriteLine("Enable", false);//PlcFile.AutoBzt.Enable);
		WriteLine("Delay", PlcFile.AutoBzt.Delay);
		WriteLine("Value", PlcFile.AutoBzt.Value);
		WriteLine("");

		/////////////////////////////写PROTECT
		WriteLine("[PROTECT]");
		WriteLine("ConnectEnable", PlcFile.Bzt.ConnectEnable);
		WriteLine("");

		/////////////////////////////写CONTROL_TIME
		WriteLine("[CONTROL_TIME]");
		WriteLine("TripTime", PlcFile.CtrlTime.TripTime);
		WriteLine("CloseTime", PlcFile.CtrlTime.CloseTime);
		WriteLine("");

		/////////////////////////////写UNIT
		for(i=1; i<PlcFile.Cfg.UnitTotal; i++)
		{
			WriteLine("[UNIT_" + Str(i) + "]");
			WriteLine("RecloseEnable", PlcFile.Reclose.ReClose[i]);
			WriteLine("CheckVoltage", PlcFile.Reclose.CheckVol[i]);
			WriteLine("RecloseDelay", PlcFile.Reclose.RecloseDelay[i]);
			WriteLine("");
		}
	}
	else if(FileType == ZJPLC_FILE)
	{
		mStdioFile.WriteString("#-------------- 诸暨PLC配置文件 ---------------------\n");
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");

		/////////////////////////////写CONFIG
		WriteLine("[CONFIG]");
		WriteLine("PlcEnable", ZjPlcFile.Cfg.PlcEnable);
		WriteLine("UnitTotal", ZjPlcFile.Cfg.UnitTotal);
		WriteLine("LogicVol", ZjPlcFile.Cfg.LogicVol);
		WriteLine("");

		/////////////////////////////写DELAYTIME
		WriteLine("[DELAYTIME]");
		WriteLine("InRecloseTime", ZjPlcFile.Delay.InRecloseTime);
		WriteLine("PlcTime", ZjPlcFile.Delay.PlcTime);
		WriteLine("");

		/////////////////////////////写备投
		WriteLine("[BZT_CFG]");
		WriteLine("Enable1", ZjPlcFile.Bzt[0].Enable);
		WriteLine("Enable2", ZjPlcFile.Bzt[1].Enable);

		/////////////////////////////写UNIT
		for(i=0; i<ZjPlcFile.Cfg.UnitTotal; i++)
		{
			WriteLine("[UNIT_" + Str(i) + "]");
			WriteLine("RecloseEnable", ZjPlcFile.Reclose.ReClose[i]);
			WriteLine("");
		}
	}
	else if(FileType == JZSLG_FILE)
	{
		mStdioFile.WriteString("######-------------- 集中式PZK-36B逻辑关系配置参数 ---------------------\n");
		//WriteLine("");
		
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");
		
		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", ProtFile.Cfg.Version);
		WriteLine("Date", ProtFile.Cfg.CreateTime);
		WriteLine("");
		
		/////////////////////////////写PLC_ENABLE
		WriteLine("[PLC_ENABLE]");
		WriteLine("PLCEnable", ProtFile.Cfg.isuseful);
		WriteLine("");

		/////////////////////////////写LIMIT_VALUE
		WriteLine("[LIMIT_VALUE]");
		WriteLine("NoVoltageValue", ProtFile.Cfg.VOGE);
		WriteLine("NoCurrentValue", ProtFile.Cfg.CURRENT);
		WriteLine("");

		/////////////////////////////写MODE_TYPE
		WriteLine("[MODE_TYPE]");
		WriteLine("ModeType", ProtFile.Cfg.modetype);
		WriteLine("OutNum1", ProtFile.Cfg.OutNum1);
		WriteLine("OutNum2", ProtFile.Cfg.OutNum2);
		WriteLine("");

		/////////////////////////////写PLC_TIME
		WriteLine("[PLC_TIME]");
		WriteLine("Jx1CHZTime", ProtFile.Cfg.atme.onetime);
		WriteLine("Jx2CHZTime", ProtFile.Cfg.atme.twotime);
		WriteLine("CxCHZTime",ProtFile.Cfg.atme.outtime);
		WriteLine("MLBZTTime", pzkml.time);
		WriteLine("");

		/////////////////////////////写JXCHZ_ENABLE
		WriteLine("[JXCHZ_ENABLE]");
		WriteLine("Ijx1CHZEnable", pzkjx[1][1].yesorno);
		WriteLine("Ijx2CHZEnable", pzkjx[1][2].yesorno);
		WriteLine("IIjx1CHZEnable", pzkjx[2][1].yesorno);
		WriteLine("IIjx2CHZEnable", pzkjx[2][2].yesorno);
		WriteLine("MLBZTEnable", pzkml.yesorno);
		WriteLine("");

		/////////////////////////////写CXCHZ_ENABLE
		WriteLine("[CXCHZ_ENABLE]");
		CString str5;
		for (i=1;i<4;i++)
		{
			for (int j=1;j<12;j++)
			{
				if (pzkcx[i][j].istrue==1)
				{
					str1.Format("1段出线%d",j);
					if (pzkcx[i][j].name==str1)
					{
						str2.Format("CXCHZEnable%d",j-1);
						WriteLine(str2, pzkcx[i][j].yesorno);
					}
					str1.Format("2段出线%d",j);
					if (pzkcx[i][j].name==str1)
					{
						str2.Format("CXCHZEnable%d",j+ProtFile.Cfg.OutNum1-1);
						WriteLine(str2, pzkcx[i][j].yesorno);
					}
				}
			}
		}
	}
	else if(FileType == MLPLC_FILE)
	{
		mStdioFile.WriteString("######-------------- 母联式PZK-36B逻辑关系配置参数 ---------------------\n");
		//WriteLine("");
		
		/////////////////////////////写FILENAME
		WriteLine("[FILENAME]");
		WriteLine("FileName", GetFileNameFromType(FileType));
		WriteLine("");
		
		/////////////////////////////写INFO
		WriteLine("[INFO]");
		WriteLine("Version", ProtFile.Cfg.Version);
		WriteLine("Date", ProtFile.Cfg.CreateTime);
		WriteLine("");
		
		/////////////////////////////写PLC_ENABLE
		WriteLine("[PLC_ENABLE]");
		WriteLine("PLCEnable", ProtFile.Cfg.isuseful);
		if(MLValid == true)
		    WriteLine("MLEnable", 1);
		else
			WriteLine("MLEnable", 0);
		WriteLine("");

		/////////////////////////////写LIMIT_VALUE
		WriteLine("[LIMIT_VALUE]");
		WriteLine("NoVoltageValue", ProtFile.Cfg.VOGE);
		WriteLine("NoCurrentValue", ProtFile.Cfg.CURRENT);
		WriteLine("");

		/////////////////////////////写MODE_TYPE
		WriteLine("[MODE_TYPE]");
		WriteLine("ModeType", ProtFile.Cfg.modetype);
		WriteLine("OutNum1", ProtFile.Cfg.OutNum1);
		WriteLine("OutNum2", ProtFile.Cfg.OutNum2);
		WriteLine("");

		/////////////////////////////写PLC_TIME
		WriteLine("[PLC_TIME]");
		WriteLine("Jx1CHZTime", ProtFile.Cfg.atme.onetime);
		WriteLine("Jx2CHZTime", ProtFile.Cfg.atme.twotime);
		WriteLine("CxCHZTime",ProtFile.Cfg.atme.outtime);
		WriteLine("MLBZTTime",pzkml.time);
		WriteLine("");

		/////////////////////////////写JXCHZ_ENABLE
		WriteLine("[JXCHZ_ENABLE]");
		WriteLine("Ijx1CHZEnable", pzkjx[1][1].yesorno);
		WriteLine("Ijx2CHZEnable", pzkjx[1][2].yesorno);
		WriteLine("IIjx1CHZEnable", pzkjx[2][1].yesorno);
		WriteLine("IIjx2CHZEnable", pzkjx[2][2].yesorno);
		WriteLine("MLBZTEnable", pzkml.yesorno);
		WriteLine("");

		/////////////////////////////写CXCHZ_ENABLE
		WriteLine("[CXCHZ_ENABLE]");
		CString str5;
		for (i=1;i<4;i++)
		{
			for (int j=1;j<12;j++)
			{
				if (pzkcx[i][j].istrue==1)
				{
					str1.Format("1段出线%d",j);
					if (pzkcx[i][j].name==str1)
					{
						str2.Format("CXCHZEnable%d",j-1);
						WriteLine(str2, pzkcx[i][j].yesorno);
					}
					str1.Format("2段出线%d",j);
					if (pzkcx[i][j].name==str1)
					{
						str2.Format("CXCHZEnable%d",j+ProtFile.Cfg.OutNum1-1);
						WriteLine(str2, pzkcx[i][j].yesorno);
					}
				}
			}
		}
	}
	EverModified = false;
	mStdioFile.Close();
	

	return true;
}

bool CReadPzkIni::ReleaseBuf()
{
	if (!IniFileOpened)
		return false;

	return true;
}

bool CReadPzkIni::CloseFile()
{
	if (!IniFileOpened)
		return true;
	if (EverModified)
	{
		int i = AfxMessageBox("配置文件已被修改，在退出前确定要存盘吗?",MB_YESNOCANCEL);
		if(i == IDYES)
			SaveToIni();
		else if(i== IDCANCEL)
			return false;
		//else if(i == IDNO)
		//	AfxMessageBox("no");
		//ReadFromIntFile();
	}
//	if(IniFileName != "")
//		mStdioFile.Close();
	IniFileName = "";
	EverModified = false;
	ReleaseBuf();
	IniFileOpened = false;

	return true;
}

CString CReadPzkIni::GetFileName()
{
	return IniFileName;
}

bool CReadPzkIni::NewFile()
{
	if(IniFileOpened)
		CloseFile();
	IniFileName = "";
	IniFileOpened = true;
	EverModified = false;

	mPzk300NormalCfg.num = 0;
	mPzk300ProCfg.num = 0;
	return true;

}

void CReadPzkIni::WriteLine(CString str="")
{
	mStdioFile.WriteString(str+"\n");//+"\r");
}

void CReadPzkIni::WriteLine(int mint = 0)
{
	mStdioFile.WriteString(Str(mint)+"\n");//+"\r");
}

void CReadPzkIni::WriteLine(CString KeyName,int KeyVal)
{
	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+";\n");//\r");
}

void CReadPzkIni::WriteLine(CString KeyName,float KeyVal)
{
	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+";\n");//\r");
}

void CReadPzkIni::WriteLine(CString KeyName,double KeyVal)
{
	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+";\n");//\r");
}

void CReadPzkIni::WriteLine(CString KeyName,CString KeyVal)
{
	mStdioFile.WriteString(KeyName+"="+KeyVal+";\n");//\r");
}

void CReadPzkIni::WriteLine(CString KeyName, char *KeyVal)
{
	CString str;
	str.Format("%s", KeyVal);
	mStdioFile.WriteString(KeyName+"="+str+";\n");
}

void CReadPzkIni::WriteLine(CString KeyName,bool KeyVal)
{
	if(KeyVal)
		mStdioFile.WriteString(KeyName+"=yes;\n");//\r");
	else
		mStdioFile.WriteString(KeyName+"=no;\n");//\r");
}

void CReadPzkIni::WriteLine(CString KeyName,int KeyVal,CString str)
{
	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+";  "+"#"+str+"\n");//\r");
}
void CReadPzkIni::WriteLine(CString KeyName,float KeyVal,CString str)
{
//	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+"%"+str+";\n");//\r");
	mStdioFile.WriteString(KeyName+"="+Str(KeyVal)+";  "+"#"+str+"\n");//\r");
}
void CReadPzkIni::WriteLine(CString KeyName,CString str1,CString str2)
{
	mStdioFile.WriteString(KeyName+"="+str1+";  "+"#"+str2+"\n");//\r");
}
/*
UINT CReadPzkIni::WatchFileEditOutWhere(LPVOID para)
{
	SHFILEINFO shFinfo;
	BOOL bFind;
	CFileFind find;
	CReadPzkIni *pthis = (CReadPzkIni *)para;
	while(pthis->IniFileOpened)
	{
		break;
	}
	return TRUE;
}
*/
bool CReadPzkIni::GetPlcenable(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;
	if(KeyName == "PLCEnable")
	{
		ProtFile.Cfg.isuseful = myatoi(KeyStr);
	}
	if(KeyName == "MLEnable")
	{
		MLValid = myatoi(KeyStr);
	}
	if(KeyName == "")
	return true;

}
bool CReadPzkIni::GetLimitvalue(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;
	if(KeyName == "NoVoltageValue")
		ProtFile.Cfg.VOGE = myatoi(KeyStr);
	else if (KeyName == "NoCurrentValue")
	{
		ProtFile.Cfg.CURRENT = myatoi(KeyStr);
	}
	return true;
}
CString str1111(int i)
{
	CString str;
	str.Format("outnum = %d",i);
	return str;
}
bool CReadPzkIni::GetModetype(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;
	if(KeyName == "ModeType")
		ProtFile.Cfg.modetype = myatoi(KeyStr);
	else if (KeyName == "OutNum1")
	{
		ProtFile.Cfg.OutNum1 = myatoi(KeyStr);
//		AfxMessageBox(str1111(ProtFile.Cfg.OutNum1));
	}
	else if (KeyName == "OutNum2")
	{
		ProtFile.Cfg.OutNum2 = myatoi(KeyStr);
//		AfxMessageBox(str1111(ProtFile.Cfg.OutNum2));
	}
	return true;
}
bool CReadPzkIni::GetPlctime(CString KeyName, CString KeyStr)
{
	if(!IniFileOpened)
		return false;
	if (KeyName == "Jx1CHZTime")			
		ProtFile.Cfg.atme.onetime= myatoi(KeyStr);
	else if (KeyName == "Jx2CHZTime")
		ProtFile.Cfg.atme.twotime= myatoi(KeyStr);
	else if (KeyName == "CxCHZTime")
		ProtFile.Cfg.atme.outtime= myatoi(KeyStr);
	else if (KeyName == "MLBZTTime")
		pzkml.time = myatoi(KeyStr);

	return true;
}
bool CReadPzkIni::GetJxchz(CString KeyName, CString KeyStr)
{
	int j;
	if(!IniFileOpened)
		return false;
	CString str1,str2,str3;
	for(j=1;j<9;j++)
	{
		str1.Format("Ijx%dCHZEnable",j);
		str2.Format("IIjx%dCHZEnable",j);
		str3.Format("MLBZTEnable");
		if (KeyName == str1)
		{
			pzkjx[1][j].istrue = 1;
			pzkjx[1][j].yesorno = myatoi(KeyStr);
		}
		else if (KeyName == str2)
		{
			pzkjx[2][j].istrue = 1;
			pzkjx[2][j].yesorno = myatoi(KeyStr);
		}
		//
        
		else if (KeyName == str3)
		{
			pzkml.istrue = 1;
			pzkml.yesorno = myatoi(KeyStr);
		}
	}
	return true;
}
bool CReadPzkIni::GetCxchz(CString KeyName, CString KeyStr)
{
	int j=1;
	int i=1;
	if(!IniFileOpened)
		return false;
	CString str1,str2,str3;
	for (j=1;j<30;j++)
	{
		str2.Format("CXCHZEnable%d",j-1);
		if ((KeyName == str2)&&(j<=ProtFile.Cfg.OutNum1))
		{
			pzkcx[1][j].yesorno = myatoi(KeyStr);
			str1.Format("1段出线%d",j);
			pzkcx[1][j].name = str1;
			pzkcx[1][j].istrue = 1;
			j++;
		}
		else if ((KeyName == str2)&&(j<=(ProtFile.Cfg.OutNum1+ProtFile.Cfg.OutNum2))&&(j>ProtFile.Cfg.OutNum1))
		{
			pzkcx[2][j-ProtFile.Cfg.OutNum1].yesorno = myatoi(KeyStr);
			str1.Format("2段出线%d",j-ProtFile.Cfg.OutNum1);
			pzkcx[2][j-ProtFile.Cfg.OutNum1].name = str1;
			pzkcx[2][j-ProtFile.Cfg.OutNum1].istrue = 1;
			j++;
		}
	}
	return true;
}
