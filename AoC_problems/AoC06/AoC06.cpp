#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <queue>
using namespace std;

// L(n) = L(n-7)+L(n-9), just DP it (by hand calculation this is related to Pascal triangle)
void LanternFishDP(array<int, 6> countArr)
{
    map<int, long long> cache = { };
    cache.insert({256, 1});
    bool large9 = true;
    while (large9) 
    {
        map<int, long long> newCache = { };
        large9 = false;
        for (auto& a : cache) 
        {
            if (a.first >= 9) 
            {
                large9 = true;
                int day = a.first - 7;
                if (newCache.find(day) == newCache.end())
                    newCache.insert({ day, a.second });
                else
                    newCache[day] += a.second;
                day = a.first - 9;
                if (newCache.find(day) == newCache.end())
                    newCache.insert({ day, a.second });
                else
                    newCache[day] += a.second;
            }
            else
            {
                int day = a.first;
                if (newCache.find(day) == newCache.end())
                    newCache.insert({ day, a.second });
                else
                    newCache[day] += a.second;
            }
        }
        cache = newCache;
    }
    long long sum = 0;
    for (auto& b : cache) 
    {
        sum += 2 * b.second; 
    }
    long long result = 0;
    for (int i = 0; i < 6; ++i) 
    {
        sum -= cache[i]; // initial case figured out on paper
        result += sum * countArr[i];
    }
    
    cout << result << "\n";
}

int main()
{
    array<int, 6> countArr = {0, 121, 47, 38, 44, 50};
    LanternFishDP(countArr);
}

