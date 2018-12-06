#include <fstream>
#include <iostream>
#include <vector>

bool has_value(std::vector<int> array, int value) {
    for (auto i = array.begin(); i != array.end(); ++i) {
        if (*i == value) {
            return true;
        }
    }

    return false;
}

int main(void) {
    std::ifstream input("input.txt");
    std::vector<int> frequencies;

    int frequency;
    while (input >> frequency) {
        frequencies.push_back(frequency);
    }

    input.close();

    std::vector<int> seen;
    int freq = 0;
    
    while (true) {
        for (auto i = frequencies.begin(); i != frequencies.end(); ++i) {
            freq += *i;
            if (has_value(seen, freq)) {
                std::cout << freq << std::endl;
                return 0;
            } else {
                seen.push_back(freq);
            }
        }
    }
    
    return 0;
}
