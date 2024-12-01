#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool func(std::string springs, std::vector<int> qmark_pos, int pos, char c, std::vector<int>* groups) {

    if (pos <= qmark_pos.size()) {
        springs[qmark_pos[pos]] = c;
    }

    for (char c : springs) {
        if (c == '?') {
            func(springs, qmark_pos, pos+1, '.', groups);
            func(springs, qmark_pos, pos+1, '#', groups);
        }
    }

}
int main() {

    // std::fstream file("inputs/day12_input.txt");
    std::fstream file("inputs/day12_input_example.txt");

    std::string line;

    if (file.is_open()) {

        while(std::getline(file, line)) {

            std::string springs;
            std::vector<int> groups;

            std::stringstream ss(line);
            ss >> springs;
            ss.ignore(1, ' ');
            std::string number;
            while (std::getline(ss, number, ',')) {
                groups.push_back(std::stoi(number));
            }

            std::vector<int> qmark_pos;

            for (int i = 0; i < springs.size(); i++) {
                if (springs[i] == '?') {
                    qmark_pos.push_back(i);
                }
            }

            std::string springs_copy = springs;
            func(springs_copy, qmark_pos, 0, '.', &groups);
            func(springs_copy, qmark_pos, 0, '#', &groups);


        }
        
    }

    return 0;

}