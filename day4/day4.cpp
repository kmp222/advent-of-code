#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <cmath>

std::regex pattern(R"(\d+)");
std::smatch match;

std::vector<int> my_numbers;
std::vector<int> winning_numbers;

int sum = 0;

void print_vector(const std::vector<int>& v) {
    for (int element : v) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::ifstream file("inputs/day4_input.txt");
    // std::ifstream file("inputs/day4_input_example.txt");
    
    if (file.is_open()) {

        std::string line;
        std::vector<std::string> tokens;

        char delimiter = '|';

        while (std::getline(file, line)) {

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
                        winning_numbers.push_back(std::stoi(match[0]));
                    } else {
                        my_numbers.push_back(std::stoi(match[0]));
                    }

                    searchStart = match.suffix().first;

                }

            }

            int winning_matches = -1; // exploit pow(2, winning_matches)

            for (int my_num : my_numbers) {

                for (int winning_num : winning_numbers) {

                    if (my_num == winning_num) {
                        winning_matches++;
                    }

                }

            }

            if (winning_matches != -1) {
                sum += pow(2, winning_matches);
            }

            tokens.clear();
            winning_numbers.clear();
            my_numbers.clear();

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}