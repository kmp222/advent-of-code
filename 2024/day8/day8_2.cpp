#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <unordered_map>
#include <cstdlib>

std::vector<std::vector<char>> matrix;
std::set<char> frequencies;
std::vector<std::pair<char, std::pair<int, int>>> frequencies_location;
std::set<std::pair<int, int>> antipoints;

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
                    if (c != '.') {
                        frequencies.insert(c);
                    }
                }

                matrix.push_back(row);
        }

    }
    
    file.close();

    size_t num_rows = matrix.size();
    size_t num_cols = matrix.empty() ? 0 : matrix[0].size();

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != '.') {
                frequencies_location.push_back(
                    std::make_pair(matrix[i][j], std::make_pair(i, j))
                );
            }
        }
    }

    for (char symbol : frequencies) {

        for (const auto& f : frequencies_location) {

            if (f.first == symbol) {

                for (const auto& f2 : frequencies_location) {
                    if (f2.first == symbol &&
                        f.second.first != f2.second.first && f.second.second != f2.second.second) {
                        
                        antipoints.insert(std::make_pair(f.second.first, f.second.second));
                        antipoints.insert(std::make_pair(f2.second.first, f2.second.second));

                        std::pair antipoint1(0, 0);
                        std::pair antipoint2(0, 0);
                        
                        int d_x = std::abs(f.second.first - f2.second.first);
                        int d_y = std::abs(f.second.second - f2.second.second);

                        if (f.second.first <= f2.second.first) {
                            antipoint1.first = f.second.first - d_x;
                            antipoint2.first = f2.second.first + d_x;
                        } else {
                            antipoint1.first = f.second.first + d_x;
                            antipoint2.first = f2.second.first - d_x;
                        }

                        if (f.second.second <= f2.second.second) {
                            antipoint1.second = f.second.second - d_y;
                            antipoint2.second = f2.second.second + d_y;
                        } else {
                            antipoint1.second  = f.second.second + d_y;
                            antipoint2.second  = f2.second.second - d_y;
                        }

                        int new_x = antipoint1.first;
                        int new_y = antipoint1.second;

                        while ( (new_y >= 0 && new_y < num_rows) && (new_x >= 0 && new_x < num_cols)) {

                            antipoints.insert(std::make_pair(new_x, new_y));

                            if (f.second.first <= f2.second.first) {
                                new_x = new_x - d_x;
                            } else {
                                new_x = new_x + d_x;
                            }
                            if (f.second.second <= f2.second.second) {
                                new_y = new_y - d_y;
                            } else {
                                new_y = new_y + d_y;
                            }

                        }

                        new_x = antipoint2.first;
                        new_y = antipoint2.second;

                        while ( (new_y >= 0 && new_y < num_rows) && (new_x >= 0 && new_x < num_cols)) {

                            antipoints.insert(std::make_pair(new_x, new_y));

                            if (f.second.first <= f2.second.first) {
                                new_x = new_x + d_x;
                            } else {
                                new_x = new_x - d_x;
                            }
                            if (f.second.second <= f2.second.second) {
                                new_y = new_y + d_y;
                            } else {
                                new_y = new_y - d_y;
                            }

                        }

                    }
                }

            }
        }

    }

    std::cout << antipoints.size() << std::endl;

    return 0;

}