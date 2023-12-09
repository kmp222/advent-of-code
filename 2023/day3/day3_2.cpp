#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> matrix;
int numRighe = 0;
int numColonne = 0;
int sum = 0;

struct Coord {

    int x;
    int y;

};


void populate_matrix(std::ifstream& file) {

    // leggi il file e salva ogni riga nel vettore
    std::string riga;
    while (std::getline(file, riga)) {
        matrix.push_back(riga);
    }

    file.close();

    // determina il numero di righe e colonne
    numRighe = matrix.size();
    numColonne = (numRighe > 0) ? matrix[0].size() : 0;

}

void print_matrix() {

    for (int i = 0; i < numRighe; i++) {
        for (int j = 0; j < numColonne; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}




int find_num(int xMatrice, int yMatrice) {

    std::string num = "";
    int yTemp = yMatrice;
    int yTemp2 = yMatrice+1;

    while (std::isdigit(matrix[xMatrice][yTemp])) {

        num += matrix[xMatrice][yTemp];
        yTemp--;

    }

    std::reverse(num.begin(), num.end());

    while (std::isdigit(matrix[xMatrice][yTemp2])) {

        num += matrix[xMatrice][yTemp2];
        yTemp2++;

    }
    
    return std::stoi(num);

}

// buffer per due adj per ogni gear
std::vector<int> numbers = {};

void gear_adj_numbers(int i, int j) {

    std::vector<Coord> bordo = {

        {i, j-1},
        {i, j+1},
        {i-1, j-1},
        {i-1, j},
        {i-1, j+1},
        {i+1, j-1},
        {i+1, j},
        {i+1, j+1}

    };

    for (Coord c : bordo) {

        if (std::isdigit(matrix[c.x][c.y])) {

            int numero = find_num(c.x, c.y);

            // evito doppioni
            bool found = false;
            for (int element : numbers) {
                if (element == numero) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                    numbers.push_back(numero);
            }
            
        }

    }

    if (numbers.size() != 2) {

        numbers.clear();
        numbers.push_back(0);
        numbers.push_back(0);

    }

}


int main() {

    // input modificato : aggiunta padding '.'
    std::ifstream file("inputs/day3_input.txt");
    // std::ifstream file("inputs/day3_input_example.txt");
    
    if (file.is_open()) {

        populate_matrix(file);
        // print_matrix();

        std::regex pattern(R"(\d+)");
        std::smatch match;

        for (int i = 0; i < numRighe; i++) {
            for (int j = 0; j < numColonne; j++) {

                if (matrix[i][j] == '*') {

                    gear_adj_numbers(i, j);

                    sum += (numbers[0]*numbers[1]);
                    numbers.clear();

                }

            }

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}