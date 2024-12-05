#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

std::vector<std::pair<int, int>> pages;

bool find_pages_rule(std::pair<int, int> p) {

    for (int i = 0; i < pages.size(); i++) {
        if (p.first == pages[i].first &&
            p.second == pages[i].second) {
                return true;
            }
    }

    return false;
}

void insertion_sort(std::vector<int> &arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        std::pair p(key, arr[j]);
        while (j >= 0 && find_pages_rule(p)) {
            arr[j + 1] = arr[j];
            j = j - 1;
            p.second = arr[j];
        }
        arr[j + 1] = key;
    }
}

int main() {

    int res = 0;

    std::fstream file("inputs/input_pages.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {

            int n = std::stoi(line.substr(0,2));
            int m = std::stoi(line.substr(3,2));
            pages.push_back(std::pair(n,m));

        }

    }

    file.close();

    std::fstream file2("inputs/input_updates.txt");

    if (file2.is_open()) {

        std::string line;

        while (std::getline(file2, line)) {

            bool correct_update = true;
            std::vector<int> update;
            std::stringstream ss(line);

            for (int i; ss >> i;) {
                update.push_back(i);    
                if (ss.peek() == ',')
                    ss.ignore();
            }

            for (int i = 0; i < update.size()-1; i++) {
                int n = update[i];
                int m = update[i+1];
                std::pair p(n, m);

                if (!find_pages_rule(p)) {
                    correct_update = false;
                    break;
                }
            }
 
            if (!correct_update) {

                insertion_sort(update, update.size());
                res += update[(update.size()-1)/2];
            }
        
        }
    }

    file2.close();

    std::cout << res;

    return 0;

}