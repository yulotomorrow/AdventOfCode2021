#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

// It's better to use the cross line algorithm (there's a ProjEuler problem with continuous example)
// but I somehow forgot the crossprod equation and wasted more time writing this...

void InputProcessHorizontalVertical(string line, vector<vector<int>>& xList, vector<vector<int>>& yList, vector<vector<int>>& aList)
{
	string numStr = "";
	vector<int> coord = {};
	for (auto& c : line)
	{
		if (c >= '0' && c <= '9')
		{
			numStr = numStr + c;
		}
		else if (numStr != "")
		{
			int num = stoi(numStr);
			coord.push_back(num);
			numStr = "";
		}
	}
	int num = stoi(numStr);
	coord.push_back(num);
	if (coord[0]==coord[2]) 
	{
		xList.push_back(coord);
	}
	else if (coord[1] == coord[3])
	{
		yList.push_back(coord);
	}
	aList.push_back(coord);
	
}

void ReadInput(vector<vector<int>>& xList, vector<vector<int>>& yList, vector<vector<int>>& aList)
{
	fstream fs;
	fs.open("05input.txt");
	string line;
	int lineNum = 0;
	string inputStr = "";
	while (getline(fs, line))
	{
		InputProcessHorizontalVertical(line, xList, yList, aList);
	}
	fs.close();
}

void FindCrossPoint(vector<vector<int>>& xList, vector<vector<int>>& yList)
{
	vector<array<int, 4>> lineCross = {};
	set<pair<int, int>> points = {};
	auto itr1 = xList.begin(); 
	while (itr1 != xList.end())
	{
		auto itr2 = itr1 + 1;
		while (itr2 != xList.end())
		{
			if ((*itr1)[0] == (*itr2)[0]) 
			{
				int y1 = (*itr1)[1];
				int y2 = (*itr1)[3];
				int y3 = (*itr2)[1];
				int y4 = (*itr2)[3];
				if (abs(y1 - y2) >= abs(y3 - y4)) 
				{
					if ((y3 - y1) * (y3 - y2) <= 0 || (y4 - y1) * (y4 - y2) <= 0)
					{
						array<int, 4> yRange = {y1, y2, y3, y4};
						sort(yRange.begin(), yRange.end());
						lineCross.push_back({ (*itr1)[0], yRange[1], (*itr1)[0] , yRange[2]});
						for (int i = yRange[1]; i <= yRange[2]; ++i) 
						{
							points.insert({ (*itr1)[0] , i});
						}
					}
				}
				else 
				{
					if ((y1 - y3) * (y1 - y4) <= 0 || (y2 - y3) * (y2 - y4) <= 0)
					{
						array<int, 4> yRange = { y1, y2, y3, y4 };
						sort(yRange.begin(), yRange.end());
						lineCross.push_back({ (*itr1)[0], yRange[1], (*itr1)[0] , yRange[2] });
						for (int i = yRange[1]; i <= yRange[2]; ++i)
						{
							points.insert({ (*itr1)[0] , i });
						}
					}
				}
			}
			++itr2;
		}
		++itr1;
	}
	auto itr3 = yList.begin();
	while (itr3 != yList.end())
	{
		auto itr4 = itr3 + 1;
		while (itr4 != yList.end())
		{
			if ((*itr3)[1] == (*itr4)[1])
			{
				int x1 = (*itr3)[0];
				int x2 = (*itr3)[2];
				int x3 = (*itr4)[0];
				int x4 = (*itr4)[2];
				if (abs(x1 - x2) >= abs(x3 - x4))
				{
					if ((x3 - x1) * (x3 - x2) <= 0 || (x4 - x1) * (x4 - x2) <= 0)
					{
						array<int, 4> xRange = { x1, x2, x3, x4 };
						sort(xRange.begin(), xRange.end());
						lineCross.push_back({  xRange[1], (*itr3)[1], xRange[2],(*itr3)[1] });
						for (int i = xRange[1]; i <= xRange[2]; ++i)
						{
							points.insert({ i, (*itr3)[1] });
						}
					}
				}
				else
				{
					if ((x1 - x3) * (x1 - x4) <= 0 || (x2 - x3) * (x2 - x4) <= 0)
					{
						array<int, 4> xRange = { x1, x2, x3, x4 };
						sort(xRange.begin(), xRange.end());
						lineCross.push_back({ xRange[1], (*itr3)[1], xRange[2],(*itr3)[1] });
						for (int i = xRange[1]; i <= xRange[2]; ++i)
						{
							points.insert({ i, (*itr3)[1] });
						}
					}
				}
			}
			++itr4;
		}
		++itr3;
	}
	for (auto& a : xList) 
	{
		for (auto& b : yList) 
		{
			if ((a[0] - b[0]) * (a[0] - b[2]) <= 0 && (b[1] - a[1]) * (b[1] - a[3]) <= 0)
				points.insert({ a[0], b[1] });
		}
	}
	cout << points.size() << "\n";

}

