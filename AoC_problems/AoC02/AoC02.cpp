#include <iostream>
#include <fstream>
#include <string>
using namespace std;

pair<int, int> InputProcess(string line)
{
	bool isDir = true;
	string dirStr = "";
	string numStr = "";
	for(auto& c : line)
	{
		if (c == ' ')
		{
			isDir = false;
		}
		else if (isDir)
		{
			dirStr = dirStr + c;
		}
		else if (!isDir)
			numStr = numStr + c;
	}
	int num = stoi(numStr);
	int dir = 0;
	if (dirStr == "up")
	{
		dir = 1;
		num *= -1;
	}
	else if (dirStr == "down") 
	{
		dir = 1;		
	}
	return {dir, num};
}

void ReadInput()
{
	fstream fs;
	fs.open("02input.txt");
	string line;
	long long aim = 0;
	pair<long long, long long> horiDepth = { 0, 0 };
	while (getline(fs, line))
	{
		pair<int, int> horiDepthChange = InputProcess(line);
		if (horiDepthChange.first == 0)
		{
			horiDepth.first += (long long)horiDepthChange.second;
			horiDepth.second += aim * long long(horiDepthChange.second);
		}
		else
		{
			//horiDepth.second += (long long)horiDepthChange.second; // fisrt step
			aim += (long long)horiDepthChange.second;
		}
	}
	fs.close();
	long long result = horiDepth.first * horiDepth.second;
	cout << result << " " << "\n";
}

int main()
{
	ReadInput();
}
