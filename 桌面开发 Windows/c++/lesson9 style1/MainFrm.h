
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

// �����û���Ϣ user message
#define UM_PROGRESS		WM_USER		// �ڴ�������ʱ��ȡ״̬���еĽ�������С

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CToolBar          m_newToolBar;		// ������
	CProgressCtrl     m_progress;		// ������
public:
	CStatusBar        m_wndStatusBar;	// ״̬��

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon[3];
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTest();
	afx_msg void OnViewNewtool();
	afx_msg void OnUpdateViewNewtool(CCmdUI *pCmdUI);
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);		// �ֶ�����û���Ϣ��Ӧ����
	afx_msg void OnPaint();
};


