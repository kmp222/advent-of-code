#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <numeric>

std::vector<long long> node_iterations_for_z;

void remove_nodes_ending_with_z(std::vector<std::string> &keys, long long steps) {

    for (std::string k : keys) {
        
        if ( (k[2] == 'Z') ) {

            node_iterations_for_z.push_back(steps);
            
            for (int i = 0; i < keys.size(); i++) {
                if (keys[i] == k) {
                    keys.erase(keys.begin()+i);
                }
            }
        }

    } 

}

int main() {

    std::ifstream file("inputs/day8_input.txt");
    std::string instructions = "LRLRRLRLRLLRRRLLLRLLRRLLRRRLRLRLRRRLRRLRLRRRLRRRLRRRLRRRLRRLRRRLRRRLRRLLLRLLRLRRRLRRRLRRLRLRLRLRRRLRRRLRRRLRRLRRLRRLLRRLRRRLLRRLRRRLRRRLRRRLRLRRLRLRRRLRRLLRLRLLRLRLRRRLRLRRLLRRRLRLRLRLRLRLRRLRLRRLLLLRRLRRLRRRLRRLRRLRRRLRRLRRRLLRLRRLLRLRRLRRLRRLLRRRLRLRLRRRLRRLRLLRLRRRR";
    // std::ifstream file("inputs/day8_2_input_example.txt");
    // std::string instructions = "LR";
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
    long long steps = 0;
    std::vector<std::string> keys;

    for (const auto& entry : map) {
        if (entry.first[2] == 'A') {
            keys.push_back(entry.first);
        }
    }

    while (!keys.empty()) {
    
        steps++;

        if (counter_instruction == instructions.length()) {
            counter_instruction = 0;
        }

        char instruction = instructions[counter_instruction];

        for (int i = 0; i < keys.size(); i++) {

            std::string next_node;

            if (instruction == 'L') {

                next_node = map.find(keys[i])->second.first;

            } else if (instruction == 'R') {

                next_node = map.find(keys[i])->second.second;

            }

            keys[i] = next_node;

        }
        
        remove_nodes_ending_with_z(keys, steps);

        counter_instruction++;

    }

    file.close();

    long long lcm = node_iterations_for_z[0];

    for (int i = 1; i < node_iterations_for_z.size(); i++) {

        lcm = std::lcm(lcm, node_iterations_for_z[i]);

    }

    std::cout << lcm << std::endl;

    return 0;

}