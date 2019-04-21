#include "XmlDemoWnd.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	CXmlDemoWnd* pFrame = new CXmlDemoWnd();
	if( pFrame == NULL ) return 0;

	//��Ҫϵͳ�İ�ť�����UI_WNDSTYLE_CONTAINER
	pFrame->Create(NULL, _T("����XML"), UI_WNDSTYLE_CONTAINER, UI_WNDSTYLE_EX_FRAME, 0, 0, 300, 500);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();

	return 0;
}