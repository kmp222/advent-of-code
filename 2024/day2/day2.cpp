#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {

    std::fstream file("inputs/input.txt");
    std::string line;

    std::vector< std::vector<int> > numbers;

    if (file.is_open()) {
        
        while (std::getline(file, line)) {

            std::istringstream iss(line);
            std::vector<int> row;
            int n;
            while (iss >> n) {
                row.push_back(n);
            }

            numbers.push_back(row);
        }

    }

    file.close();

    int res = 0;

    for (int i = 0; i < numbers.size(); ++i) {
        bool order = true; // false = asc, true = desc 
        if (numbers[i][1] > numbers[i][0]) {
            order = false;
        }

        bool safe = true;
        int prev = numbers[i][1];

        if (abs(numbers[i][1] - numbers[i][0]) == 0 ||
                abs(numbers[i][1] - numbers[i][0]) > 3) {
                    safe = false;
                }

        for (int j = 2; j < numbers[i].size(); ++j) {

            int curr = numbers[i][j];

            if (!safe) {
                break;
            }

            if ( ( curr > prev &&
                order == true ) ||
                ( curr < prev &&
                order == false )
                ) {
                    safe = false;
                }

            if (abs(curr - prev) == 0 ||
                abs(curr - prev) > 3) {
                    safe = false;
                }

            prev = numbers[i][j];

        }

        if (safe) {
            res++;
        }

    }

    std::cout << res;

    return 0;

}
