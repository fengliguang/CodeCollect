#pragma once
#include "Common.h"
#include <Windows.h>

class CFirstDemoWnd : public CWindowWnd, public INotifyUI
{
public:
	 CFirstDemoWnd();
	~CFirstDemoWnd();
public:
	LPCTSTR GetWindowClassName() const;
	UINT    GetClassStyle() const;
	void    OnFinalMessage(HWND hWnd);
	void    Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CPaintManagerUI m_pm;
};