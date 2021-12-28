#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

array<int, 512> RefListReading(string line)
{
	int count = 0;
	array<int, 512> refList = {};
	for (auto& chara : line)
	{
		if (chara == '#')
		{
			refList[count] = 1;
		}
		else
			refList[count] = 0;
		++count;
	}
	return refList;
}

deque<int> InputProcess(string line)
{
	deque<int> rowInput = {};
	for (auto& chara : line) 
	{
		if (chara == '#')
		{
			rowInput.push_back(1);
		}
		else
			rowInput.push_back(0);
	}
	return rowInput;
}

array<int, 512> ReadInput(deque<deque<int>>& graph0)
{
	fstream fs;
	fs.open("20input.txt");
	string line;
	getline(fs, line);
	array<int, 512> refList = RefListReading(line);
	while (getline(fs, line))
	{
		if (line != "")
		{
			graph0.push_back(InputProcess(line));
		}
	}
	fs.close();
	return refList;
}

void EnlargeConstruct(deque<deque<int>>& graph0,  bool isZero)
{
	int columnSize = graph0[0].size();
	deque<int> fills1(columnSize + 4);
	int fillValue = isZero ? 0 : 1;
	fill(fills1.begin(),fills1.end(), fillValue);
	graph0.push_front(fills1);
	graph0.push_front(fills1);
	int rowCount = 0;
	for (auto& rows : graph0)
	{
		if (rowCount >= 2)
		{
			rows.push_back(fillValue);
			rows.push_back(fillValue);
			rows.push_front(fillValue);
			rows.push_front(fillValue);
		}
		++rowCount;
	}
	graph0.push_back(fills1);
	graph0.push_back(fills1);
}

deque<deque<int>> EnhanceGraphic(array<int, 512> refList, deque<deque<int>>& graph0, int& litCount)
{
	int rowSize = graph0.size();
	int columnSize = graph0[0].size();
	litCount = 0;
	deque<deque<int>> graph1 = {};
	deque<int> row1 = {};
	for (int r = 1; r < rowSize - 1; ++r) 
	{
		row1 = {};
		for (int c = 1; c < columnSize - 1; ++c)
		{
			int binaryVal = graph0[r - 1][c - 1] * 256 + graph0[r - 1][c] * 128 + graph0[r - 1][c + 1] * 64 + graph0[r][c - 1] * 32
				+ graph0[r][c] * 16 + graph0[r][c + 1] * 8 + graph0[r + 1][c - 1] * 4 + graph0[r + 1][c] * 2 + graph0[r + 1][c + 1];
			row1.push_back(refList[binaryVal]);
			litCount += refList[binaryVal];
		}
		graph1.push_back(row1);
	}
//	cout << litCount << "\n";
	return graph1;
}

void RepeatEnhance(array<int, 512> refList, deque<deque<int>>& graph0, int& litCount, int times) 
{
	for (int t = 1; t <= times; ++t)
	{
		deque<deque<int>> graphic1 = EnhanceGraphic(refList, graph0, litCount);
		graph0 = graphic1;
		bool isZero = true;
		if (t % 2 == 1)
			isZero = refList[0] == 0 ? true : false;
		else
			isZero = refList[511] == 0 ? true : false;
		EnlargeConstruct(graph0, isZero);
	}
	cout << litCount << "\n";
}

int main()
{
	deque<deque<int>> originalGraphic = {};
	deque<deque<int>>& graph0 = originalGraphic;
	array<int, 512> refList = ReadInput(graph0);

	EnlargeConstruct(graph0, true);
	int lit = 0;
	int& litCount = lit;

//	deque<deque<int>> graphic1 = EnhanceGraphic(refList, graph0, litCount);
//	deque<deque<int>>& graph1 = graphic1;
//	bool isZero = refList[0] == 0 ? true : false;
//	EnlargeConstruct(graph1, isZero);

//	deque<deque<int>> graphic2 = EnhanceGraphic(refList, graph1, litCount);

	RepeatEnhance(refList, graph0, litCount, 50);

}

