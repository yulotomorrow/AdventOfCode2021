#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

pair<int, int> InputProcessP1(string line)
{
	int num1 = 0;
	int num2 = 0;
	string num = "";
	for (auto& chara : line)
	{
		
		if (chara != ',')
		{
			num = num + chara;
		}
		else 
		{
			num1 = stoi(num);
			num = "";
		}
	}
	num2 = stoi(num);
	return { num1, num2 };
}

pair<char, int> InputProcessP2(string line)
{
	char c = 'x';
	int num2 = 0;
	string num = "";
	for (auto& chara : line)
	{

		if (chara == 'x' || chara == 'y')
		{
			c = chara;
		}
		else if (chara >= '0' && chara <= '9')
		{
			num = num + chara;
		}
	}
	num2 = stoi(num);
	return { c, num2 };
}

void ReadInput(vector<pair<int, int>>& coords, vector<pair<char, int>>& folds)
{
	fstream fs;
	fs.open("13input.txt");
	string line;
	int lineNum = 0;
	int columnCount = 0;
	while (getline(fs, line))
	{
		if (line[0] == 'f') 
		{
			folds.push_back(InputProcessP2(line));
		}
		else if (line[0] >= '0' && line[0] <= '9') 
		{
			coords.push_back(InputProcessP1(line));
		}
	}
	fs.close();
}

int Folding(vector<pair<int, int>>& coords, pair<char, int> fold)
{
	set<pair<int, int>> newCoords = {};
	if (fold.first == 'x') 
	{
		for (auto& c : coords) 
		{
			int x = c.first;
			int y = c.second;
			if (c.first > fold.second)
			{
				x = 2 * fold.second - c.first;			
			}
			newCoords.insert({ x,y });
		}
	}
	else 
	{
		for (auto& c : coords)
		{
			int x = c.first;
			int y = c.second;
			if (c.second > fold.second)
			{
				y = 2 * fold.second - c.second;
			}
			newCoords.insert({ x,y });
		}
	}
	return newCoords.size();
}

void Visualization(set<pair<int, int>> coords) 
{
	int xMax = 0;
	int yMax = 0;
	for (auto& a : coords) 
	{
		if (a.first > xMax) 
		{
			xMax = a.first;
		}
		if (a.second > yMax)
			yMax = a.second;
	}
	vector<char> rowFill(xMax + 1);
	vector<vector<char>> empty(yMax + 1);
	fill(rowFill.begin(), rowFill.end(), '.');
	fill(empty.begin(), empty.end(), rowFill);
	for (auto& b : coords)
	{
		empty[b.second][b.first] = '0';
	}
	for (auto& i : empty) 
	{
		for (auto& j : i) 
		{
			cout << j;
		}
		cout << "\n";
	}
}

void FoldingRepeat(vector<pair<int, int>>& coords, vector<pair<char, int>>& folds)
{
	set<pair<int, int>> newCoords = {};
	for(auto& a : coords)
	{
		newCoords.insert(a);
	}
	set<pair<int, int>> newCoords2 = {};
	for (auto& fold : folds)
	{
		if (fold.first == 'x')
		{
			for (auto& c : newCoords)
			{
				int x = c.first;
				int y = c.second;
				if (c.first > fold.second)
				{
					x = 2 * fold.second - c.first;
				}
				newCoords2.insert({ x,y });
			}
		}
		else
		{
			for (auto& c : newCoords)
			{
				int x = c.first;
				int y = c.second;
				if (c.second > fold.second)
				{
					y = 2 * fold.second - c.second;
				}
				newCoords2.insert({ x,y });
			}
		}
		newCoords = newCoords2;
		newCoords2 = {};
	}
	Visualization(newCoords);
}


int main()
{
	vector<pair<int, int>> coordinates = {}; 
	vector<pair<char, int>> foldings = {};
	vector<pair<int, int>>& coords = coordinates;
	vector<pair<char, int>>& folds = foldings;
	ReadInput(coords, folds);
	int result = Folding(coords, folds[0]);
	cout << result << "\n";

	FoldingRepeat(coords, folds);
}

