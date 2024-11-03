#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

struct Galaxy {
    int x;
    int y;
};

int main() {

    const int size1 = 140;
    const int size2 = 140;
    // const int size1 = 10;
    // const int size2 = 10;

    std::vector<std::vector<char>> universe(size1, std::vector<char>(size2));

    std::fstream file("inputs/day11_input.txt");
    // std::fstream file("inputs/day11_input_example.txt");

    std::vector<Galaxy> galaxies;

    if (file.is_open()) {

        std::string line;
        int row = 0;

        while (std::getline(file, line)) {

            for (int column = 0; column < size2; column++) {

                universe[row][column] = line[column];
                if (universe[row][column] == '#') {
                    Galaxy g;
                    g.x = row;
                    g.y = column;
                    galaxies.push_back(g);
                }

            }

            row++;
        }
    }

    file.close();

    // get rows and columns expanded
    bool is_empty = true;
    std::vector<int> rows_expanded;
    std::vector<int> columns_expanded;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (universe[i][j] == '#') {
                is_empty = false;
                break;
            }
        }
        if (is_empty) {
            rows_expanded.push_back(i);
        }
        is_empty = true;
    }

    for (int j = 0; j < size2; j++) {
        for (int i = 0; i < size1; i++) {
            if (universe[i][j] == '#') {
                is_empty = false;
                break;
            }
        }
        if (is_empty) {
            columns_expanded.push_back(j);
        }
        is_empty = true;
    }

    long long sum = 0;

    for (int i = 0; i < galaxies.size(); i++) {

        Galaxy g = galaxies[i];

        for (int j = i; j < galaxies.size(); j++) {

            Galaxy g2 = galaxies[j];        
            long long increment = 0;

            for (int r : rows_expanded) {
                if (r < std::max(g.x, g2.x) && r > std::min(g.x, g2.x)) {
                    increment = increment + 1000000 - 1;
                }
            }

            for (int c : columns_expanded) {
                if (c < std::max(g.y, g2.y) && c > std::min(g.y, g2.y)) {
                    increment = increment + 1000000 - 1;
                }
            }

            sum += ( (abs(g.x - g2.x)) + (abs(g.y - g2.y)) + increment );
        }

    }

    std::cout << sum << std::endl;

    return 0;

}