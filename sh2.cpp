#include <iostream>
#include <bitset>
#include <unordered_map>
#include <utility>

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second % 32); // Wrap around when it exceeds 32
        return h1 ^ h2;
    }
};

struct PairEqual {
    template <typename T1, typename T2>
    bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && (lhs.second % 32) == (rhs.second % 32); // Wrap around comparison
    }
};

// Define a function to calculate the number of terms for a given Wt in SHA-256
int countTerms(int t, int rotl, std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual>& hmap, int a, int b, int c, int d) {
    if (t <= 15) {
        // For t values less than or equal to 16, return 1 term
        hmap[std::make_pair(t, rotl % 33)]++;
        return 1;
    }
    
    // Recursively calculate the terms for Wt_17, Wt_19, Wt_10, and Wt_7
    int terms_Wt_A = countTerms(t - a, rotl + 7, hmap, a, b, c, d) + countTerms(t - a, rotl + 18, hmap, a, b, c, d);
    int terms_Wt_B = countTerms(t - b, rotl, hmap, a, b, c, d);
    int terms_Wt_C = countTerms(t - c, rotl + 17, hmap, a, b, c, d) + countTerms(t - c, rotl + 19, hmap, a, b, c, d);
    int terms_Wt_D = countTerms(t - d, rotl, hmap, a, b, c, d);
    
    // Calculate the total number of terms involved in Wt
    return terms_Wt_A + terms_Wt_B + terms_Wt_C + terms_Wt_D;
}

int main() {
    int t = 20; // The value of t for W27
    
    std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual> hmap;

    // Call the function to count the terms involved in W27 for SHA-256
    int terms = countTerms(t, 0, hmap, 6144, 1, 1, 16777216);
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
        std::cout << "Key: (" << key.first << ", " << (key.second) << "), Value: " << value << std::endl;
    }
    
    std::cout<<"Terms in Wt: "<<res;

    return 0;
}