int Direction(pair<int, int> a1, pair<int, int> a2, pair<int, int> a3)
{
	return (a3.first - a1.first) * (a2.second - a1.second) - (a2.first - a1.first) * (a3.second - a1.second);
}

int TypeOfLine(vector<int> segment) 
{
	if (segment[0] == segment[2])
		return 0;
	else if (segment[1] == segment[3])
		return 1;
	else if ((segment[0] - segment[2]) / (segment[1] - segment[3]) == 1)
		return 2;
	else if ((segment[0] - segment[2]) / (segment[1] - segment[3]) == -1)
		return 3;
//	else
//		return -1;
}

void FindCrossPointAll(vector<vector<int>>& aList)
{
	auto itr1 = aList.begin();
	set<pair<int, int>> points = {};
	while (itr1 != aList.end())
	{
		auto itr2 = itr1 + 1;
		while (itr2 != aList.end())
		{
			int y1 = (*itr1)[1];
			int y2 = (*itr1)[3];
			int y3 = (*itr2)[1];
			int y4 = (*itr2)[3];
			int x1 = (*itr1)[0];
			int x2 = (*itr1)[2];
			int x3 = (*itr2)[0];
			int x4 = (*itr2)[2];

			int d1 = Direction({x3, y3}, {x4, y4}, {x1, y1});
			int d2 = Direction({ x3, y3 }, { x4, y4 }, { x2, y2 });
			int d3 = Direction({ x1, y1 }, { x2, y2 }, { x3, y3 });
			int d4 = Direction({ x1, y1 }, { x2, y2 }, { x4, y4 });

			// overlap
			if (TypeOfLine(*itr1) == TypeOfLine(*itr2)) 
			{
				int t = TypeOfLine(*itr1);
				switch (t) 
				{
					case 0:
						if (x1 == x3)
						{
							if (abs(y1 - y2) >= abs(y3 - y4))
							{
								if ((y3 - y1) * (y3 - y2) <= 0 || (y4 - y1) * (y4 - y2) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									sort(yRange.begin(), yRange.end());
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ x1 , i });
									}
								}
							}
							else
							{
								if ((y1 - y3) * (y1 - y4) <= 0 || (y2 - y3) * (y2 - y4) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									sort(yRange.begin(), yRange.end());
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ x1 , i });
									}
								}
							}
						}
						break;
					case 1:
						if (y1 == y3)
						{
							if (abs(x1 - x2) >= abs(x3 - x4))
							{
								if ((x3 - x1) * (x3 - x2) <= 0 || (x4 - x1) * (x4 - x2) <= 0)
								{
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(xRange.begin(), xRange.end());
									for (int i = xRange[1]; i <= xRange[2]; ++i)
									{
										points.insert({ i, y1 });
									}
								}
							}
							else
							{
								if ((x1 - x3) * (x1 - x4) <= 0 || (x2 - x3) * (x2 - x4) <= 0)
								{
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(xRange.begin(), xRange.end());
									for (int i = xRange[1]; i <= xRange[2]; ++i)
									{
										points.insert({ i, y1 });
									}
								}
							}
						}
						break;
					case 2:
						if (y1 - x1 == y3 - x3)
						{
							if (abs(y1 - y2) >= abs(y3 - y4))
							{
								if ((y3 - y1) * (y3 - y2) <= 0 || (y4 - y1) * (y4 - y2) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(yRange.begin(), yRange.end());
									sort(xRange.begin(), xRange.end());
									int j = xRange[1];
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ j , i });
										++j;
									}
								}
							}
							else
							{
								if ((y1 - y3) * (y1 - y4) <= 0 || (y2 - y3) * (y2 - y4) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(yRange.begin(), yRange.end());
									sort(xRange.begin(), xRange.end());
									int j = xRange[1];
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ j , i });
										++j;
									}
								}
							}
						}
						break;
					case 3:
						if (y1 + x1 == y3 + x3)
						{
							if (abs(y1 - y2) >= abs(y3 - y4))
							{
								if ((y3 - y1) * (y3 - y2) <= 0 || (y4 - y1) * (y4 - y2) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(yRange.begin(), yRange.end());
									sort(xRange.begin(), xRange.end());
									int j = xRange[2];
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ j , i });
										--j;
									}
								}
							}
							else
							{
								if ((y1 - y3) * (y1 - y4) <= 0 || (y2 - y3) * (y2 - y4) <= 0)
								{
									array<int, 4> yRange = { y1, y2, y3, y4 };
									array<int, 4> xRange = { x1, x2, x3, x4 };
									sort(yRange.begin(), yRange.end());
									sort(xRange.begin(), xRange.end());
									int j = xRange[2];
									for (int i = yRange[1]; i <= yRange[2]; ++i)
									{
										points.insert({ j , i });
										--j;
									}
								}
							}
						}
						break;
				}
			}
			// one cross
			else if (d1 * d2 <= 0 && d3 * d4 <= 0)
			{
				int t1 = TypeOfLine(*itr1);
				int t2 = TypeOfLine(*itr2);
				int x0 = -1; 
				int y0 = -1;
				array<int, 4> yRange = { y1, y2, y3, y4 };
				array<int, 4> xRange = { x1, x2, x3, x4 };
				sort(yRange.begin(), yRange.end());
				sort(xRange.begin(), xRange.end());
				if (xRange[1] == xRange[2])
					x0 = xRange[1];
				if (yRange[1] == yRange[2])
					y0 = yRange[1];
				if (t1 > 1 && t2 > 1) 
				{
					int b1 = t1 == 2 ? y1 - x1 : y1 + x1;
					int b2 = t2 == 2 ? y3 - x3 : y3 + x3;
					y0 = (b1 + b2) / 2;
					x0 = abs(b1 - y0);
				}
				else if (t1 > 1)
				{
					int b1 = t1 == 2 ? y1 - x1 : y1 + x1;
					if (x0 >= 0)
						y0 = x0 + b1;
					else if (y0 >= 0)
						x0 = abs(y0 - b1);
				}
				else if (t2 > 1) 
				{
					int b2 = t2 == 2 ? y3 - x3 : y3 + x3;
					if (x0 >= 0)
						y0 = x0 + b2;
					else if (y0 >= 0)
						x0 = abs(y0 - b2);
				}
				if(x0 >= 0 && y0 >= 0)
					points.insert({x0, y0});
			}
			++itr2;
		}
		++itr1;
	}
	cout << points.size() << "\n";
}

int main()
{
	vector<vector<int>>horizontalList = {};
	vector<vector<int>>& xList = horizontalList;
	vector<vector<int>>verticalList = {};
	vector<vector<int>>& yList = verticalList;
	vector<vector<int>>allList = {};
	vector<vector<int>>& aList = allList;
	ReadInput(xList, yList, aList);
	FindCrossPoint(xList, yList);
	FindCrossPointAll(aList);
}
