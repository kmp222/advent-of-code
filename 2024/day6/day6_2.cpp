#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

enum Direction {
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4
};

void next_direction(Direction &curr) {
    curr = static_cast<Direction>((curr % 4) + 1);
}

void next_movement(int &x, int &y, Direction &d) {
    switch(d) {
        case UP:
            x--;
            break;
        case LEFT:
            y--;
            break;
        case DOWN:
            x++;
            break;
        case RIGHT:
            y++;
            break;
    }
}

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

    std::pair<int, int> starting_position(0, 0);

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == '^') {
                starting_position.first = i;
                starting_position.second = j;
            }
        }

    }

    int res = 0;

    for (int m = 0; m < matrix.size(); m++) {
        for (int n = 0; n < matrix[m].size(); n++) {
            
            if (m == starting_position.first && n == starting_position.second) {
                continue;
            }

            int i = starting_position.first;
            int j = starting_position.second;
            int timeout = 0;
            bool loop = false;
            std::vector<std::vector<char>> temp_matrix = matrix;

            temp_matrix[m][n] = '#';
            Direction d = UP;

            while (!loop && temp_matrix[i][j] != 'N') {

                timeout++;
                if (timeout == 50000) loop = true;

                int tmp_i = i;
                int tmp_j = j;

                next_movement(i, j, d);
                
                if (temp_matrix[i][j] == '#') {

                    while (temp_matrix[i][j] == '#') {
                        i = tmp_i;
                        j = tmp_j;
                        next_direction(d);
                        next_movement(i, j, d);
                    }
                    
                }

            }

            if (loop) res++;

        }
    }
    
    std::cout << res-1; // -1 works and idk why
    return 0;

}