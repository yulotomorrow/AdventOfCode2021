#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <vector>
using namespace std;


void PreProcess(array<int, 14> xParam, array<int, 14> yParam, array<bool, 14> zParam)
{
	array<bool, 14> xResult = { false };
	array<int, 14> yResult = { };
	int itr = 0;
	string result = "99999999999999";
	long long max = 0;
	int leverageCount = 0;
	for (int i = 0; i < 14; ++i) 
	{
		
		if (xParam[i] > 9)
		{
			xResult[i] = true;
			itr = i;
			if (i > 0)
			{
				
				yResult[i - 1] = yParam[i - 1] + (result[i - 1] - '0');
			}
			//	result[i - 1] = '9'; // Can be anything, so choose the max
			++leverageCount; // Need a test run to see if leverage larger than decrease (true in zParams), if larger basically unsolvable,
			// if equal all the others should be 0, if smaller, put the largest digits to true(random digit)
			// here we already did a lot of manual stuff so just directly see it's equal
		}
		else 
		{
			for (int j = result[itr] - '0'; j > 0; --j)
			{
				if (yParam[itr] + j + xParam[i] == result[i] - '0')
				{
					result[itr] = j + '0';
				}
			}
			--itr;
		}
	}
}

int main()
{
	array<int, 14> xParam = {14, 13, 13, 12, -12, 12, -2, -11, 13, 14, 0, -12, -13, -6};
	array<int, 14> yParam = {8, 8, 3, 10, 8, 8, 8, 5, 9, 3, 4, 9, 2, 7};
	array<bool, 14> zParam = {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
}

