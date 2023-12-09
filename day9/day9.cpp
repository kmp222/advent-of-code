#include <iostream>
#include <fstream>
#include <regex>

long calculate_next_number(std::vector<int> riga) {

    if (std::all_of(riga.begin(), riga.end(), [](int val) { return val == 0; })) {
        return 0;
    }

    std::vector<int> differences;

    long result = 0;

    for (int i = 0; i < riga.size()-1; i++) {

        differences.push_back(riga[i+1] - riga[i]);

    }

    result = calculate_next_number(differences) + riga[riga.size()-1];

    return result;
    
}

int main() {

    std::fstream file("inputs/day9_input.txt");
    // std::fstream file("inputs/day9_input_example.txt");

    std::regex pattern("-?\\b\\d+\\b");
    std::smatch match;

    long sum = 0;

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            std::sregex_iterator iter(line.begin(), line.end(), pattern);
            std::sregex_iterator end;
            std::vector<int> riga;

            while (iter != end) {
                std::smatch match = *iter;
                riga.push_back(std::stoi(match.str()));
                ++iter;
            }

            sum += calculate_next_number(riga);

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}