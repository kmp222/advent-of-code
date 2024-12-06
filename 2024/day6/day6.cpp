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

Direction next_direction(Direction curr) {
    return static_cast<Direction>((curr % 4) + 1);
}

std::vector<std::vector<char>> matrix;

void walk(std::pair<int, int> position, Direction d) {

    int next_x = position.first;
    int next_y = position.second;

    switch(d) {
        case UP:
            next_x--;
            break;
        case LEFT:
            next_y--;
            break;
        case DOWN:
            next_x++;
            break;
        case RIGHT:
            next_y++;
            break;
    }
    
    if (matrix[next_x][next_y] == 'N') {
        if (! (matrix[position.first][position.second] == 'X'))
            matrix[position.first][position.second] = 'X';
    }

    matrix[position.first][position.second] = 'X';

    if (matrix[next_x][next_y] == '.') {

        std::pair<int, int> p(next_x, next_y);
        walk(p, d);

    } else if (matrix[next_x][next_y] == 'X') {

        std::pair<int, int> p(next_x, next_y);
        walk(p, d);
        
    } else if (matrix[next_x][next_y] == '#') {

        Direction new_d = d; // placeholder value

        while (matrix[next_x][next_y] == '#') {
            
            new_d = next_direction(new_d);

            next_x = position.first;
            next_y = position.second;

            switch(new_d) {
                case UP:
                    next_x--;
                    break;
                case LEFT:
                    next_y--;
                    break;
                case DOWN:
                    next_x++;
                    break;
                case RIGHT:
                    next_y++;
                    break;
            }

        }

        std::pair<int, int> p(next_x, next_y);
        
        walk(p, new_d);

    }

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

    std::pair<int, int> starting_position(0, 0);

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == '^') {
                starting_position.first = i;
                starting_position.second = j;
            }
        }

    }

    walk(starting_position, UP);

    int res = 0;
    
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 'X') res++;
        }
    }  

    std::cout << res;

    return 0;

}