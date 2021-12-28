#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <bitset>
using namespace std;

void InputProcess(string line, vector<int>& oneCount)
{
	int index = 0;
	for (auto& chara : line)
	{
		if (chara == '1')
		{
			if ((oneCount.size()) < (index + 1))
				oneCount.push_back(1);
			else
				++oneCount[index];
		}
		else
		{
			if ((oneCount.size() - 1) < index)
				oneCount.push_back(0);
		}
		++index;
	}
}

array<string,2> ReadInput(vector<string>& input, vector<int>& oneCount)
{
	fstream fs;
	fs.open("03input.txt");
	string line;
	getline(fs, line);

	int lineNum = 0;
	string gammaStr = "";
	string epsilonStr = "";
	while (getline(fs, line))
	{
		InputProcess(line, oneCount);
		input.push_back(line);
		++lineNum;
	}
	fs.close();
	for (auto& digit : oneCount)
	{
		if (digit * 2 > lineNum)
		{
			gammaStr = gammaStr + "1";
			epsilonStr = epsilonStr + "0";
		}
		else
		{
			gammaStr = gammaStr + "0";
			epsilonStr = epsilonStr + "1";
		}
	}
	return {gammaStr, epsilonStr};
}

string ResultString(vector<string> input, bool isMost, vector<int> oneList)
{
	int digitLength = input[0].size();
	for (int i = 0; i < digitLength; ++i)
	{
		vector<string> newInput = {};
		int totalStr = input.size();
		bool isOneKept = isMost ? oneList[i] * 2 >= totalStr : oneList[i] * 2 < totalStr;
		for (auto& str : input)
		{			
			bool isOne = str[i] == '1';
			if ((isOneKept && isOne )||(!isOneKept && !isOne))
			{
				newInput.push_back(str);
			}
			else
			{				
				for (int j = i + 1; j < digitLength; ++j)
				{
					oneList[j] -= str[j] - '0';
				}
			}
		}
		if (newInput.size() == 1) 
		{
			return newInput[0];
		}
		input = newInput;
	}
}

int main()
{
	vector<string> inputStr = {};
	vector<string>& input = inputStr;
	vector<int> countList = {};
	vector<int>& oneCount = countList;

	array<string, 2> geStr = ReadInput(input, oneCount);
	int result1 = 1;
	result1 = bitset<32>(geStr[0]).to_ulong() * bitset<32>(geStr[1]).to_ulong();

	string o2Str = ResultString(inputStr, true, countList);
	string co2Str = ResultString(inputStr, false, countList);
	int result2 = 1;
	result2 = bitset<32>(o2Str).to_ulong() * bitset<32>(co2Str).to_ulong();

	cout << result1 << " " << result2 << "\n";
}

