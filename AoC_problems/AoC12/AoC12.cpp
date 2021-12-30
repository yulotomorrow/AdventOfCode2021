#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Don't put yulo near recursion, or don't put recursion near yulo ;)

void ReadInput(unordered_map<string, unordered_set<string>>& caves)
{
	fstream fs;
	fs.open("12input.txt");
	string line;
	unordered_set<string> smallCave = {};
	while (getline(fs, line))
	{
		string caveStr1 = "";
		string caveStr2 = "";
		bool firstCave = true;
		for (auto& c : line)
		{
			if (c == '-')
			{
				firstCave = false;
			}
			else if (firstCave)
			{
				caveStr1 = caveStr1 + c;
			}
			else
			{
				caveStr2 = caveStr2 + c;
			}
		}
		if (caves.find(caveStr1) == caves.end())
		{
			caves.insert({ caveStr1, { caveStr2 } });
		}
		else
			caves[caveStr1].insert(caveStr2);

		if (caves.find(caveStr2) == caves.end())
		{
			caves.insert({ caveStr2, { caveStr1 } });
		}
		else
			caves[caveStr2].insert(caveStr1);
	}
	fs.close();
}

void CavePath(unordered_map<string, unordered_set<string>>& caves, unordered_set<string>& smallCave, 
	string lastCave, int& paths, bool twiceChance)
{
	if (lastCave == "end") 
	{
		++paths;
		return;
	}
	unordered_set<string> nextCave = caves[lastCave];
	for (auto& cave : nextCave) 
	{
		if (smallCave.find(cave) == smallCave.end()) 
		{
			if (cave[0] >= 'a')
				smallCave.insert(cave);
			CavePath(caves, smallCave, cave, paths, twiceChance);
			if (cave[0] >= 'a')
				smallCave.erase(cave);
		}
		else if (twiceChance && cave != "start")
		{
			CavePath(caves, smallCave, cave, paths, false);
		}
	}
}

int main()
{
	unordered_map<string, unordered_set<string>> cavesConnection = { };
	unordered_map<string, unordered_set<string>>& caves = cavesConnection;
	ReadInput(caves);
	int oneSmallPaths = 0;
	int& paths = oneSmallPaths;
	unordered_set<string> emptyCave = {"start"};
	unordered_set<string>& empty = emptyCave;
	CavePath(caves, empty, "start", paths, true); // first question: twiceChance = false
	cout << paths << "\n";
}

