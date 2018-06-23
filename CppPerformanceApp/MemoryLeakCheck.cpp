#include "MemoryLeakCheck.h"

void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

namespace AutoCheck
{
	class CAutoRun
	{
	public:
		CAutoRun()
		{
			EnableMemLeakCheck();
		}
		~CAutoRun()
		{
		}
	};
	static CAutoRun s_AutoRun;
}