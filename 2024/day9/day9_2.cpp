#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<int> disk;

int main() {

    std::fstream file("inputs/input_ex.txt");
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

    while (i >= 0) {

        if (i == disk.size()-1) {
            file_ID = disk[i];
        } else {
            if (disk[i] < file_ID) file_ID = disk[i];
            else {
                file_ID = 0;
                i--;
            }
        }

        if (file_ID == 0) continue;

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

        while (j < disk.size() && i > 0) {

            int space_size = 0;
        
            while (j < disk.size() && disk[j] != -1) {
                j++;
            }

            int space_start = j;

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