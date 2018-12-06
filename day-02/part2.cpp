#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#define _DiffMapEntry std::tuple<std::string, std::string, int>
#define _DiffMap std::vector<_DiffMapEntry>
#define _IdMap std::vector<std::string>
#define LENGTH 26

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

_DiffMap generate_map(_IdMap ids) {
    _DiffMap map;

    for (std::string& id : ids) {
        for (std::string& _id : ids) {
            if (id == _id) continue;

            int differences = 0;
            for (int i = 0; i < LENGTH; i++) {
                if (id[i] != _id[i]) {
                    differences++;
                }
            }

            map.push_back(std::make_tuple(id, _id, differences));
        }
    }

    return map;
}

void sort_map(_DiffMap& map) {
    std::sort(begin(map), end(map), 
        [](_DiffMapEntry const &t1, _DiffMapEntry const &t2) {
            return std::get<2>(t1) < std::get<2>(t2);
        }
    );
}

std::string remove_diffs(std::string id1, std::string id2) {
    std::string common;

    for (int i = 0; i < LENGTH; i++) {
        if (id1[i] == id2[i]) {
            common.push_back(id1[i]);
        }
    }

    return common;
}

int main() {
    auto ids = get_ids();
    auto map = generate_map(ids);

    sort_map(map);

    auto entry = map[0];
    auto id1 = std::get<0>(entry);
    auto id2 = std::get<1>(entry);
    auto common = remove_diffs(id1, id2);

    std::cout << common << std::endl; 

    return 0;
}