#include <iostream>
#include <fstream>
#include <regex>

bool is_between(int value, int lower, int upper) {
    return value >= lower && value <= upper;
}

int main() {

    std::fstream file("inputs/input.txt");

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    file.close();

    long res = 0;

    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::sregex_iterator currentMatch(content.begin(), content.end(), pattern);
    std::sregex_iterator lastMatch;
    std::vector<std::pair<size_t, int>> all_multiplications;

    while (currentMatch != lastMatch) {
        
        std::smatch match = *currentMatch;
        std::string num1 = match[1];
        std::string num2 = match[2];

        size_t pos1 = match.position(1);
        int mul = (std::stoi(num1)*std::stoi(num2));
        
        std::pair<size_t, int> p(pos1, mul);
        all_multiplications.push_back(p);

        ++currentMatch;

    }

    std::regex pattern2("do\\(\\)");
    std::sregex_iterator currentMatch2(content.begin(), content.end(), pattern2);
    std::sregex_iterator lastMatch2;
    std::vector<size_t> all_do;
    all_do.push_back(0);

    while (currentMatch2 != lastMatch2) {
        
        std::smatch match = *currentMatch2;
        size_t pos1 = match.position(0);
        all_do.push_back(pos1);

        ++currentMatch2;

    }

    std::regex pattern3("don't\\(\\)");
    std::sregex_iterator currentMatch3(content.begin(), content.end(), pattern3);
    std::sregex_iterator lastMatch3;
    std::vector<size_t> all_dont;

    while (currentMatch3 != lastMatch3) {
        
        std::smatch match = *currentMatch3;
        size_t pos1 = match.position(0);
        all_dont.push_back(pos1);

        ++currentMatch3;

    }

    all_dont.push_back(content.length());

    std::vector<std::pair <size_t, size_t>> ranges;

    auto it1 = all_do.begin();
    auto it2 = all_dont.begin();

    while (it1 != all_do.end() && it2 != all_dont.end()) {

        if (*it2 > *it1) {

            int curr = *it1;

            while (it1 != all_do.end() && *it1 < *it2) {
            it1++;
            }

            if (it2 != all_dont.end()) {
            ranges.push_back(std::pair(curr, *it2));
            }

        } else if (*it1 > *it2) {

            if (it2 != all_dont.end()) {
            it2++;
            }

        }

    }

    for (int i = 0; i < all_multiplications.size(); ++i) {
        
        for (int j = 0; j < ranges.size(); ++j) {
            if (is_between(all_multiplications[i].first, ranges[j].first, ranges[j].second)) {
                res += all_multiplications[i].second;
            }
        }
    }

    std::cout << res;

    return 0;

}