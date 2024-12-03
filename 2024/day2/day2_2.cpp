#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

bool is_ascending(std::vector<int> &numbers) {

    int prev = numbers[0];
    bool b = true;

    for (int i = 1; i < numbers.size(); ++i) {
        int curr = numbers[i];
        if (curr < prev){
            b = false;
            break;
        }
        prev = curr;
    }

    return b;

}

bool is_descending(std::vector<int> &numbers) {

    int prev = numbers[0];
    bool b = true;

    for (int i = 1; i < numbers.size(); ++i) {
        int curr = numbers[i];
        if (curr > prev){
            b = false;
            break;
        }
        prev = curr;
    }

    return b;

}

bool is_bounded(std::vector<int> &numbers) {
    int prev = numbers[0];
    bool b = true;

    for (int i = 1; i < numbers.size(); ++i) {
        int curr = numbers[i];
        if (abs(curr-prev) == 0 ||
            abs(curr-prev) > 3) {
                b = false;
                break;
        }
        prev = curr;
    }

    return b;

}

int main() {

    std::fstream file("inputs/input.txt");
    std::string line;

    std::vector< std::vector<int> > numbers;

    if (file.is_open()) {
        
        int i = 0;
        
        while (std::getline(file, line)) {

            std::istringstream iss(line);
            std::vector<int> row;
            int n;
            while (iss >> n) {
                row.push_back(n);
            }

            numbers.push_back(row);
            i++;

        }

    }

    file.close();

    int res = 0;

    
    for (int i = 0; i < numbers.size(); ++i) {
       
        bool safe = false;

        for (int j = 0; j < numbers[i].size(); ++j) {
            
            std::vector<int> numbers_tmp;

            for (int k = 0; k < numbers[i].size(); ++k) {

                if (k != j) {
                    numbers_tmp.push_back(numbers[i][k]);
                }

            }

            if (is_bounded(numbers_tmp)) {
                    if (is_ascending(numbers_tmp) ||
                        is_descending(numbers_tmp)) {
                            safe = true;
                            break;
                    }
            }

        }

        if (safe) res++;

    }

    std::cout << res;

    return 0;

}
