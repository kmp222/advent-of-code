#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

/*
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
*/

/*  for (int i; ss >> i;) {
        vect.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }*/

std::vector<std::vector<char>> matrix;

int main() {

    std::fstream file("inputs/input.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream iss(line);
                char c;
                std::vector<char> row;
                while (iss >> c) {
                    row.push_back(c);
                }

                matrix.push_back(row);
        }

    }
    
    file.close();

    int res = 0;

    std::cout << res;

    return 0;

}