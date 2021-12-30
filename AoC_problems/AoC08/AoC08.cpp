#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int InputProcessV1(string line)
{
	int count = 0;
	bool read = false;
	int charaCount = 0;
	for (auto& chara : line)
	{
		if (read)
		{
			if (chara == ' ')
			{
				if (charaCount == 2 || charaCount == 3 || charaCount == 4 || charaCount == 7)
					++count;
				charaCount = 0;
			}
			else
			{
				++charaCount;
			}
		}
		if (chara == '|')
		{
			read = true;
		}
	}
	if (charaCount == 2 || charaCount == 3 || charaCount == 4 || charaCount == 7)
		++count;
	return count;
}

bool MatchString(string str1, string str2) 
{
	for (auto& c : str2) 
	{
		bool find = false;
		for (auto& c0 : str1) 
		{
			if (c0 == c)
			{
				find = true;
				break;
			}
		}
		if (!find)
			return false;
	}
	return true;
}

int InputProcessV2(string line)
{
	string digits = "";
	bool read = false;
	int charaCount = 0;
	array<string, 10> verifyArr = {};
	vector<string> unchecked5 = {};
	vector<string> unchecked6 = {};
	string charaStr = "";
	for (auto& chara : line)
	{
		if (chara >= 'a' && chara <= 'g') 
		{
			charaStr = charaStr + chara;
		}
		else if (chara == ' ')
		{
			sort(charaStr.begin(), charaStr.end());
			if (!read)
			{
				int length = charaStr.size();
				switch (length) 
				{
				case 2 :
					verifyArr[1] = charaStr;
					break;
				case 3:
					verifyArr[7] = charaStr;
					break;
				case 4:
					verifyArr[4] = charaStr;
					break;
				case 5:
					unchecked5.push_back(charaStr);
					break;
				case 6:
					unchecked6.push_back(charaStr);
					break;
				case 7:
					verifyArr[8] = charaStr;
					break;
				}
			}
			else
			{
				int i = 0;
				for (auto& a : verifyArr) 
				{
					if (a == charaStr) 
					{
						digits = digits + to_string(i);
						break;
					}
					++i;
				}
			}
			charaStr = "";
		}
		else if (chara == '|')
		{
			read = true;
			for (auto& s6 : unchecked6) 
			{
				if (!MatchString(s6, verifyArr[1]))
					verifyArr[6] = s6;
				else if (!MatchString(s6, verifyArr[4]))
					verifyArr[0] = s6;
				else
					verifyArr[9] = s6;
			}
			char c6 = 'a'; // the character 6 missing
			if (find(verifyArr[6].begin(), verifyArr[6].end(), verifyArr[1][0]) == verifyArr[6].end())
				c6 = verifyArr[1][0];
			else
				c6 = verifyArr[1][1];
			for (auto& s5 : unchecked5)
			{
				if (MatchString(s5, verifyArr[1]))
					verifyArr[3] = s5;
				else if (find(s5.begin(), s5.end(), c6) == s5.end())
					verifyArr[5] = s5;
				else
					verifyArr[2] = s5;
			}
		}
	}
	sort(charaStr.begin(), charaStr.end());
	int i = 0;
	for (auto& a : verifyArr)
	{
		if (a == charaStr)
		{
			digits = digits + to_string(i);
			break;
		}
		++i;
	}
	return stoi(digits);
}

void ReadInput()
{
	fstream fs;
	fs.open("08input.txt");
	string line;
	
	int result1 = 0;
	int result2 = 0;
	while (getline(fs, line))
	{
		result1 += InputProcessV1(line);
		result2 += InputProcessV2(line);
	}
	fs.close();
	cout << result1 << " " << result2 << "\n";
}

int main()
{
	ReadInput();
}
