#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void InputProcessHorizontalVertical(string line, vector<vector<int>>& xList, vector<vector<int>>& yList )
{
	string numStr = "";
	vector<int> coord = {};
	for (auto& c : line)
	{
		if (c >= '0' && c <= '9')
		{
			numStr = numStr + c;
		}
		else if (numStr != "")
		{
			int num = stoi(numStr);
			coord.push_back(num);
			numStr = "";
		}
	}
	int num = stoi(numStr);
	coord.push_back(num);
	if (coord[0]==coord[2]) 
	{
		xList.push_back(coord);
	}
	else if (coord[1] == coord[3])
	{
		yList.push_back(coord);
	}
}

void ReadInput(vector<vector<int>>& xList, vector<vector<int>>& yList)
{
	fstream fs;
	fs.open("05input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	while (getline(fs, line))
	{
		InputProcessHorizontalVertical(line, xList, yList);
	}
	fs.close();
}

int main()
{
	vector<vector<int>>horizontalList = {};
	vector<vector<int>>& xList = horizontalList;
	vector<vector<int>>verticalList = {};
	vector<vector<int>>& yList = verticalList;
	ReadInput(xList, yList);

}
