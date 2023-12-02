#include <iostream>
#include <fstream>

int main() {

    std::ifstream file("inputs/day1_input.txt");
    // std::ifstream file("inputs/day1_input_example.txt");

    int sum = 0; // somma totale

    if (file.is_open()) {

        std::string line; // linea analizzata

        while (std::getline(file, line)) {
            
            std::string local_number = ""; // doppia cifra sulla linea

            // trova prima cifra
            for (char& c : line) {

                if (std::isdigit(c)) {

                    local_number += c;
                    break;

                }

            }

            // trova ultima cifra
            for (auto it = line.rbegin(); it != line.rend(); ++it) {

                if (std::isdigit(*it)) {

                    local_number += (*it);
                    break;

                }   

            }

            int local_num_int = std::stoi(local_number); // doppia cifra sulla linea convertita a int
            sum += local_num_int; // aggiungi doppia cifra a somma totale

        }

    file.close();

    }

    std::cout << sum << std::endl;

    return 0;
    
}