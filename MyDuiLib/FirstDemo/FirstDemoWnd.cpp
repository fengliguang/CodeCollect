#include "FirstDemoWnd.h"

CFirstDemoWnd::CFirstDemoWnd()
{

}

CFirstDemoWnd::~CFirstDemoWnd()
{

}

LPCTSTR CFirstDemoWnd::GetWindowClassName() const
{ 
	return _T("UIMainFrame"); 
}

UINT CFirstDemoWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CFirstDemoWnd::OnFinalMessage(HWND hWnd) 
{ 
	delete this; 
}

void CFirstDemoWnd::Notify(TNotifyUI& msg)
{
	TCHAR wstrBuffer[1024];    
	wsprintf(wstrBuffer, L"Notify = %s, Sender = %s\n", msg.sType.GetData(), msg.pSender->GetName().GetData());
	OutputDebugString(wstrBuffer);

	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender->GetName() == _T("closebtn") ) 
		{
			Close();
		}
	}
}

LRESULT CFirstDemoWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR wstrBuffer[1024];    
	wsprintf(wstrBuffer, L"HandleMessage = %u\n", uMsg);
	OutputDebugString(wstrBuffer);    

	if(WM_CREATE == uMsg) 
	{
		OutputDebugString(L"HandleMessage:WM_CREATE\n");
		m_pm.Init(m_hWnd);
		CControlUI *pButton = new CButtonUI;
		pButton->SetName(_T("closebtn"));
		pButton->SetBkColor(0xFFFF0000);
		m_pm.AttachDialog(pButton);
		m_pm.AddNotifier(this);
		return 0;
	}
	else if(WM_DESTROY == uMsg) 
	{
		OutputDebugString(L"HandleMessage:WM_DESTROY\n");
		::PostQuitMessage(0);
	}
	LRESULT lRes = 0;
	if(m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}