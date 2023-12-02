#include <iostream>
#include <fstream>
#include <regex>

// controlla su una riga che ogni token 'numero + colore' rispetti le indicazioni
int few_cubes_color(const std::string& line, const std::regex& pattern) {

    int few_color = 0;

    std::smatch match;
    std::string::const_iterator searchStart(line.cbegin());

    // trova tutte le occorrenze del pattern nella linea
    while (std::regex_search(searchStart, line.cend(), match, pattern)) {

        int n_cubes = std::stoi(match[1]);
       
        if (n_cubes > few_color) {
            few_color = n_cubes;
        }

        searchStart = match.suffix().first;

    }

    return few_color;

}

int main() {

    int sum = 0;

    std::regex pattern1("(\\d+)\\s+(red)");
    std::regex pattern2("(\\d+)\\s+(green)");
    std::regex pattern3("(\\d+)\\s+(blue)");

    std::ifstream file("day2_input.txt");
    // std::ifstream file("day2_input_example.txt");

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            int few_red = few_cubes_color(line, pattern1);
            int few_green = few_cubes_color(line, pattern2);
            int few_blue = few_cubes_color(line, pattern3);
        
            int set_power = (few_red * few_green * few_blue);
            
            sum += set_power;

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}