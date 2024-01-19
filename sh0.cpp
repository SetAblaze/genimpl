#include <iostream>
#include <bitset>
#include <unordered_map>

std::unordered_map<uint32_t, int> iniMap() {
    std::unordered_map<uint32_t, int> myMap;

    for (uint32_t i = 1; i <= 15; ++i) {
        myMap[i] = 0;
    }

    return myMap;
}

// Define a function to calculate the number of terms for a given Wt in SHA-256
int countTerms(uint32_t Wt, int t, std::unordered_map<uint32_t, int>& hmap, int a, int b, int c, int d) {
    if (t <= 16) {
        // For t values less than or equal to 16, return 1 term
        hmap[t]++;
        return 1;
    }

    // Calculate the terms involved in Wt based on previous words
    uint32_t Wt_A = (Wt >> a) & 0x1FF;
    uint32_t Wt_B = (Wt >> b) & 0x1FF;
    uint32_t Wt_C = (Wt >> c) & 0x3FFFFF;
    uint32_t Wt_D = (Wt >> d) & 0x7FFFFFF;
    
    // Recursively calculate the terms for Wt_17, Wt_19, Wt_10, and Wt_7
    int terms_Wt_A = countTerms(Wt_A, t - a, hmap, a, b, c, d);
    int terms_Wt_B = countTerms(Wt_B, t - b, hmap, a, b, c, d);
    int terms_Wt_C = countTerms(Wt_C, t - c, hmap, a, b, c, d);
    int terms_Wt_D = countTerms(Wt_D, t - d, hmap, a, b, c, d);
    
    // Calculate the total number of terms involved in Wt
    return terms_Wt_A + terms_Wt_B + terms_Wt_C + terms_Wt_D;
}

int main() {
    uint32_t W27 = 0x13; // Replace with your W27 value for SHA-256
    int t = 27; // The value of t for W27
    
    std::unordered_map<uint32_t, int> hmap = iniMap();

    // Call the function to count the terms involved in W27 for SHA-256
    int terms = countTerms(W27, t, hmap, 3, 8, 14, 16);
    int res = 0;
    
    for (uint32_t i = 1; i <= 15; ++i) {
        if(hmap[i] > 0 )
        {
            if(hmap[i] % 2 != 0){
                res++;
            }
        }
    }
    
    std::cout << "Number of terms in W27 (SHA-0): " << terms << std::endl;
    std::cout << "Real Number of terms in W27 (SHA-0): " << res << std::endl;

    return 0;
}
