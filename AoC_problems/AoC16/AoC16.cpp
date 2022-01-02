#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

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

int CountInput(string& input, int& pos) 
{
	int v = stoi(input.substr(pos, 3), nullptr, 2);
	pos += 3;
	int t = stoi(input.substr(pos, 3), nullptr, 2);
	pos += 3;
	int vTotal = v;
	if (t == 4) 
	{
		string numStr = "";
		int leading = input[pos] - '0';
		while (leading == 1)
		{
			++pos;
			numStr = numStr + input.substr(pos, 4);
			pos += 4;
			leading = input[pos] - '0';
		}
		++pos;
		numStr = numStr + input.substr(pos, 4);
		pos += 4;
		long long p4 = stoll(numStr, nullptr, 2);

		return vTotal;
	}
	else
	{
		int i = input[pos] - '0';
		++pos;
		if (i == 0)
		{
			const int l = stoi(input.substr(pos, 15), nullptr, 2);
			pos += 15;
			const int pos0 = pos;
			while (pos < (l + pos0)) 
			{
				vTotal += CountInput(input, pos);
				int posTemp = pos;
				bool isAllZero = true;
				if (posTemp >= (l + pos0))
					isAllZero = false;
				while (posTemp < (l + pos0)) 
				{
					if (input[posTemp] != '0')
					{
						isAllZero = false;
						break;
					}
					++posTemp;
				}
				if (isAllZero)
					pos = l + pos0;
			}
		}
		else if (i == 1) 
		{
			int l = stoi(input.substr(pos, 11), nullptr, 2);
			pos += 11;
			for (int count = 1; count <= l; ++count) 
			{
				vTotal += CountInput(input, pos);
			}
		}
	}
	return vTotal;
}

long long ProcessCalculation(int t, vector<long long> nums) 
{
	long long result = 0;
	long long prod = 1;
	switch (t) 
	{
	case 0:
		for (auto& n : nums) 
		{
			result += n;
		}
		return result;
	case 1:
		for (auto& n : nums)
			prod *= n;
		return prod;
	case 2:
		result = nums[0]; 
		for (auto& n : nums)
		{
			if (n < result)
				result = n;
		}
		return result;
	case 3:
		result = nums[0];
		for (auto& n : nums)
		{
			if (n > result)
				result = n;
		}
		return result;
	// sorry I don't use internal type conversion
	case 5 :
		return nums[0] > nums[1] ? (long long)1 : (long long)0;
	case 6:
		return nums[0] < nums[1] ? (long long)1 : (long long)0;
	case 7:
		return nums[0] == nums[1] ? (long long)1 : (long long)0;
	}
}

long long ProcessInput(string& input, int& pos)
{
//	int v = stoi(input.substr(pos, 3), nullptr, 2);
	pos += 3;
	int t = stoi(input.substr(pos, 3), nullptr, 2);
	pos += 3;
//	int vTotal = v;
	long long value = 0;
	if (t == 4)
	{
		string numStr = "";
		int leading = input[pos] - '0';
		while (leading == 1)
		{
			++pos;
			numStr = numStr + input.substr(pos, 4);
			pos += 4;
			leading = input[pos] - '0';
		}
		++pos;
		numStr = numStr + input.substr(pos, 4);
		pos += 4;
		long long p4 = stoll(numStr, nullptr, 2);
		return p4;
	}
	else
	{
		int i = input[pos] - '0';
		++pos;
		if (i == 0)
		{
			const int l = stoi(input.substr(pos, 15), nullptr, 2);
			pos += 15;
			const int pos0 = pos;
			vector<long long> nums1 = {};
			while (pos < (l + pos0))
			{
				nums1.push_back(ProcessInput(input, pos));
				int posTemp = pos;
				bool isAllZero = true;
				if (posTemp >= (l + pos0))
					isAllZero = false;
				while (posTemp < (l + pos0))
				{
					if (input[posTemp] != '0')
					{
						isAllZero = false;
						break;
					}
					++posTemp;
				}
				if (isAllZero)
					pos = l + pos0;
			}
			return ProcessCalculation(t, nums1);
		}
		else if (i == 1)
		{
			int l = stoi(input.substr(pos, 11), nullptr, 2);
			pos += 11;
			vector<long long> nums2 = {};
			for (int count = 1; count <= l; ++count)
			{
				nums2.push_back(ProcessInput(input, pos));
			}
			return ProcessCalculation(t, nums2);
		}
	}	
}

int main()
{
	string inputStr = ReadInput();
	string& input = inputStr;
//	int test = inputStr.size();
	int position = 0;
	int& pos = position;
	int v = CountInput(input, pos);
	cout << v << "\n";
	pos = 0;
	cout << ProcessInput(input, pos) << "\n";
}
