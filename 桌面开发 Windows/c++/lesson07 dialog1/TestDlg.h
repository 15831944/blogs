#pragma once
#include "afxwin.h"


// CTestDlg 对话框

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };	// 建立对象和资源的关联

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
private:
	CButton m_btn;
	bool m_blsCreate;
public:
	afx_msg void OnClickedNumber1();
private:
	int num1;
public:
	int m_num1;
	int m_num2;
	int m_num3;
	CEdit m_Edit1;
	CEdit m_Edit2;
	CEdit m_Edit3;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
