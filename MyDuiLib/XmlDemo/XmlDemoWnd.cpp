#include "XmlDemoWnd.h"

CXmlDemoWnd::CXmlDemoWnd()
{

}

CXmlDemoWnd::~CXmlDemoWnd()
{

}

LPCTSTR CXmlDemoWnd::GetWindowClassName() const
{ 
	return _T("UIMainFrame"); 
}

UINT CXmlDemoWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CXmlDemoWnd::OnFinalMessage(HWND hWnd) 
{ 
	delete this; 
}

void CXmlDemoWnd::Notify(TNotifyUI& msg)
{
	TCHAR wstrBuffer[1024];    
	wsprintf(wstrBuffer, L"Notify = %s, Sender = %s\n", msg.sType.GetData(), msg.pSender->GetName().GetData());
	OutputDebugString(wstrBuffer);

	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender->GetName() == _T("btnMax") ) 
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
			return;
		}
		else if( msg.pSender->GetName() == _T("btnMin") ) 
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if( msg.pSender->GetName() == _T("btnClose") ) 
		{
			Close();
		}
	}
}

LRESULT CXmlDemoWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR wstrBuffer[1024];    
	wsprintf(wstrBuffer, L"HandleMessage = %u\n", uMsg);
	OutputDebugString(wstrBuffer);    

	if(WM_CREATE == uMsg) 
	{
		OutputDebugString(L"HandleMessage:WM_CREATE\n");

		m_pm.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("XmlDemo.xml"), (UINT)0, NULL, &m_pm);
		ASSERT(pRoot && "Failed to parse XmlDemo.xml");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		return 0;
	}
	else if(WM_DESTROY == uMsg) 
	{
		OutputDebugString(L"HandleMessage:WM_DESTROY\n");
		::PostQuitMessage(0);
	}
	else if(WM_NCACTIVATE == uMsg)
	{
		if( !::IsIconic(m_hWnd)) 
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if(WM_NCCALCSIZE == uMsg) //不使用系统的标题栏和边框这些非客户区绘制
	{
		return 0;
	}
	else if(WM_NCPAINT == uMsg)
	{
		return 0;
	}

	LRESULT lRes = 0;
	if(m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}