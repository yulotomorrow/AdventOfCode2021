#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <map>
using namespace std;

// just shout DIJKSTRA!!! (But I just copied my code :P)

void InputProcessV2(string line, vector<vector<int>>& input)
{
	array<vector<int>, 5> rows = {};
	int count2 = line.size();
	for (auto& c : line)
	{
		int n = c - '0';
		// wrong, repeat the whole block, need revisit
		for (int i = 0; i < 5; ++i)
		{
			rows[0].push_back((n + i - 1) % 9 + 1);
			rows[1].push_back((n + i + 1 - 1) % 9 + 1);
			rows[2].push_back((n + i + 2 - 1) % 9 + 1);
			rows[3].push_back((n + i + 3 - 1) % 9 + 1);
			rows[4].push_back((n + i + 4 - 1) % 9 + 1);
		}
	}
	for(auto& l : rows)
		input.push_back(l);
}

void ReadInput(vector<vector<int>>& input)
{
	fstream fs;
	fs.open("15input.txt");
	string line;
	while (getline(fs, line))
	{
	/*	vector<int> row = {};
		int count2 = line.size();
		for (auto& c : line)
		{
			row.push_back(c - '0');
		}
		input.push_back(row);
		*/
		InputProcessV2(line, input);
	}
	fs.close();
}


array<int, 2> FindCurrentMinimum(const vector<vector<int>> inputCopy, const vector<vector<bool>> canVisit)
{
	int bound = 100 * 5;
	int min = 1e8;
	array<int, 2> coord = { 0,0 };
	for (int i = 0; i < bound; ++i)
	{
		for (int j = 0; j < bound; ++j)
		{
			if (inputCopy[i][j] < min && canVisit[i][j])
			{
				coord = { i, j };
				min = inputCopy[i][j];
			}
		}
	}
	return coord;
}

void MinOverwrite(vector<vector<int>>& inputArr, const vector<vector<int>>& input,
	const vector<vector<bool>> canVisit, int r, int c, int compareVal)
{
	if (inputArr[r][c] > compareVal && canVisit[r][c])
		inputArr[r][c] = compareVal;
}

void FindMinPathSum4Dir(vector<vector<int>>& input)
{
	int bound = 100 * 5;
	int initial = 1e8;
	vector<vector<int>> inputCopy(bound, vector<int>(bound, initial));
	vector<vector<int>>& inputArr = inputCopy;
	vector<vector<bool>> canVisit(bound, vector<bool>(bound, true));
	multimap<int, array<int, 2>> pairs = {};
	inputCopy[0][0] = 0;
	for (int a = 1; a <= pow(bound, 2); ++a)
	{
		array<int, 2> coord = FindCurrentMinimum(inputCopy, canVisit);
		int row = coord[0];
		int col = coord[1];
		if (row < bound - 1)
		{
			if (inputArr[row + 1][col] > (inputArr[row][col] + input[row][col]) && canVisit[row + 1][col])
				inputArr[row + 1][col] = (inputArr[row][col] + input[row][col]);
		}
		if (row > 0)
		{
			if (inputArr[row - 1][col] > (inputArr[row][col] + input[row][col]) && canVisit[row - 1][col])
				inputArr[row - 1][col] = (inputArr[row][col] + input[row][col]);
		}
		if (col < bound - 1)
		{
			if (inputArr[row][col + 1] > (inputArr[row][col] + input[row][col]) && canVisit[row][col + 1])
				inputArr[row][col + 1] = (inputArr[row][col] + input[row][col]);
		}
		if (col > 0)
		{
			if (inputArr[row][col - 1] > (inputArr[row][col] + input[row][col]) && canVisit[row][col - 1])
				inputArr[row][col - 1] = (inputArr[row][col] + input[row][col]);
		}

		canVisit[row][col] = false;
	}
	// The last element is not in the path, add it.
	cout << inputCopy[bound - 1][bound - 1] + input[bound - 1][bound - 1] - input[0][0] << "\n";
}

int main()
{
	vector<vector<int>> inputList = {};
	vector<vector<int>>& input = inputList;
	ReadInput(input);
	FindMinPathSum4Dir(input);
}
