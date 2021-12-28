#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// (x1 + x2) * (x1 - x2 + 1) / 2
// Repeat counted some velocity need change

map<int, int> PossibleValueX(pair<int, int> xRange)
{
	int timeBound = ceil(sqrt(xRange.second * 2)) + 2;
	map<int, int> timeNCaseNum = {};
	for (int t = 1; t < timeBound; ++t)
	{
		int caseNum = 0;
		int x = 1;
		while ((2 * x + 1 - t) * t / 2 <= xRange.second)
		{
			if ((2 * x + 1 - t) * t / 2 >= xRange.first && (x + 1 - t) >= 0)
				++caseNum;
			++x;
		}
		timeNCaseNum.insert({ t, caseNum });
	}
	return timeNCaseNum;
}

map<int, int> PossibleValueY(pair<int, int> yRange)
{
	map<int, int> timeNCaseNum = {};
	for (int vy = -abs(yRange.first); vy < abs(yRange.first); ++vy)
	{
		int t = 1;
		while ((2 * vy + 1 - t) * t / 2 >= yRange.first)
		{
			if ((2 * vy + 1 - t) * t / 2 <= yRange.second)
			{
				if (timeNCaseNum.find(t) == timeNCaseNum.end())
					timeNCaseNum.insert({ t, 1 });
				else
					++timeNCaseNum[t];
				
			}
			++t;
		}	
	}
	return timeNCaseNum;
}

vector<int> PossibleLongerX(pair<int, int> xRange)
{
	int vx = 1;
	vector<int> zeroVCase = {};
	while ((vx + 1) * vx / 2 <= xRange.second)
	{
		if ((vx + 1) * vx / 2 >= xRange.first)
			zeroVCase.push_back(vx + 1);
		++vx;
	}
	return zeroVCase;
}

int main()
{
	pair<int, int> xRange = { 20, 30 };
	pair<int, int> yRange = { -10, -5 };

	map<int, int> xList = PossibleValueX(xRange);
	map<int, int> yList = PossibleValueY(yRange);
	vector<int> zeroX = PossibleLongerX(xRange);

	int result = 0;
	for(auto& itrX : xList)
	{
		for (auto& itrY : yList)
		{
			if (itrY.first == itrX.first)
			{
				result += itrY.second * itrX.second;
			}
			else if (itrY.first > itrX.first)
				break;
		}
	}

	for (auto& itrX2 : zeroX)
	{
		if (xList.find(itrX2) != xList.end()) 
		{
			for (auto& itrY : yList)
			{
				if (itrY.first > itrX2)
				{
					result += itrY.second;
				}
			}
		}
	}

	cout << result << "\n";
}
