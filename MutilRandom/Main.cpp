#include "CreateRandom.h"

int main(int argc, char **argv)
{
	CCreateRandom * pCreateArray[1024] = {NULL};

	char strName[32];
	for (int i = 0; i < 10; i++)
	{
		sprintf(strName, "%03d", i);
		pCreateArray[i] = new CCreateRandom(strName);
		pCreateArray[i]->StartThread(i);
	}

	getchar();

	for (int i = 0; i < 10; i++)
	{
		delete pCreateArray[i];
		pCreateArray[i] = NULL;
	}

	system("pause");
	return 0;
}