#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <unordered_map>
#include <deque>
#include <set>
#include <algorithm>
using namespace std;

int InputProcess(string line)
{
	stack<char, deque<char>> brackets = {};
	unordered_map<char, char> bracketMatch = { {')', '('}, {']','['}, {'}', '{'}, {'>', '<'}};
	unordered_map<char, int> bracketScore = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
	int num = 0;
	for (auto& chara : line)
	{

		if (chara == '(' || chara == '[' || chara == '{' || chara == '<')
		{
			brackets.push(chara);
		}
		else
		{
			char lastBrac = brackets.top();
			if (lastBrac != bracketMatch[chara]) 
			{
				num += bracketScore[chara];
				return num;
			}
			brackets.pop();			
		}
	}
	return num; 
}

long long InputProcessV2(string line)
{
	stack<char, deque<char>> brackets = {};
	unordered_map<char, char> bracketMatch = { {'(', ')'}, {'[',']'}, {'{', '}'}, {'<', '>'} };
	unordered_map<char, int> bracketScore = { {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
	long long multi = 5;
	long long num2 = 0;
	for (auto& chara : line)
	{

		if (chara == '(' || chara == '[' || chara == '{' || chara == '<')
		{
			brackets.push(chara);
		}
		else
		{
			char lastBrac = brackets.top();
			if (chara != bracketMatch[lastBrac])
			{
				return 0;
			}
			brackets.pop();
		}
	}
	while (brackets.size() != 0) 
	{
		num2 *= multi;
		char closeBrac = bracketMatch[brackets.top()];
		num2 += (long long)bracketScore[closeBrac];
		brackets.pop();
	}
	return num2;
}

void ReadInput()
{
	fstream fs;
	fs.open("10input.txt");
	string line;
	int score = 0;
	set<long long> score2 = {};
	while (getline(fs, line))
	{
		score += InputProcess(line);
		long long s = InputProcessV2(line);
		if (s != 0)
			score2.insert(s);
	}
	fs.close();
	int mid = (score2.size() + 1) / 2;
	auto itr = score2.begin();
	for (int i = 1; i < mid; ++i)
		++itr;
	cout << score  << " " << *itr << "\n";
}

int main()
{
	ReadInput();
}

