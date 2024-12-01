#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

int MAX_SIZE = 1000;

bool comp(int a, int b) {
    return a >= b;
}

int main() {

    std::fstream file("inputs/input.txt");
    std::string line;

    std::vector<int> first_row;
    std::vector<int> second_row;

    if (file.is_open()) {

        while (std::getline(file, line)) {
        std::istringstream iss(line);
        int n, m;
        iss >> n >> m;
        first_row.push_back(n);
        second_row.push_back(m);
        }

    }

    file.close();

    int res = 0;

    for (int i = 0; i < MAX_SIZE; ++i) {
        int n = first_row[i];
        int repetitions = 0;
        for (int j = 0; j < MAX_SIZE; ++j) {
            if (second_row[j] == n) {
                repetitions++;
            }
        }

        res += n*repetitions;
    }

    std::cout << res;
    
    return 0;

}

