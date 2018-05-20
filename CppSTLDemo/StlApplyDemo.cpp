#include "StlApplyDemo.h"
#include <math.h>

void CStlApplyDemo::DeleteTheRepeatElevment(bool bRun)
{
	if (!bRun) return;

	vector<double> vecTemp;
	vecTemp.push_back(10.1234);
	vecTemp.push_back(12.2345);
	vecTemp.push_back(14.3456);
	vecTemp.push_back(11.4567);
	vecTemp.push_back(12.2345);
	vecTemp.push_back(10.1234);
	vecTemp.push_back(16.5678);

	for (unsigned int i = 0; i < vecTemp.size(); i++)
	{
		printf("%02d:%7.4f\n", i, vecTemp[i]);
	}

	printf("sort.\n");

	sort(vecTemp.begin(), vecTemp.end());

	int n = 0;
	for (vector<double>::iterator it = vecTemp.begin(); it != vecTemp.end(); it++ )
	{
		printf("%02d:%7.4f\n", n++, *it);
	}

	printf("delete the repeat one.\n");

	double f8LastTemp = -9999;
	for (vector<double>::iterator it = vecTemp.begin(); it != vecTemp.end();)
	{
		if (fabs(f8LastTemp - *it) < 0.000001 )
		{
			printf("Find and erase:%7.4f\n", *it);
			it = vecTemp.erase(it);
		}
		else
		{
			f8LastTemp = *it;
			it++;
		}
	}

	for (unsigned int i = 0; i < vecTemp.size(); i++)
	{
		printf("%02d:%7.4f\n", i, vecTemp[i]);
	}
}
