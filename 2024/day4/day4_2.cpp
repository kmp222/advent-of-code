#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::vector<char>> matrix;

int cross_search(int i, int j) {

    char upleft_corner = matrix[i-1][j-1];
    char downright_corner = matrix[i+1][j+1];
    char upright_corner = matrix[i-1][j+1];
    char downleft_corner = matrix[i+1][j-1];

    bool c1 = upleft_corner == 'M' && downright_corner == 'S' && upright_corner == 'S' && downleft_corner == 'M';
    bool c2 = upleft_corner == 'M' && downright_corner == 'S' && upright_corner == 'M' && downleft_corner == 'S';
    bool c3 = upleft_corner == 'S' && downright_corner == 'M' && upright_corner == 'S' && downleft_corner == 'M';
    bool c4 = upleft_corner == 'S' && downright_corner == 'M' && upright_corner == 'M' && downleft_corner == 'S';

    if (c1 || c2 || c3 || c4) return 1;

    return 0; 

}

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
    std::string s = "MAS";

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {

            if (matrix[i][j] == 'A') {
                res += cross_search(i, j);
            }

        }
    }

    std::cout << res;

    return 0;

}