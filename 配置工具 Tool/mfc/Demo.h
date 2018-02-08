// Demo.h : main header file for the DEMO application

#if !defined(AFX_DEMO_H__88616122_4218_48A0_9752_26D0146598CB__INCLUDED_)
#define AFX_DEMO_H__88616122_4218_48A0_9752_26D0146598CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif					// _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"				// main symbols
#include "Usb.h"
#include "uftp.h"					// û������ļ� wanghuiyong
#include "FocusScrollListCtrl.h"

// #define __SUPERMODE		1		// ����Աģʽ wanghuiyong

/* ȫ�ֺ������� */
extern void SendToUsb(LinuxCmdStru1 *LinuxCmd, int Priority, int wait_flag, int timeout);
extern BOOL SendToUsb(LinuxCmdStru1 *LinuxCmd, int wait_flag,bool bNeedRequest);
extern BOOL SendToUsb(char *buf, int len, int wait_flag, bool bNeedRequest);

/* �û��Զ�����Ϣ */
const UINT SHOW_TEXT_AT_TOOLBAR = (WM_USER + 1);	// ���ݷָ�ڵ��ڹ������ָ���λ��
const UINT FILE_COPY_PROGRESS   = (WM_USER + 2);	// �ļ��������̶�̬�ı�״̬���Ͻ���������
const UINT UPLOAD_PROGRESS		= (WM_USER + 3);	// ���ؽ���
const UINT DOWNLOAD_PROGRESS	= (WM_USER + 4);	// ���ؽ���
const UINT RETURN_PRESEL_ITEM   = (WM_USER + 100);
const UINT DELETE_NEW_NODE      = (WM_USER + 101);
const UINT SAVE_FILE            = (WM_USER + 102);
const UINT UNSAVE_FILE          = (WM_USER + 103);
const UINT SET_FRAME_WINTEXT    = (WM_USER + 104);
const UINT XTWM_OUTBAR_NOTIFY   = (WM_USER + 1018);

/* ȫ�ֱ������� */
extern CString		TitleName;
extern CReadPzkIni	mPzkIni;
extern CMainFrame	*pFrame;

/* ȫ�ֱ������� */
const CString ProtFileName   = "mzkprot.ini";
const CString PlcFileName    = "sx_plc.ini";
const CString ZjPlcFileName  = "zj_plc.ini";
const CString JZSPlcFileName = "pzk36b_plc.ini";
const CString mlPlcFileName  = "pzk36b_mlplc.ini";
const CString FaultFileName  = "fault.ini";
const CString SxjzsFileName  = "protplc.ini";		//���˼���ʽ 2015.7.15
const CString KMGFileName    = "kmgprotflt.ini";
const CString SXYJFileName   = "sxyj.ini";

// CDemoApp:
// See Demo.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp();

public:
	// ֻ����������Ա����
	usb_t       m_USBDevice;
    HUFTP       m_uFtp;

public:
	BOOL OpenUsb();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define UPDATE_WRITE FALSE
#define UPDATE_READ	 TRUE
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_H__88616122_4218_48A0_9752_26D0146598CB__INCLUDED_)
