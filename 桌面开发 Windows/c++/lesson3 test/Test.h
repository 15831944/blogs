
// Test.h : Test 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CTestApp:
// 有关此类的实现，请参阅 Test.cpp
// 应用程序类
class CTestApp : public CWinApp
{
public:
	CTestApp();


// 重写
public:
	virtual BOOL InitInstance();	// 初始化实例

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()			// 声明消息映射 wanghuiyong
};

extern CTestApp theApp;
