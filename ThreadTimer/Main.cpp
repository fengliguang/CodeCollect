#include "Timer.h"

void CALLBACK TimerProc(void * p)
{
	int i = *((int*)p);
	cout << i << endl;
}

int main(int argc, char **argv)
{ 
	CTimer timer;

	int i = 10;
	int *p = &i;

	timer.RegisterHandler(TimerProc, p);
	timer.SetTimerInterval(1000);
	timer.Start();

	getchar();

	timer.Cancel();
	system("pause");
	return 0;
}