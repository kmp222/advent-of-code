#include <iostream>
#include <fstream>
#include <regex>

// controlla su una riga che ogni token 'numero + colore' rispetti le indicazioni
bool check_cubes_color(const std::string& line, const std::regex& pattern, const int n_cubes_color) {

    bool valid_color = false;

    std::smatch match;
    std::string::const_iterator searchStart(line.cbegin());

    // trova tutte le occorrenze del pattern nella linea
    while (std::regex_search(searchStart, line.cend(), match, pattern)) {

        int n_cubes = std::stoi(match[1]);

        if (n_cubes <= n_cubes_color) {
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

    const int red = 12;
    const int green = 13;
    const int blue = 14;

    int sum = 0;

    bool valid_line = false;
    int game_id = 0;

    std::regex pattern1("(\\d+)\\s+(red)");
    std::regex pattern2("(\\d+)\\s+(green)");
    std::regex pattern3("(\\d+)\\s+(blue)");

    std::ifstream file("inputs/day2_input.txt");
    // std::ifstream file("inputs/day2_input_example.txt");

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            valid_line = false;
            game_id++;

            valid_line = ( 
                            check_cubes_color(line, pattern1, red) &&
                                check_cubes_color(line, pattern2, green) &&
                                    check_cubes_color(line, pattern3, blue)
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