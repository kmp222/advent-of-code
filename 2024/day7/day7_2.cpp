#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

bool func(std::vector<int> &numbers, int index, long long current, long long test) {

    if (index == numbers.size()) {
        return current == test;
    }

    long long concat_number = std::stoll( std::to_string(current) +
                                    std::to_string(numbers[index]) );

    return func(numbers, index + 1, current + numbers[index], test) ||
           func(numbers, index + 1, current * numbers[index], test) ||
           func(numbers, index + 1, concat_number, test);

}

int main() {

    std::fstream file("inputs/input.txt");

    long long res = 0;

    if (file.is_open()) {

        std::string line;
        while (std::getline(file, line)) {

                std::istringstream iss(line);
                long long test;
                int n;
                std::vector<int> numbers;

                iss >> test;

                while (iss >> n) {
                    numbers.push_back(n);
                }

                if (func(numbers, 1, numbers[0], test)) {
                    res += test;
                }

        }

    }
    
    file.close();

    std::cout << res;

    return 0;

}