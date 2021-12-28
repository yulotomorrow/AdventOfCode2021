#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <map>
using namespace std;

void DeterminedDice(int p1, int p2)
{
	int totalP1 = 0;
	int totalP2 = 0;
	int count = 0;
	int result = 1;
	bool isP1 = true;
	while (totalP1 < 1000 && totalP2 < 1000)
	{
		if (isP1)
		{
			p1 = (p1 + (count * 3 + 2) * 3) % 10;
			if (p1 == 0)
				p1 = 10;
			totalP1 += p1;
		}
		else
		{
			p2 = (p2 + (count * 3 + 2) * 3) % 10;
			if (p2 == 0)
				p2 = 10;
			totalP2 += p2;
		}
		++count;
		isP1 = !isP1;
	}
	if (isP1)
	{
		result = totalP1 * count * 3;
	}
	else
		result = totalP2 * count * 3;
	cout << result << "\n";
}

void PossibilityTable(map<int, long long>& poss)
{
	for (int a =1; a <=3; ++a)
	{
		for (int b = 1; b <= 3; ++b)
		{
			for (int c =1; c <=3; ++c)
			{
				int key = a + b + c;
				if (poss.find(key) == poss.end())
				{
					poss.insert({ key, 1 });
				}
				else
					++poss[key];
			}
		}
	}
}

int StopPlace(int p, int dice) 
{
	p = (p + dice) % 10;
	if (p == 0)
		p = 10;
	return p;
}

void QuantumDiceTable(int initial, const map<int, long long> poss, int totalP, int step, long long totalCase,
	map<int, long long>& stepCaseNum, map<int, long long>& less21)
{
	if (totalP >= 21) 
	{
		if (stepCaseNum.find(step) == stepCaseNum.end())
		{
			stepCaseNum.insert({ step, totalCase });
		}
		else
			stepCaseNum[step] += totalCase;
		return;
	}
	if (less21.find(step) == less21.end())
	{
		less21.insert({ step, totalCase });
	}
	else
		less21[step] += totalCase;
	for (auto& diceVal : poss) 
	{
		int stopVal = StopPlace(initial, diceVal.first);
		QuantumDiceTable(stopVal, poss, totalP + stopVal, step + 1, totalCase * long long(diceVal.second), stepCaseNum, less21);
	}
}

void TableCompare(const map<int, long long>& stepCaseNumP1, const map<int, long long>& stepCaseNumP2, 
	map<int, long long>& lessP1, map<int, long long>& lessP2)
{
	long long p1Win = 0;
	long long p2Win = 0;
	for (auto& diceValP1 : stepCaseNumP1) 
	{
		int indexP2 = (diceValP1.first - 1);
		p1Win += lessP2[indexP2] * diceValP1.second;
	}
	for (auto& diceValP2 : stepCaseNumP2)
	{
		int indexP1 = (diceValP2.first);
		p2Win += diceValP2.second * lessP1[indexP1];
			
	}
	if (p1Win > p2Win)
	{
		cout << p1Win << "\n";
	}
	else
		cout << p2Win << "\n";
}

int main()
{
	int p1 = 6;
	int p2 = 10;
	DeterminedDice(p1, p2);

	map<int, long long> possibilityMap = {};
	map<int, long long>& poss = possibilityMap;
	PossibilityTable(poss);
	map<int, long long> stepCaseNumP1 = {};
	map<int, long long>& stepP1 = stepCaseNumP1;
	map<int, long long> stepCaseNumP2 = {};
	map<int, long long>& stepP2 = stepCaseNumP2;
	map<int, long long> lessThan21P1 = {};
	map<int, long long>& lessP1 = lessThan21P1;
	map<int, long long> lessThan21P2 = {};
	map<int, long long>& lessP2 = lessThan21P2;
	QuantumDiceTable(p1, poss, 0, 0, 1, stepP1, lessP1);
	QuantumDiceTable(p2, poss, 0, 0, 1, stepP2, lessP2);
	TableCompare(stepP1, stepP2,lessP1,lessP2);
}

