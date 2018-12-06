#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

std::vector<std::string> get_ids() {
    std::ifstream input("input.txt");
    std::vector<std::string> ids;

    std::string id;
    while (input >> id) {
        ids.push_back(id);
    }

    input.close();

    return ids;
}

std::tuple<int, int> check_occurences(std::string str) {
    int x = 0;
    int y = 0;
    for (char& c : str) {
        size_t i = std::count(str.begin(), str.end(), c);
        if (i == 2 && x == 0) {
            x++;
        } else if (i == 3 && y == 0) {
            y++;
        }
    }

    return std::make_tuple(x, y);
}

int main() {
    int two = 0;
    int three = 0;
    auto ids = get_ids();
    for (std::string& id : ids) {
        auto values = check_occurences(id);
        two += std::get<0>(values);
        three += std::get<1>(values);
    }

    std::cout << two * three << std::endl;

    return 0;
}