#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

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

    int i = disk.size()-1;
    int file_ID = 0;

    std::set<int> checkedIDs;

    while (i >= 0) {

        bool has_been_checked = false;

        for (auto &id : checkedIDs) {
            if (disk[i] == id) {
                has_been_checked = true;
                break;
            }
        }

        if (disk[i] != -1 && !has_been_checked) {
            file_ID = disk[i];
            checkedIDs.insert(file_ID);
        } else {
            i--;
            continue;
        }

        int file_size = 0;

        while (i >= 0 && disk[i] == -1) {
            i--;
        }

        if (i < 0) break;

        while (i >= 0 && disk[i] != -1 && disk[i] == file_ID) {
            file_size++;
            i--;
        }
        
        int j = 0;

        while (j < disk.size() && i >= 0) {

            int space_size = 0;

            while (j < disk.size() && disk[j] != -1) {
                j++;
            }

            int space_start = j;

            if (space_start >= i) {
                break;
            }

            while (j < disk.size() && disk[j] == -1) {
                space_size++;
                j++;
            }

            if (space_size >= file_size) {

            for (int k = 0; k < file_size; k++) {
                disk[i+1+k] = -1;
                disk[space_start+k] = file_ID;
            }

            break;

            }

        }

    }

    long long res = 0;

    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] != -1) res+= i*disk[i];
    }

    std::cout << res;

    return 0;

}