
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

// 定义用户消息 user message
#define UM_PROGRESS		WM_USER		// 在创建窗口时获取状态栏中的进度栏大小

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CToolBar          m_newToolBar;		// 工具栏
	CProgressCtrl     m_progress;		// 进度栏
public:
	CStatusBar        m_wndStatusBar;	// 状态栏

// 生成的消息映射函数
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
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);		// 手动添加用户消息响应函数
	afx_msg void OnPaint();
};


