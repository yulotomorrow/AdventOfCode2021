#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

// (x1 + x2) * (x1 - x2 + 1) / 2
// Repeat counted some velocity need change

array<map<int, int>, 2> PossibleValueX(pair<int, int> xRange)
{
	int timeBound = ceil(sqrt(xRange.second * 2)) + 2;
	map<int, int> timeNCaseNum = {};
	map<int, int> repeatMap = {};
	set<int> lastGroup = {};
	for (int t = 1; t < timeBound; ++t)
	{
		int caseNum = 0;
		int repeatNum = 0;
		int x = 1;
		set<int> lastGroupCopy = {};
		while ((2 * x + 1 - t) * t / 2 <= xRange.second)
		{
			if ((2 * x + 1 - t) * t / 2 >= xRange.first && (x + 1 - t) >= 0)
			{
				++caseNum;
				lastGroupCopy.insert(x);
				if (lastGroup.find(x) != lastGroup.end())
					++repeatNum;
			}
			++x;
		}
		timeNCaseNum.insert({ t, caseNum });
		repeatMap.insert({ t, repeatNum });
		lastGroup = lastGroupCopy;
	}
	return { timeNCaseNum, repeatMap };
}

array<map<int, int>, 2> PossibleValueY(pair<int, int> yRange)
{
	map<int, int> timeNCaseNum = {};
	map<int, int> repeatMap = {};
	for (int vy = -abs(yRange.first); vy < abs(yRange.first); ++vy)
	{
		int t = 1;
		bool validV = false;
		while ((2 * vy + 1 - t) * t / 2 >= yRange.first)
		{
			if ((2 * vy + 1 - t) * t / 2 <= yRange.second)
			{			
				if (timeNCaseNum.find(t) == timeNCaseNum.end())
					timeNCaseNum.insert({ t, 1 });
				else
					++timeNCaseNum[t];
				if (validV) 
				{
					if (repeatMap.find(t) == repeatMap.end())
						repeatMap.insert({ t, 1 });
					else
						++repeatMap[t];
				}
				validV = true;
			}
			++t;
		}	
	}
	return { timeNCaseNum, repeatMap };
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
	pair<int, int> xRange = { 288, 330 };
	pair<int, int> yRange = { -96, -50 };

	array<map<int, int>, 2> xCopy = PossibleValueX(xRange);
	array<map<int, int>, 2> yCopy = PossibleValueY(yRange);

	map<int, int> xList = xCopy[0];
	map<int, int> yList = yCopy[0];
	map<int, int> xRepeat = xCopy[1];
	map<int, int> yRepeat = yCopy[1];
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
			for (auto& itrY2 : yRepeat)
			{
				if (itrY2.first > itrX2)
				{
					result -= itrY2.second;
				}
			}
		}
	}

	for (auto& itrX3 : xRepeat)
	{
		for (auto& itrY3 : yRepeat)
		{
			if (itrY3.first == itrX3.first)
			{
				result -= itrY3.second * itrX3.second;
			}
			else if (itrY3.first > itrX3.first)
				break;
		}
	}

	cout << result << "\n";
}
