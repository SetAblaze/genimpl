#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>

#include "sh2.cpp"


struct Solution {
    double rank;
    int a, b, c, d;
    int t;
    int rotl = 0;
    std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual> hmap;


    void fitness() {
        int ans = countTerms(t, rotl, hmap, a, b, c, d);
        int res = 0;
    
        for (const auto& entry : hmap) {
            std::pair<int, int> key = entry.first;
            int value = entry.second;
            if(value > 0)
            {
                if(value % 2 != 0)
                {
                    res++; 
                }   
            }
        }
        
        rank = res;
    }
};

int main()
{
    std::random_device device;
    std::uniform_int_distribution<int> uinf(-999, 999);
    std::vector<Solution> solutions;

    const int NUM = 10000;
    for(int i = 0; i < NUM; i++) {
        solutions.push_back(Solution{
            0,
            uinf(device),
            uinf(device),
            uinf(device),
            uinf(device),
            0x13,
            27
        });
    }

    for(auto& s : solutions) {s.fitness();}

    std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs){
        return lhs.rank > rhs.rank;
    });

    std::for_each(solutions.begin(), solutions.begin() + 10, [](const auto& s){
        std::cout<<"Rank "<<s.rank
        <<"\n A:"<<s.a<<" B:"<<s.b<<" C:"<<s.c<<" D:"<<s.d<<" \n";
    });
    return 0;
}