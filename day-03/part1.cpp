#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#define _Pair std::pair<int, int>
#define _MapEntry std::tuple<int, _Pair, _Pair>
#define _Map std::vector<_MapEntry>
#define _FieldEntry std::vector<int>
#define _Field std::vector<_FieldEntry>

// #ID @ LEFT_MARGIN,TOP_MARGIN: WIDTHxHEIGHT

int get_digit(std::string claim, char symbol, bool shift) {
    std::string margin;
    bool read = false;

    for (int i = 0; i < claim.size(); i++) {
        char c = claim[i];
        if (read && std::isdigit(c)) {
            margin.push_back(c);
        } else if (read && !std::isdigit(c)) {
            break;
        }

        if (c == symbol) {
            if (shift) i++;
            read = true;
        }
    }

    return std::stoi(margin);
}

int get_id(std::string claim) {
    return get_digit(claim, '#', false);
}

int get_left_margin(std::string claim) {
    return get_digit(claim, '@', true);
}

int get_top_margin(std::string claim) {
    return get_digit(claim, ',', false);
}

int get_width(std::string claim) {
    return get_digit(claim, ':', true);
}

int get_height(std::string claim) {
    return get_digit(claim, 'x', false);
}

_Pair get_margin(std::string claim) {
    int left = get_left_margin(claim);
    int top = get_top_margin(claim);

    return std::make_pair(left, top);
}

_Pair get_size(std::string claim) {
    int width = get_width(claim);
    int height = get_height(claim);

    return std::make_pair(width, height);
}

_Map get_claims() {
    std::ifstream input("input.txt");
    _Map claims;

    std::string claim;
    while (std::getline(input, claim)) {
        auto id = get_id(claim);
        auto margin = get_margin(claim);
        auto size = get_size(claim);

        claims.push_back(std::make_tuple(id, margin, size));
    }

    input.close();

    return claims;
}

_Pair get_max_size(_Map claims) {
    int width = 0;
    int height = 0;

    for (_MapEntry& claim : claims) {
        auto x = std::get<0>(std::get<1>(claim));
        auto mx = std::get<0>(std::get<2>(claim));
        auto w = x + mx;

        auto y = std::get<1>(std::get<1>(claim));
        auto my = std::get<1>(std::get<2>(claim));
        auto h = y + my;

        if (w > width) width = w;
        if (h > height) height = h;
    }

    return std::make_pair(width, height);
}

_Field initialize_field(int x, int y) {
    _Field field;

    for (int i = 0; i < x; i++) {
        _FieldEntry entry(y, 0);
        field.push_back(entry);
    }

    return field;
}

void generate_field(_Field& field, _Map claims) {
    for (_MapEntry& claim : claims) {
        auto margin = std::get<1>(claim);
        auto size = std::get<2>(claim);

        int mx = std::get<0>(margin);
        int my = std::get<1>(margin);

        for (int x = mx; x < mx + std::get<0>(size); ++x) {
            for (int y = my; y < my + std::get<1>(size); ++y) {
                field[x][y]++;
            }
        }
    }
}

int main() {
    auto claims = get_claims();
    auto max_size = get_max_size(claims);
    int max_x = std::get<0>(max_size);
    int max_y = std::get<1>(max_size);

    std::cout << "Max size: " << max_x << "x" << max_y << std::endl;

    auto field = initialize_field(max_x, max_y);
    generate_field(field, claims);

    int inches = 0;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (field[i][j] >= 2) {
                inches++;
            }
        }
    }

    std::cout << inches << std::endl;

    return 0;
}