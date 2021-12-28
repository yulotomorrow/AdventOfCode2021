#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <unordered_set>
using namespace std;

int InputProcess(string line, int lineNum, set<pair<int, int>>& rightShift, set<pair<int, int>>& downShift)
{
	int columnNum = 0;
	for (auto& chara : line)
	{
		if (chara == '>')
		{
			rightShift.insert({ lineNum, columnNum });
		}
		else if (chara == 'v')
		{
			downShift.insert({ lineNum, columnNum });
		}
		++columnNum;
	}
	return columnNum - 1;
}

pair<int, int> ReadInput(set<pair<int, int>>& rightShift, set<pair<int, int>>& downShift)
{
	fstream fs;
	fs.open("25input.txt");
	string line;
	int lineNum = 0;
	int columnCount = 0;
	while (getline(fs, line))
	{
		columnCount = InputProcess(line, lineNum, rightShift, downShift);
		++lineNum;
	}
	fs.close();
	return { lineNum - 1, columnCount };
}


int Movements(set<pair<int, int>>& rightShift, set<pair<int, int>>& downShift, pair<int, int> range)
{
	set<pair<int, int>> newRightShift = {};	
	int movementCount = 0;
	for (auto& a : rightShift)
	{
		pair<int, int> newCoordRight = { a.first, a.second + 1 };
		if (a.second >= range.second)
		{
			newCoordRight = {a.first, 0};
		}
		if (rightShift.find(newCoordRight) == rightShift.end() && downShift.find(newCoordRight) == downShift.end())
		{
			newRightShift.insert(newCoordRight);
			++movementCount;
		}
		else
		{
			newRightShift.insert(a);
		}
	}
	rightShift = newRightShift;
	set<pair<int, int>> newDownShift = {};
	for (auto& b : downShift)
	{
		pair<int, int> newCoordDown = { b.first + 1, b.second };
		if (b.first >= range.first)
		{
			newCoordDown = { 0, b.second };
		}
		if (rightShift.find(newCoordDown) == rightShift.end() && downShift.find(newCoordDown) == downShift.end())
		{
			newDownShift.insert(newCoordDown);
			++movementCount;
		}
		else
		{
			newDownShift.insert(b);
		}
	}
	downShift = newDownShift;
	return movementCount;
}

int AllMovements(set<pair<int, int>>& rightShift, set<pair<int, int>>& downShift, pair<int, int> range)
{
	int stepCount = 0;
	while (Movements(rightShift, downShift, range) != 0)
	{
		++stepCount;
	}
	++stepCount;
	return stepCount;
}


int main()
{
	set<pair<int, int>> right = {};
	set<pair<int, int>>& rightShift = right;
	set<pair<int, int>> down = {};
	set<pair<int, int>>& downShift = down;
	pair<int, int> maxRange = ReadInput(rightShift, downShift);
	int result = AllMovements(rightShift, downShift, maxRange);

    std::cout << maxRange.first << " " << maxRange.second << " " << result << "\n";
}

