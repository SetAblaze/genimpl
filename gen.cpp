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
    int t;
    

    void fitness()
    {
        int ans = getTerms(t, a, b, c, d);

        if(rank < ans) rank = ans;
    }
};

int main()
{
    std::random_device device;
    std::uniform_int_distribution<int> uinf(1, 6);
    std::vector<Solution> solutions;

    const int NUM = 10000;
    for(int i = 0; i < NUM; i++) {
        solutions.push_back(Solution{
            0,
            uinf(device),
            uinf(device),
            uinf(device),
            uinf(device),
            20
        });
    }
    while(true)
    {
        //Run fitness function
        for(auto& s : solutions) {s.fitness();}

        std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs){
            return lhs.rank > rhs.rank;
        });

        std::for_each(solutions.begin(), solutions.begin() + 10, [](const auto& s){
            std::cout<<"Rank "<<s.rank
            <<"\n A:"<<s.a<<" B:"<<s.b<<" C:"<<s.c<<" D:"<<s.d<<" \n";
        });

        const int SAMPLE_SIZE = 100;
        std::vector<Solution> sample;
        std::copy(
            solutions.begin(), 
            solutions.begin() + SAMPLE_SIZE,
            std::back_inserter(sample)
        );

        solutions.clear();

        //Mutation
        std::uniform_int_distribution<int> m(1, 2);
        std::for_each(sample.begin(), sample.end(), [&](auto& s){
            s.a *= m(device);
            s.b *= m(device);
            s.c *= m(device);
            s.d *= m(device);
        });

        //Crossover
        std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
        for(int i = 0; i < NUM; i++)
        {
            solutions.push_back(Solution{
                0,
                sample[cross(device)].a,
                sample[cross(device)].b,
                sample[cross(device)].c,
                sample[cross(device)].d,
                20
            });
        }
    }

    return 0;
}