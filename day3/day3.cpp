#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> matrix;
int numRighe = 0;
int numColonne = 0;
int sum = 0;

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

bool is_part_number(int start, int end, int riga_indexed) {
 
        if (riga_indexed != 0 && riga_indexed < numRighe-1) { // numeri non sulla prima e ultima linea

            // check laterale
            if ( !( matrix[riga_indexed][start-1] == '.' &&
                matrix[riga_indexed][end+1] == '.' ) ) {  
                return true;
            }

            // check linea sopra
            for (int i = start-1; i < end+2; i++) {

                if ( !(std::isdigit(matrix[riga_indexed-1][i]) ||
                        matrix[riga_indexed-1][i] == '.' ) ) {
                        return true;

                }

            }
            
            // check linea sotto
            for (int i = start-1; i < end+2; i++) {

                if ( !(std::isdigit(matrix[riga_indexed+1][i]) ||
                        matrix[riga_indexed+1][i] == '.' ) ) {
                        return true;

                }

            }

        } else if (riga_indexed == 0) { // numeri sulla prima linea

            // check laterale
            if ( !( matrix[riga_indexed][start-1] == '.' &&
                matrix[riga_indexed][end+1] == '.' ) ) {  
                return true;
            }

            // check linea sotto
            for (int i = start-1; i < end+2; i++) {

                if ( !(std::isdigit(matrix[riga_indexed+1][i]) ||
                        matrix[riga_indexed+1][i] == '.' ) ) {
                        return true;

                }

            }

        } else if (riga_indexed == numRighe-1) { // numeri sull'ultima linea

            // check laterale
            if ( !( matrix[riga_indexed][start-1] == '.' &&
                matrix[riga_indexed][end+1] == '.' ) ) {  
                return true;
            }

            // check linea sopra
            for (int i = start-1; i < end+2; i++) {

                if ( !(std::isdigit(matrix[riga_indexed-1][i]) ||
                        matrix[riga_indexed-1][i] == '.' ) ) {
                        return true;

                }

            }

        }

    return false;

}


int main() {

    // input modificato : aggiunta '.' a inizio e fine di ogni riga
    std::ifstream file("inputs/day3_input.txt");
    // std::ifstream file("inputs/day3_input_example.txt");
    
    if (file.is_open()) {

        populate_matrix(file);
        // print_matrix();

        std::regex pattern(R"(\d+)");
        std::smatch match;

        for (int i = 0; i < numRighe; i++) {

            std::string::const_iterator searchStart(matrix[i].cbegin());

            while (std::regex_search(searchStart, matrix[i].cend(), match, pattern)) {

                int start = std::distance(matrix[i].cbegin(), searchStart) + match.position();
                int end = start + match.length() - 1;

                if (is_part_number(start, end, i)) {

                    int numero = std::stoi(match[0]);
                    std::cout << numero << std::endl;
                    sum += numero;

                }

                searchStart = match.suffix().first;

            }

        }

    }

    file.close();

    std::cout << sum << std::endl;

    return 0;

}