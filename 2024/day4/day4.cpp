#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::vector<char>> matrix;

int neighbor_search(const std::string &s, int i, int j) {
    
    int res = 0;
    int i_og = i;
    int j_og = j;

    // check right
    int k = 0;
    bool occ = true;
    while (occ && k < s.length()) {
        if (matrix[i][j+1] == s.at(k)) {
            k++;
            j++;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check left
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i][j-1] == s.at(k)) {
            k++;
            j--;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check down
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i+1][j] == s.at(k)) {
            k++;
            i++;
        } else {
            occ = false;
        }
    }
    if (occ) res++;
    
    // check up
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i-1][j] == s.at(k)) {
            k++;
            i--;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check right-up
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i-1][j+1] == s.at(k)) {
            k++;
            i--; j++;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check right-down
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i+1][j+1] == s.at(k)) {
            k++;
            i++; j++;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check left-up
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i-1][j-1] == s.at(k)) {
            k++;
            i--; j--;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    // check left-down
    k = 0; occ = true; i = i_og; j = j_og;
    while (occ && k < s.length()) {
        if (matrix[i+1][j-1] == s.at(k)) {
            k++;
            i++; j--;
        } else {
            occ = false;
        }
    }
    if (occ) res++;

    return res;

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

            if (matrix[i][j] == 'X') {
                res += neighbor_search(s, i, j);
            }

        }
    }

    std::cout << res;

    return 0;

}