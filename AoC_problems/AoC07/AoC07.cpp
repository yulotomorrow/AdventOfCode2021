#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

void BinarySearchIncreMove(multiset<int> crabs)
{
	int front = *crabs.begin();
	int end = *(--crabs.end());
	int guess = 0;
	int leastSum = 0;
	int sum1 = 0;
	int sum2 = 0;
	
	while (true)
	{
		sum1 = 0;
		sum2 = 0;
		for (auto& a : crabs)
		{
			sum1 += abs(front - a) * (abs(front - a) + 1) / 2;
			sum2 += abs(end - a) * (abs(end - a) + 1) / 2;
		}
		if (sum1 > sum2) 
		{
			guess = ceil((front + end) / 2.0);
			front = guess;
		}
		else if(sum1 < sum2)
		{
			guess = floor((front + end) / 2.0);
			end = guess;
		}
		else 
		{
			leastSum = sum2;
			break;
		}
	}
	cout << leastSum << "\n";
}

void ReadInput()
{
	fstream fs;
	fs.open("07input.txt");
	string line;
	multiset<int> crabs = { };
	while (getline(fs, line))
	{
		string numStr = "";
		for (auto& c : line)
		{
			if (c == ',')
			{
				crabs.insert(stoi(numStr));
				numStr = "";
			}
			else
			{
				numStr = numStr + c;
			}
		}
		crabs.insert(stoi(numStr));
	}
	fs.close();
	int midPoint =(crabs.size() + 1) / 2;
	int count = 0;
	int total = 0;
	bool isMinus = true;
	for (auto& a : crabs)
	{
		++count;

		if (count == midPoint)
		{
			isMinus = false;
			if (crabs.size() % 2 ==0)
				total -= a;
		}
		else if (isMinus)
			total -= a;
		else
			total += a;
		
	}
	BinarySearchIncreMove(crabs);
	cout << total << " " << "\n";
}

int main()
{
	ReadInput();
}

