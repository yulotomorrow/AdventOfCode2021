#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

void ReadInput(array<array<int, 10>, 10>& octopusMap)
{
	fstream fs;
	fs.open("11input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	while (getline(fs, line))
	{
		for (int col = 0; col <=9; ++col)
		{
			octopusMap[lineNum][col] = line[col] - '0';
		}
		++lineNum;
	}
	fs.close();
}

void OctopusFlashing(array<array<int, 10>, 10>& octopus)
{
	int sum = 0;
	int l = 10;
	int flashTime = 100;
	list<pair<int, int>> flashList = {};
	for (int f = 1; f <= flashTime; ++f)
	{
		for (int i = 0; i < l; ++i)
		{
			for (int j = 0; j < l; ++j)
			{
				++octopus[i][j];
				if (octopus[i][j] > 9)
					flashList.push_back({ i, j });
			}
		}
		auto itr = flashList.begin();
		while (itr != flashList.end())
		{
			int ii = (*itr).first;
			int jj = (*itr).second;
			if (ii > 0)
			{
				++octopus[ii - 1][jj];
				pair<int, int> p1 = { ii - 1, jj };
				if (octopus[ii - 1][jj] > 9 && find(flashList.begin(), flashList.end(), p1) == flashList.end())
					flashList.push_back(p1);
			}
			if (ii < l -1)
			{
				++octopus[ii + 1][jj];
				pair<int, int> p2 = { ii + 1, jj };
				if (octopus[ii + 1][jj] > 9 && find(flashList.begin(), flashList.end(), p2) == flashList.end())
					flashList.push_back(p2);
			}
			if (jj > 0)
			{
				++octopus[ii][jj - 1];
				pair<int, int> p3 = { ii, jj -1 };
				if (octopus[ii][jj -1] > 9 && find(flashList.begin(), flashList.end(), p3) == flashList.end())
					flashList.push_back(p3);
			}
			if (jj < l -1)
			{
				++octopus[ii][jj + 1];
				pair<int, int> p4 = { ii, jj + 1 };
				if (octopus[ii][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p4) == flashList.end())
					flashList.push_back(p4);
			}
			// diag
			if (ii > 0 && jj > 0)
			{
				++octopus[ii - 1][jj -1];
				pair<int, int> p1 = { ii - 1, jj -1 };
				if (octopus[ii - 1][jj -1] > 9 && find(flashList.begin(), flashList.end(), p1) == flashList.end())
					flashList.push_back(p1);
			}
			if (ii < l - 1 && jj < l -1)
			{
				++octopus[ii + 1][jj + 1];
				pair<int, int> p2 = { ii + 1, jj + 1 };
				if (octopus[ii + 1][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p2) == flashList.end())
					flashList.push_back(p2);
			}
			if (jj > 0 && ii < l - 1)
			{
				++octopus[ii+1][jj - 1];
				pair<int, int> p3 = { ii+1, jj - 1 };
				if (octopus[ii+1][jj - 1] > 9 && find(flashList.begin(), flashList.end(), p3) == flashList.end())
					flashList.push_back(p3);
			}
			if (jj < l - 1 && ii > 0)
			{
				++octopus[ii -1][jj + 1];
				pair<int, int> p4 = { ii-1, jj + 1 };
				if (octopus[ii-1][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p4) == flashList.end())
					flashList.push_back(p4);
			}
			++itr;
		}
		auto itr2 = flashList.begin();
		while (itr2 != flashList.end())
		{
			++sum; 
			octopus[(*itr2).first][(*itr2).second] = 0;
			++itr2;
		}
		flashList = {};
	}
	cout << sum << "\n";
}

void OctopusSync(array<array<int, 10>, 10>& octopus)
{
	int sum = 1;
	int l = 10;
	int flashTime = 100;
	list<pair<int, int>> flashList = {};
	while(true)
	{
		for (int i = 0; i < l; ++i)
		{
			for (int j = 0; j < l; ++j)
			{
				++octopus[i][j];
				if (octopus[i][j] > 9)
					flashList.push_back({ i, j });
			}
		}
		auto itr = flashList.begin();
		while (itr != flashList.end())
		{
			int ii = (*itr).first;
			int jj = (*itr).second;
			if (ii > 0)
			{
				++octopus[ii - 1][jj];
				pair<int, int> p1 = { ii - 1, jj };
				if (octopus[ii - 1][jj] > 9 && find(flashList.begin(), flashList.end(), p1) == flashList.end())
					flashList.push_back(p1);
			}
			if (ii < l - 1)
			{
				++octopus[ii + 1][jj];
				pair<int, int> p2 = { ii + 1, jj };
				if (octopus[ii + 1][jj] > 9 && find(flashList.begin(), flashList.end(), p2) == flashList.end())
					flashList.push_back(p2);
			}
			if (jj > 0)
			{
				++octopus[ii][jj - 1];
				pair<int, int> p3 = { ii, jj - 1 };
				if (octopus[ii][jj - 1] > 9 && find(flashList.begin(), flashList.end(), p3) == flashList.end())
					flashList.push_back(p3);
			}
			if (jj < l - 1)
			{
				++octopus[ii][jj + 1];
				pair<int, int> p4 = { ii, jj + 1 };
				if (octopus[ii][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p4) == flashList.end())
					flashList.push_back(p4);
			}
			// diag
			if (ii > 0 && jj > 0)
			{
				++octopus[ii - 1][jj - 1];
				pair<int, int> p1 = { ii - 1, jj - 1 };
				if (octopus[ii - 1][jj - 1] > 9 && find(flashList.begin(), flashList.end(), p1) == flashList.end())
					flashList.push_back(p1);
			}
			if (ii < l - 1 && jj < l - 1)
			{
				++octopus[ii + 1][jj + 1];
				pair<int, int> p2 = { ii + 1, jj + 1 };
				if (octopus[ii + 1][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p2) == flashList.end())
					flashList.push_back(p2);
			}
			if (jj > 0 && ii < l - 1)
			{
				++octopus[ii + 1][jj - 1];
				pair<int, int> p3 = { ii + 1, jj - 1 };
				if (octopus[ii + 1][jj - 1] > 9 && find(flashList.begin(), flashList.end(), p3) == flashList.end())
					flashList.push_back(p3);
			}
			if (jj < l - 1 && ii > 0)
			{
				++octopus[ii - 1][jj + 1];
				pair<int, int> p4 = { ii - 1, jj + 1 };
				if (octopus[ii - 1][jj + 1] > 9 && find(flashList.begin(), flashList.end(), p4) == flashList.end())
					flashList.push_back(p4);
			}
			++itr;
		}
		if (flashList.size() == 100)
		{
			cout << sum << "\n";
			return;
		}
		auto itr2 = flashList.begin();
		while (itr2 != flashList.end())
		{	
			octopus[(*itr2).first][(*itr2).second] = 0;
			++itr2;
		}
		flashList = {};
		++sum;
	}
}

int main()
{
	array<array<int, 10>, 10> octopusMap = {};
	array<array<int, 10>, 10>& octopus = octopusMap;
	ReadInput(octopus);

//	OctopusFlashing(octopus);
	OctopusSync(octopus);
}
