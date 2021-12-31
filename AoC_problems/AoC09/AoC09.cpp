#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

void ReadInput(vector<vector<int>>& lowPointMap)
{
	fstream fs;
	fs.open("09input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	while (getline(fs, line))
	{
		vector<int> lineMap = {};
		for (auto& n : line) 
		{
			lineMap.push_back(n - '0');
		}
		lowPointMap.push_back(lineMap);
	}
	fs.close();
}

void FindLowPoint(vector<vector<int>>& lowPointMap, vector<pair<int, int>>& lowPoints)
{
	int sum = 0;
	int l = lowPointMap.size();
	for (int i = 0; i < l; ++i) 
	{
		for (int j = 0; j < l; ++j)
		{
			if (i == 0 || lowPointMap[i][j] < lowPointMap[i - 1][j]) 
			{
				if (i == l - 1 || lowPointMap[i][j] < lowPointMap[i + 1][j])
				{
					if (j == 0 || lowPointMap[i][j] < lowPointMap[i][j - 1])
					{
						if (j == l - 1|| lowPointMap[i][j] < lowPointMap[i][j + 1]) 
						{
							sum += lowPointMap[i][j] + 1;
							lowPoints.push_back({ i, j });
						}
					}
				}
			}
		}
	}
	cout << sum << "\n";
}

int BasinRecursion(const vector<vector<int>>& lowPointMap, vector<vector<bool>>& visitList, int i, int j, const int l)
{
	if (lowPointMap[i][j] == 9)
	{
		visitList[i][j] = false;
		return 0;
	}
	else if (!visitList[i][j])
		return 0;
	int sum = 1;
	visitList[i][j] = false;
	if (i > 0)
		sum += BasinRecursion(lowPointMap, visitList, i - 1, j, l);
	if (i < l - 1)
		sum += BasinRecursion(lowPointMap, visitList, i + 1, j, l);
	if (j > 0)
		sum += BasinRecursion(lowPointMap, visitList, i, j - 1, l);
	if (j < l - 1)
		sum += BasinRecursion(lowPointMap, visitList, i, j + 1, l);
	return sum;
}

void FindBasin(const vector<vector<int>>& lowPointMap)
{
	const int l = lowPointMap.size();
	vector<bool> visitRow = {};
	visitRow.resize(l);
	fill(visitRow.begin(), visitRow.end(), true);
	vector<vector<bool>> visit = {};
	visit.resize(l);
	fill(visit.begin(), visit.end(), visitRow);
	vector<vector<bool>>& visitList = visit;
	multiset<int> basinSize = {};
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < l; ++j) 
		{
			if (visit[i][j]) 
			{
				int basinS = BasinRecursion(lowPointMap, visitList, i, j, l);
				basinSize.insert(basinS);
			}
		}
	}
	int sizeProd = 1;
	auto itr = basinSize.end();
	for (int k = 0; k < 3; ++k)
	{
		--itr;
		sizeProd *= *itr;
	}
	cout << sizeProd << "\n";
}

int main()
{
	vector<vector<int>> lowPointMap = {};
	vector<vector<int>>& lowPoint = lowPointMap;
	ReadInput(lowPoint);

	vector<pair<int, int>> lowPointList = {};
	vector<pair<int, int>> lpts = lowPointList;
	FindLowPoint(lowPoint, lpts);
	FindBasin(lowPoint);
}

