#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <algorithm>
#include <deque>
using namespace std;

array<int, 6> InputProcess(string line)
{
	string numStr = "";
	int count = 0;
	array<int, 6> coord = {};
	for (auto& c : line) 
	{
		if (c == '-' || (c >= '0' && c <= '9'))
		{
			numStr = numStr + c;
		}
		else if (numStr != "")
		{
			int num = stoi(numStr);
			coord[count] = num;
			++count;
			numStr = "";
		}
	}
	int num = stoi(numStr);
	coord[count] = num;
	return coord;
}

void ReadInput(deque<pair<bool, array<int, 6>>>& cubes)
{
	fstream fs;
	fs.open("22inputPt1.txt");
	string line;
	array<int, 6> coord = {};
	bool isOn = true;
//	regex onPattern("on");
	while (getline(fs, line))
	{
		if (line[1] != 'n')
			isOn = false;
		else
			isOn = true;
		coord = InputProcess(line);
		cubes.push_back({ isOn, coord });
	}
	fs.close();
}

deque<array<int, 6>> DivideCubesOrdered(array<int, 6> cube1, array<int, 6> cube2)
{
	array<int, 6> newCube = {};
	deque<array<int, 6>> cubeList = {};
	bool isValid = true;
	for(int x = -1; x <= 1; ++x)
	{
		switch (x) 
		{
		case -1 :
			newCube[0] = cube1[0];
			newCube[1] = cube2[0] - 1;
			break;
		case 0:
			newCube[0] = cube2[0];
			newCube[1] = cube2[1];
			break;
		case 1:
			newCube[0] = cube2[1] + 1;
			newCube[1] = cube1[1];
			break;
		default:
			break;
		}
		for (int y = -1; y <= 1; ++y) 
		{
			switch (y)
			{
			case -1:
				newCube[2] = cube1[2];
				newCube[3] = cube2[2] - 1;
				break;
			case 0:
				newCube[2] = cube2[2];
				newCube[3] = cube2[3];
				break;
			case 1:
				newCube[2] = cube2[3] + 1;
				newCube[3] = cube1[3];
				break;
			default:
				break;
			}
			for (int z = -1; z <= 1; ++z) 
			{
				switch (z)
				{
				case -1:
					newCube[4] = cube1[4];
					newCube[5] = cube2[4] - 1;
					break;
				case 0:
					newCube[4] = cube2[4];
					newCube[5] = cube2[5];
					break;
				case 1:
					newCube[4] = cube2[5] + 1;
					newCube[5] = cube1[5];
					break;
				default:
					break;
				}

				isValid = (newCube[0] <= newCube[1]) && (newCube[2] <= newCube[3]) && newCube[4] <= newCube[5];
				if (isValid && !(!x && !y && !z))
					cubeList.push_back(newCube);
			}
		}
	}
	return cubeList;
}

int CubeNumberCalculation(array<int, 6> cube)
{
	return (cube[1] - cube[0] + 1) * (cube[3] - cube[2] + 1) * (cube[5] - cube[4] + 1);
}

void CubeOperation(deque<pair<bool, array<int, 6>>>& cubes)
{
	int sum = 0;
	auto revItr = cubes.end() - 1;
	deque<array<int, 6>> onList = {};
	deque<array<int, 6>> offList = {};
	deque<array<int, 6>> cubeTempList = {};
	while (true) 
	{
		if ((*revItr).first) 
		{
			array<int, 6> checkCube = (*revItr).second;
			cubeTempList = {};
			cubeTempList.push_back(checkCube);
			deque<array<int, 6>> newCubeTempList = {};
			for (auto& cubeOn : onList) 
			{
				for (auto& cCube : cubeTempList)
				{
					deque<array<int, 6>> cList = DivideCubesOrdered(cCube, cubeOn);
					for (auto& c : cList) 
					{
						newCubeTempList.push_back(c);
					}
				}
				cubeTempList = newCubeTempList;
				newCubeTempList = {};
			}
			for (auto& cubeOff : offList)
			{
				for (auto& cCube : cubeTempList)
				{
					deque<array<int, 6>> cList = DivideCubesOrdered(cCube, cubeOff);
					for (auto& c : cList)
					{
						newCubeTempList.push_back(c);
					}
				}
				cubeTempList = newCubeTempList;
				newCubeTempList = {};
			}
			for (auto& c : cubeTempList)
			{
				onList.push_back(c);
			}
		}
		else 
		{
			array<int, 6> checkCube = (*revItr).second;
			cubeTempList = {};
			cubeTempList.push_back(checkCube);
			deque<array<int, 6>> newCubeTempList = {};
			for (auto& cubeOn : onList)
			{
				for (auto& cCube : cubeTempList)
				{
					deque<array<int, 6>> cList = DivideCubesOrdered(cCube, cubeOn);
					for (auto& c : cList)
					{
						newCubeTempList.push_back(c);
					}
				}
				cubeTempList = newCubeTempList;
				newCubeTempList = {};
			}
			for (auto& c : cubeTempList)
			{
				offList.push_back(c);
			}
		}
		if (revItr != cubes.begin())
			--revItr;
		else
			break;
	}
	for (auto& on : onList) 
	{
		sum += CubeNumberCalculation(on);
	}
	cout << sum << "\n";
}

int main()
{
	deque<pair<bool, array<int, 6>>> cubeCoordinate = {};
	deque<pair<bool, array<int, 6>>>& cubes = cubeCoordinate;
	ReadInput(cubes);
	CubeOperation(cubes);
}
