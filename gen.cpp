#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>
#include "sh2.cpp"

struct Solution
{
    int rank;
    int a, b, c, d;
    int t = 20;
    std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual> hmap;

    void fitness()
    {
        int ans = countTerms(t, 0, hmap, a, b, c, d);

        rank = ans;
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