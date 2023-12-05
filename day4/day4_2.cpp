#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

std::regex pattern(R"(\d+)");
std::smatch match;
std::vector<std::string> file_lines;

char delimiter = '|';

int scratchcards = 0;

void print_vector(const std::vector<int>& v) {
    for (int element : v) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void create_scratchcards(std::string line, std::vector<int>& my_nums, std::vector<int>& w_nums, std::vector<std::string>& tokens) {

    std::string token;
        
    line = line.substr(line.find(": ") + 2); // rimuovi token card

    std::istringstream stream(line);

    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token); // dividi le due liste
    }

    // aggiungi le liste di numeri in vettori
    std::regex pattern(R"(\d+)");
    std::smatch match;

    for (int i = 0; i < 2; i++) {

        std::string::const_iterator searchStart(tokens[i].cbegin());

        while (std::regex_search(searchStart, tokens[i].cend(), match, pattern)) {
            
            if (i == 0) {
                w_nums.push_back(std::stoi(match[0]));
            } else {
                my_nums.push_back(std::stoi(match[0]));
            }

            searchStart = match.suffix().first;

        }

    }

}

int get_wins(std::vector<int>& my_nums, std::vector<int>& w_nums) {

    int wins = 0;

    for (int my_num : my_nums) {

                for (int winning_num : w_nums) {

                    if (my_num == winning_num) {
                        wins++;
                    }

                }

    }

    return wins;

}

std::vector<std::string> read_lines(const std::string& filename) {

    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "err"<< std::endl;
    }

    return lines;

}


int main() {

    file_lines = read_lines("inputs/day4_input.txt");
    // file_lines = read_lines("inputs/day4_input_example.txt");

    std::vector<int> matches;
    std::vector<int> total;

    for (int i = 0; i < file_lines.size(); i++) {
        
        std::vector<int> my_nums;
        std::vector<int> w_nums;
        std::vector<std::string> tokens;

        create_scratchcards(file_lines[i], my_nums, w_nums, tokens);

        int wins = get_wins(my_nums, w_nums);
        matches.push_back(wins);
        total.push_back(1);

    }

    for (int i = 0; i < total.size(); i++) {

        for (int j = 0; j < matches[i]; j++) {

            total[i+j+1] = total[i+j+1] + total[i];

        }

    }

    for (int i = 0; i < total.size(); i++) {
        scratchcards += total[i];
    }

    std::cout << scratchcards << std::endl;

    return 0;

}