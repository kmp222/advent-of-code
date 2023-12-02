#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

const int red = 12;
const int green = 13;
const int blue = 14;

// controlla su una riga che ogni token 'numero + colore' rispetti le indicazioni
bool check_cubes_color(const std::string& line, const std::regex& pattern) {

    bool valid_color = false;

    std::smatch match;
    std::string::const_iterator searchStart(line.cbegin());

    // trova tutte le occorrenze del pattern nella linea
    while (std::regex_search(searchStart, line.cend(), match, pattern)) {

        int n_cubes = std::stoi(match[1]);
        std::string color = match[2];

        if (color == "red" && n_cubes <= red) {
            valid_color = true;
        } else if (color == "green" && n_cubes <= green) {
            valid_color = true;
        } else if (color == "blue" && n_cubes <= blue) {
            valid_color = true;
        } else {
            valid_color = false;
            break;
        }

        searchStart = match.suffix().first;

    }

    return valid_color;

}

int main() {

    int sum = 0;

    bool valid_line = false;
    int game_id = 0;

    std::regex pattern1("(\\d+)\\s+(red)");
    std::regex pattern2("(\\d+)\\s+(green)");
    std::regex pattern3("(\\d+)\\s+(blue)");

    std::ifstream file("day2_input.txt");
    // std::ifstream file("day2_input_example.txt");

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            valid_line = false;
            game_id++;

            valid_line = ( 
                            check_cubes_color(line, pattern1) &&
                                check_cubes_color(line, pattern2) &&
                                    check_cubes_color(line, pattern3)
                    );

            if (valid_line) {

                sum += game_id;

            }

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}