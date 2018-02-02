// ReadPzkIni.h: interface for the CReadPzkIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READPZKINI_H__FBF54A42_068A_4F1B_B86B_C778EA8C3417__INCLUDED_)
#define AFX_READPZKINI_H__FBF54A42_068A_4F1B_B86B_C778EA8C3417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniStru.h"
#include "MyStdioFile.h"

extern bool lizhen;
class CReadPzkIni
{
public:
	CReadPzkIni();
	CReadPzkIni(CString FileName);
	virtual ~CReadPzkIni();

public:

	bool IniFileOpened;

	bool EverModified;
	bool MLValid;
	Pzk300NormalCfgStru mPzk300NormalCfg;
	Pzk300ProCfgStru mPzk300ProCfg;

	PlcStru PlcFile;
	pzk36bplc pzkjx[4][4];
	pzk36bplc pzkcx[4][12];
	pzk36bplc pzkcxls[4][12];
	pzk36bmlplc pzkml;
	ProtCfgStru ProtFile;
	ZjPlcStru ZjPlcFile;
	int FileType;
	int LineNum;

	/*********绍兴集中式**********/
	SXJZSCfgStru SXJZSFile;
	SXJZSCfgStru SXJZSFileTemp;

	/***********看门狗*****************/
	KMGCfgStru KMGFile;
	KMGCfgStru KMGFileTemp;

	/**********绍兴液晶***************/
	SXYJCfgStru SXYJFile;
	SXYJCfgStru SXYJFileTemp;

	/***********分段狗*****************/
	FDGCfgStru FDGFile;
	FDGCfgStru FDGFileTemp;

protected:
	CString IniFileName;		// 当前打开的配置文件名
	CMyStdioFile mStdioFile;
	CMyStdioFile mStdioFile_tmp;


public:
	bool OpenFile(CString FileName);
	bool OpenTempFile(CString FileName);
	bool NewFile();
	bool ReleaseBuf();
	bool CloseFile();
	CString GetFileName();

private:
	bool ReadFromIntFile();
	bool WriteToIni();// lz
	int	 GetSecNo(CString SectionStr,int *CurNum);
	bool Get_Infomation(CString KeyName,CString KeyStr);
	bool Get300Cfg(CString KeyName,CString KeyStr,int CurNum);
//	void ReadUnionData(Pzk300UnionStru *val, int datatype, CString KeyStr);
	bool Get300Pro(CString KeyName,CString KeyStr,int CurNum);

	bool GetFileName(CString KeyName, CString KeyStr);
	bool GetSecInfo(CString KeyName, CString KeyStr);
	bool SetSecInfo(CString KeyName, CString *KeyStr);//lz
	bool GetSecLine(CString KeyName, CString KeyStr, int CurNum);
	bool SetSecLine(CString KeyName, CString *KeyStr, int CurNum); //lz
	bool GetControlW(CString KeyName, CString KeyStr);
	bool SetControlW(CString KeyName, CString *KeyStr);// lz
	bool Getprot_general(CString KeyName, CString KeyStr);
	bool Setprot_general(CString KeyName, CString *KeyStr);// lz
	bool Write_to(CString LineString,CString KeyName, CString KeyStr);//lz
	bool Write_to(CString LineString,CString KeyName);//lz
	bool GetConfig(CString KeyName, CString KeyStr);
	bool GetDelayTime(CString KeyName, CString KeyStr);
	bool GetLVProt(CString KeyName, CString KeyStr);
	bool GetBzt(CString KeyName, CString KeyStr);
	bool GetCtrl(CString KeyName, CString KeyStr);
	bool GetUnit(CString KeyName, CString KeyStr, int CurNum);
	bool GetAutoBzt(CString KeyName, CString KeyStr);

	bool GetZjConfig(CString KeyName, CString KeyStr);
	bool GetZjDelayTime(CString KeyName, CString KeyStr);
	bool GetPlcenable(CString KeyName, CString KeyStr);
	bool GetLimitvalue(CString KeyName, CString KeyStr);
	bool GetModetype(CString KeyName, CString KeyStr);
	bool GetPlctime(CString KeyName, CString KeyStr);
	bool GetJxchz(CString KeyName, CString KeyStr);
	bool GetCxchz(CString KeyName, CString KeyStr);
	bool Getprot_select(CString KeyName,CString KeyStr);//绍兴集中式保护
	bool GetZjUnit(CString KeyName, CString KeyStr, int CurNum);
	bool CReadPzkIni::GetZjBzt(CString KeyName, CString KeyStr);

	CString WriteSXJZSNote(int );//写绍兴集中式注释

public:
	bool SaveToIni();
	bool SaveToIni(CString FileName);
	bool SaveToTempIni(CString FileName);

protected:
	void WriteLine(CString str);
	void WriteLine(int mint);
	void WriteLine(CString KeyName,int KeyVal);
	void WriteLine(CString KeyName,float KeyVal);
	void WriteLine(CString KeyName,double KeyVal);
	void WriteLine(CString KeyName,CString KeyVal);
	void WriteLine(CString KeyName, char *KeyVal);
	void WriteLine(CString KeyName,bool KeyVal);
	void WriteLine(CString KeyName,int KeyVal,CString str);
	void WriteLine(CString KeyName,float KeyVal,CString str);
	void WriteLine(CString KeyName,CString str1,CString str2);

};

#endif // !defined(AFX_READPZKINI_H__FBF54A42_068A_4F1B_B86B_C778EA8C3417__INCLUDED_)
