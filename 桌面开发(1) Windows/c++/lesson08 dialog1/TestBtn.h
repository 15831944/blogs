#pragma once


// CTestBtn

class CTestBtn : public CButton
{
	DECLARE_DYNAMIC(CTestBtn)

public:
	CTestBtn();
	virtual ~CTestBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CTestBtn *m_pBtn;	// 存储另一个按钮对象的地址
};


