#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

string ReadInput(map<pair<char, char>, char>& mappingChart)
{
	fstream fs;
	fs.open("14input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	while (getline(fs, line))
	{
		if (lineNum == 0)
		{
			inputStr = line;
		}
		else if (lineNum > 1)
		{
			pair<char, char> prev = { line[0], line[1] };
			char next = line.back();
			mappingChart.insert({ prev, next });
		}
		++lineNum;
	}
	fs.close();
	return inputStr;
}

void LetterCount(string input, map<pair<char, char>, char>& mappingChart)
{
	map<pair<char, char>, long long> pairCount = {};
	map<char, long long> letterCount = {};
	for (auto& a : mappingChart) 
	{
		pairCount.insert({a.first, 0});
		letterCount.insert({ a.second, 0 });
	}
	++letterCount[input.front()];
	for (int i = 1; i < input.size(); ++i) 
	{
		++letterCount[input[i]];
		char nextLetter = mappingChart[{input[i - 1], input[i]}];
		++letterCount[nextLetter];
		++pairCount[{input[i-1], nextLetter}];
		++pairCount[{nextLetter, input[i]}];
	}
	for (int step = 2; step <= 40; ++step) 
	{
		map<pair<char, char>, long long> newPairCount = {};
		for (auto& b : pairCount) 
		{
			char nextLetter = mappingChart[b.first];
			letterCount[nextLetter] += b.second;
			newPairCount[{b.first.first, nextLetter}] += b.second;
			newPairCount[{nextLetter, b.first.second}] += b.second;
		}
		pairCount = newPairCount;
	}
	long long least = (*letterCount.begin()).second;
	long long most = least;
	for (auto& c : letterCount)
	{
		if (c.second > most)
			most = c.second;
		if (c.second < least)
			least = c.second;
	}
	cout << most - least << "\n";
}

int main()
{
	map<pair<char, char>, char> mappingChart = {};
	map<pair<char, char>, char>& mapChart = mappingChart;
	string inputStr = ReadInput(mapChart);
	LetterCount(inputStr, mappingChart);
}

