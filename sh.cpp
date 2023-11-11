#include <iostream>
#include <bitset>

// Define a function to calculate the number of terms for a given Wt in SHA-256
int countTerms(uint32_t Wt, int t) {
    if (t <= 16) {
        // For t values less than or equal to 16, return 1 term
        return 1;
    }

    // Calculate the terms involved in Wt based on previous words
    uint32_t Wt_17 = (Wt >> 17) & 0x1FF;
    uint32_t Wt_19 = (Wt >> 19) & 0x1FF;
    uint32_t Wt_10 = (Wt >> 10) & 0x3FFFFF;
    uint32_t Wt_7 = (Wt >> 7) & 0x7FFFFFF;
    
    // Recursively calculate the terms for Wt_17, Wt_19, Wt_10, and Wt_7
    int terms_Wt_17 = countTerms(Wt_17, t - 17);
    int terms_Wt_19 = countTerms(Wt_19, t - 19);
    int terms_Wt_10 = countTerms(Wt_10, t - 10);
    int terms_Wt_7 = countTerms(Wt_7, t - 7);
    
    // Calculate the total number of terms involved in Wt
    return terms_Wt_17 + terms_Wt_19 + terms_Wt_10 + terms_Wt_7;
}

int main() {
    uint32_t W27 = 0x12345678; // Replace with your W27 value for SHA-256
    int t = 27; // The value of t for W27

    // Call the function to count the terms involved in W27 for SHA-256
    int terms = countTerms(W27, t);

    std::cout << "Number of terms in W27 (SHA-256): " << terms << std::endl;
    
    return 0;
}
