#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

struct Packet
{

};

unordered_map<char, string> Hex() 
{
	unordered_map<char, string> hex = {};
	for (int i = 0; i < 16; ++i) 
	{
		string binary = "";
		int num = i;
		for (int a = 0; a < 4; ++a)
		{
			binary = to_string(num % 2) + binary;
			num /= 2;
		}
		if (i < 10)
			hex.insert({ i + '0', binary });
		else
			hex.insert({ i - 10 + 'A', binary });
	}
	return hex;
}

string ReadInput()
{
	fstream fs;
	fs.open("16input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	unordered_map<char, string> hex = Hex();
	while (getline(fs, line))
	{
		for (auto& c : line)
		{
			inputStr += hex[c];
		}
	}
	fs.close();
	return inputStr;
}

int CountInput(string& input) 
{
	auto itr = input.begin();
	int v = stoi(input.substr(0, 3), nullptr, 2);
	int t = stoi(input.substr(3, 3), nullptr, 2);
	itr += 6;
	int vTotal = v;
	if (t == 4) 
	{
	}
	else
	{
		int i = *(++itr) - '0';
		if (i == 0)
		{
			int l = stoi(input.substr(7, 15), nullptr, 2);
			itr += 15;
			while (itr - input.begin() <= (l + 22)) 
			{

			}
		}
		else if (i == 1) 
		{
			int l = stoi(input.substr(7, 11), nullptr, 2);
			itr += 11;
			string parseStr = input.substr();
			for (int count = 1; count <= l; ++count) 
			{

			}
		}
	}
	return vTotal;
}

int main()
{
	string inputStr = ReadInput();
	string& input = inputStr;
	CountInput(input);
}
