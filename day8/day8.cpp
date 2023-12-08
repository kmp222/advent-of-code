#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

int main() {

    std::ifstream file("inputs/day8_input.txt");
    std::string instructions = "LRLRRLRLRLLRRRLLLRLLRRLLRRRLRLRLRRRLRRLRLRRRLRRRLRRRLRRRLRRLRRRLRRRLRRLLLRLLRLRRRLRRRLRRLRLRLRLRRRLRRRLRRRLRRLRRLRRLLRRLRRRLLRRLRRRLRRRLRRRLRLRRLRLRRRLRRLLRLRLLRLRLRRRLRLRRLLRRRLRLRLRLRLRLRRLRLRRLLLLRRLRRLRRRLRRLRRLRRRLRRLRRRLLRLRRLLRLRRLRRLRRLLRRRLRLRLRRRLRRLRLLRLRRRR";
    // std::ifstream file("inputs/day8_input_example.txt");
    // std::string instructions = "RL";
    std::string line;
    std::regex pattern("([A-Z]+) = \\(([A-Z]+),\\s*([A-Z]+)\\)");
    std::smatch match;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    if (file.is_open()) {

        while(std::getline(file, line)) {

            if (std::regex_search(line, match, pattern)) {
           
                map.insert({match[1], {match[2], match[3]}});

            }

        }

    }

    int counter_instruction = 0;
    int steps = 0;
    std::string key =  "AAA";

    while (key != "ZZZ") {
    
        steps++;

        if (counter_instruction == instructions.length()) {
            counter_instruction = 0;
        }

        char instruction = instructions[counter_instruction];

        std::string next_node;

        if (instruction == 'L') {

            next_node = map.find(key)->second.first;

        } else if (instruction == 'R') {

            next_node = map.find(key)->second.second;

        }

        key = next_node;
        counter_instruction++;

    }

    file.close();

    std::cout << steps << std::endl;

    return 0;

}