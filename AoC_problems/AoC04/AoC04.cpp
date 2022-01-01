#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

string ReadInput(vector<pair<array<array<int, 5>, 5>, array<array<bool, 5>, 5>>>& bingo)
{
	fstream fs;
	fs.open("04input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	array<array<int, 5>, 5> bingoSheet = {};
	array<array<bool, 5>, 5> chosen = {};
	array<bool, 5> chooseLine = {};
	fill(chooseLine.begin(), chooseLine.end(), false);
	fill(chosen.begin(), chosen.end(), chooseLine);
	while (getline(fs, line))
	{
		if (lineNum == 0)
			inputStr = line;
		else if (lineNum > 1)
		{			
			if (lineNum % 6 != 1)
			{
				array<int, 5> bingoLine = {};
				int count = 0;
				string numStr = "";
				bool interval = true;
				for (auto& c : line)
				{
					if (c != ' ')
					{
						numStr = numStr + c;
						interval = false;
					}
					else if(!interval)
					{
						bingoLine[count] = stoi(numStr);
						numStr = "";
						++count;
						interval = true;
					}
				}
				bingoLine[count] = stoi(numStr);
				bingoSheet[(lineNum - 2) % 6] = bingoLine;
			}
			else
			{
				bingo.push_back({ bingoSheet, chosen });
				bingoSheet = {};
			}

		}
		++lineNum;
	}
	bingo.push_back({ bingoSheet, chosen });
	fs.close();
	return inputStr;
}

void ResultProcess(array<array<int, 5>, 5>& win, array<array<bool, 5>, 5>& b, int callNum)
{
	int sum = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (!b[i][j])
			{
				sum += win[i][j];
			}
		}
	}
	cout << sum * callNum << " "<< callNum << "\n";
}

void BingoProcess(string input, vector<pair<array<array<int, 5>, 5>, array<array<bool, 5>, 5>>>& bingo) 
{
	string numStr = "";
	for (auto& c : input) 
	{
		if (c != ',') 
		{
			numStr = numStr + c;
		}
		else
		{
			int callNum = stoi(numStr);
			auto itr = bingo.begin();
			for (auto& a : bingo) 
			{
				for (int i = 0; i < 5; ++i) 
				{
					for (int j = 0; j < 5; ++j) 
					{
						if (a.first[i][j] == callNum) 
						{
							a.second[i][j] = true;
							array<array<bool, 5>, 5>& b = a.second;
							if ((b[i][0] && b[i][1] && b[i][2] && b[i][3] && b[i][4])
								|| (b[0][j] && b[1][j] && b[2][j] && b[3][j] && b[4][j])) 
							{
								array<array<int, 5>, 5>& win = a.first;
								ResultProcess(win, b, callNum);
								bingo.erase(itr);
								return;
							}
						}
					}
				}
			}
			numStr = "";
		}
	}
	int callNum = stoi(numStr);
	for (auto& a : bingo)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (a.first[i][j] == callNum)
				{
					a.second[i][j] = true;
					array<array<bool, 5>, 5>& b = a.second;
					if (b[i][0] && b[i][1] && b[i][2] && b[i][3] && b[i][4]
						&& b[0][j] && b[1][j] && b[2][j] && b[3][j] && b[4][j])
					{
						array<array<int, 5>, 5>& win = a.first;
						ResultProcess(win, b, callNum);
						return;
					}
				}
			}
		}
	}
}

void BingoProcessV2(string input, vector<pair<array<array<int, 5>, 5>, array<array<bool, 5>, 5>>>& bingo)
{
	string numStr = "";
	set<int> index = {};
	for (auto& c : input)
	{
		if (c != ',')
		{
			numStr = numStr + c;
		}
		else
		{
			int callNum = stoi(numStr);
			auto itr = bingo.begin();
			int ind = 0;
			for (auto& a : bingo)
			{
				if (index.find(ind) == index.end())
				{
					for (int i = 0; i < 5; ++i)
					{
						for (int j = 0; j < 5; ++j)
						{
							if (a.first[i][j] == callNum)
							{
								a.second[i][j] = true;
								array<array<bool, 5>, 5>& b = a.second;
								if ((b[i][0] && b[i][1] && b[i][2] && b[i][3] && b[i][4])
									|| (b[0][j] && b[1][j] && b[2][j] && b[3][j] && b[4][j]))
								{
									if (index.size() == 99)
									{
										array<array<int, 5>, 5>& win = a.first;
										ResultProcess(win, b, callNum);
										return;
									}
									else
									{
										index.insert(ind);
									}
								}
							}
						}
					}
				}
				++ind;
			}
			numStr = "";
		}
	}
	int callNum = stoi(numStr);
	for (auto& a : bingo)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (a.first[i][j] == callNum)
				{
					a.second[i][j] = true;
					array<array<bool, 5>, 5>& b = a.second;
					if (b[i][0] && b[i][1] && b[i][2] && b[i][3] && b[i][4]
						&& b[0][j] && b[1][j] && b[2][j] && b[3][j] && b[4][j])
					{
						array<array<int, 5>, 5>& win = a.first;
						ResultProcess(win, b, callNum);
						return;
					}
				}
			}
		}
	}
}

int main()
{
	vector<pair<array<array<int, 5>, 5>, array<array<bool, 5>, 5>>> allBingo = {  };
	vector<pair<array<array<int, 5>, 5>, array<array<bool, 5>, 5>>>& bingo = allBingo;
	string input = ReadInput(bingo);
//	BingoProcess(input, bingo);
	BingoProcessV2(input, bingo);
}

