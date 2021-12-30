#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <list>
#include <queue>
using namespace std;

list<pair<int, int>> InputProcess(string line)
{
	list<pair<int, int>> levelList = {};
	int levelCount = 1; // leverage level by 1 while building, save time for join
	for (auto& chara : line)
	{
		if (chara == '[')
		{
			++levelCount;
		}
		else if (chara == ']')
		{
			--levelCount;
		}
		else if (chara >= '0' && chara <= '9')
		{
			levelList.push_back({levelCount, chara - '0'});
		}		
	}
	return levelList;
}

void ReadInput(queue<list<pair<int, int>>>& addQueue)
{
	fstream fs;
	fs.open("18test.txt");
	string line;
	list<pair<int, int>> levelList;
	while (getline(fs, line))
	{
		levelList = InputProcess(line);
		addQueue.push(levelList);
	}
	fs.close();
}

void BracketReduction(list<pair<int, int>>& processList)
{
	auto mainItr = processList.begin();
	// iterator follows the left side, move to right
	while (mainItr != processList.end()) 
	{
		if ((*mainItr).first > 4)
		{
		int temp_front = (*mainItr).second;
		mainItr = processList.erase(mainItr);
		int temp_back = (*mainItr).second;
		--(*mainItr).first;
		(*mainItr).second = 0;
		++mainItr;
		if (mainItr != processList.end())
		{
			(*mainItr).second += temp_back;
		}
		--mainItr;
		if (mainItr != processList.begin())
		{
			--mainItr;
			(*mainItr).second += temp_front;
		}
		}

		else if ((*mainItr).second > 9)
		{
		int temp_front = floor((*mainItr).second / 2.0);
		int temp_back = ceil((*mainItr).second / 2.0);
		++(*mainItr).first;
		(*mainItr).second = temp_back;
		processList.insert(mainItr, { (*mainItr).first, temp_front });
		--mainItr;
		}

		else
			++mainItr;
	}
	for (auto& a : processList) 
	{
		++a.first;
	}
}

void BracketScore(list<pair<int, int>>& processList) 
{
	int maxLayer = 5;
	auto mainItr = processList.begin();
	bool isFirst = true;
	while (maxLayer > 1) 
	{
		mainItr = processList.begin();
		int localScore = 0;
		while (mainItr != processList.end()) 
		{
			if ((*mainItr).first == maxLayer)
			{
				localScore += 3 * (*mainItr).second;
				mainItr = processList.erase(mainItr);
				localScore += 2 * (*mainItr).second;
				--(*mainItr).first;
				(*mainItr).second = localScore;
				localScore = 0;
			}
			++mainItr;
		}
		--maxLayer;
	}
}

void BracketAddition(queue<list<pair<int, int>>>& addQueue)
{
	int count = 0;
	list<pair<int, int>> firstList = {};
	list<pair<int, int>>& processList = firstList;
	while (addQueue.size() != 0) 
	{
		if (count == 0) 
		{
			firstList = addQueue.front();
			addQueue.pop();
			list<pair<int, int>> secondList = addQueue.front();
			firstList.splice(firstList.end(), secondList);
			addQueue.pop();
		}
		else 
		{
			list<pair<int, int>> secondList = addQueue.front();
			firstList.splice(firstList.end(), secondList);
			addQueue.pop();
		}
		BracketReduction(processList);
		++count;
	}
	BracketScore(processList);
	cout << (*processList.begin()).second << "\n";
}

int main()
{
	queue<list<pair<int, int>>> additionQueue = {};
	queue<list<pair<int, int>>>& addQueue = additionQueue;
	ReadInput(addQueue);
	BracketAddition(addQueue);


	list<pair<int, int>> testL = { {1,1} };
	list<pair<int, int>>& testList = testL;
	BracketScore(testList);

}

