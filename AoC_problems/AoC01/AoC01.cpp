#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

void ReadInput()
{
	fstream fs;
	fs.open("01input.txt");
	string line;

	int count = -1;
	int last = 0;
	int count2 = 0;
	int last3 = 0;
	queue<int, deque<int>> q = {};
	while (getline(fs, line))
	{
		if (last < stoi(line))
			++count;
		last = stoi(line);
		//
		q.push(last);
		if (q.size() > 3) 
		{
			last3 = q.front();
			q.pop();
			if (last > last3)
				++count2;
		}
	}
	fs.close();
	cout << count << " " << count2 << "\n";
}

int main()
{
	ReadInput();
}
