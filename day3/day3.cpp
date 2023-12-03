#include <iostream>
#include <fstream>
#include <vector>

int righe = 10, colonne = 10;
std::vector<std::vector<char>> matrix(righe, std::vector<char>(colonne));

// popola matrice MxN a partire da un file di testo
void populate_matrix(std::ifstream& file) {

    char c;

    // conta righe e colonne file
    bool fine_colonne = false;

    while (file.get(c)) {

        if (c == '\n') {

            ++righe;
            fine_colonne = true;

        } else if (!fine_colonne) {

            ++colonne;

        }

    }

    std::cout << righe << std::endl;
    std::cout << colonne << std::endl;

    // resetta la posizione del file
    file.clear();
    file.seekg(0, std::ios::beg);

    // Ridimensiona la matrice
    matrix.resize(righe, std::vector<char>(colonne));

    // popola la matrice
    for (int i = 0; i < righe; ++i) {

        for (int j = 0; j < colonne; ++j) {

            char c;

            while (c == '\n') {
                file.get(c);
            }
            
            std::cout << i << " " << j << std::endl;

            matrix[i][j] = c;

        }



    }

}

// for debugging
void print_matrix() {

    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

int main() {

    std::ifstream file("inputs/day3_input_example.txt");
    
    if (file.is_open()) {

        populate_matrix(file);
        print_matrix();
        file.close();

    }

    return 0;

}