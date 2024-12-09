#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<int> disk;

int main() {

    std::fstream file("inputs/input.txt");
    bool is_file = true;

    if (file.is_open()) {

        char c;
        int file_ID = 0;

        while (file.get(c)) {
            if (is_file) {
                for (int i = 0; i < (c - '0'); i++) {
                    disk.push_back(file_ID);
                }
                file_ID++;
                is_file = false;
            } else {
                for (int i = 0; i < (c - '0'); i++) {
                    disk.push_back(-1);
                }
                is_file = true;
            }
        }

    }
    
    file.close();

    auto it1 = disk.begin();
    auto it2 = disk.end()-1;

    while (it1 < it2) {

        while (it1 < it2 && *it1 != -1) {
            it1++;
        }

        while (it1 < it2 && *it2 == -1) {
            it2--;
        }

         if (it1 < it2) {
            std::swap(*it1, *it2);
        }

    }

    long long res = 0;

    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] != -1) res+= i*disk[i];
    }

    std::cout << res;

    return 0;

}