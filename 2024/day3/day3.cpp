#include <iostream>
#include <fstream>
#include <regex>

int main() {

    std::fstream file("inputs/input.txt");

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    file.close();

    std::regex pattern(R"(mul\((\d+),(\d+)\))");

    std::sregex_iterator currentMatch(content.begin(), content.end(), pattern);
    std::sregex_iterator lastMatch;

    long res = 0;

    while (currentMatch != lastMatch) {
        
        std::smatch match = *currentMatch;
        std::string num1 = match[1];
        std::string num2 = match[2];

        res += (std::stoi(num1)*std::stoi(num2));

        ++currentMatch;

    }

    std::cout << res;

    return 0;

}