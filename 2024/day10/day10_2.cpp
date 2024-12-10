#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <set>

int result = 0;
std::vector<std::vector<int>> matrix;
std::set<std::pair<int, int>> explored;

void bfs(std::pair<int, int> trailhead) {

    std::queue<std::pair<int, int>> queue;
    explored.insert(trailhead);
    queue.push(trailhead);

    while (!queue.empty()) {

        std::pair<int, int> v = queue.front();
        queue.pop();

        if (matrix[v.first][v.second] == 9) {
            result++;
            continue;
        }
        
        std::vector<std::pair<int, int>> adjs;
        adjs.push_back(std::make_pair(v.first+1, v.second));
        adjs.push_back(std::make_pair(v.first, v.second+1));
        adjs.push_back(std::make_pair(v.first, v.second-1));
        adjs.push_back(std::make_pair(v.first-1, v.second));

        for (std::pair adj : adjs) {
            
            bool exp = false;

            for (auto &i : explored) {

                if (adj.first == i.first && adj.second == i.second) {
                    exp = false;
                    break;
                }

            }

            if (!exp && matrix[adj.first][adj.second] != -1 &&
                matrix[adj.first][adj.second] == matrix[v.first][v.second]+1) {
                explored.insert(adj);
                queue.push(adj);
            }

        }   

    }

}

int main() {

    std::fstream file("inputs/input.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream iss(line);
                char c;
                std::vector<int> row;
                while (iss >> c) {
                    int number = 0;
                    if (c == 'X') {
                        number = -1;
                    } else {
                        number = c - '0';
                    }
                    row.push_back(number);
                }
                matrix.push_back(row);
        }
    }
    
    file.close();

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            if (matrix[i][j] == 0) {
                std::pair<int, int> p(i, j);
                bfs(p);
                explored.clear();
            }

        }
    }

    std::cout << result;

    return 0;

}