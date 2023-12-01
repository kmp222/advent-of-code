#include <iostream>
#include <fstream>
#include <unordered_map>

int main() {

    std::ifstream file("day1_input.txt");
    // std::ifstream file("day1_2_input_example.txt");

    std::unordered_map<int, std::string> digit_to_word = {

        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"}

    };

    int sum = 0; // somma totale

    if (file.is_open()) {

        std::string line; // linea analizzata

        while (std::getline(file, line)) {
            
            std::string local_number = ""; // doppia cifra sulla linea
            std::string first_digit = ""; // prima cifra
            std::string last_digit = ""; // ultima cifra

            int first_digit_pos = 0;
            int last_digit_pos = line.size() - 1;

            // trova prima cifra
            for (char& c : line) {

                if (std::isdigit(c)) {

                    first_digit = c;
                    break;

                }

                  first_digit_pos++;

            }

            // trova prima cifra come parola
            for (int i = 1; i < 10; i++) {

                int pos_occorrenza = line.find(digit_to_word.at(i));

                // se esiste un'occorrenza della cifra i come parola && 
                // occorre prima della cifra migliore, rimpiazzala

                if ( (pos_occorrenza != std::string::npos) &&
                        (pos_occorrenza < first_digit_pos) ) {

                            first_digit = std::to_string(i);
                            first_digit_pos = pos_occorrenza;

                        }

            }


            // trova ultima cifra
            for (auto it = line.rbegin(); it != line.rend(); ++it) {

                if (std::isdigit(*it)) {

                    last_digit = (*it);
                    break;

                }

                last_digit_pos--;

            }

            // trova ultima cifra come parola
            for (int i = 1; i < 10; i++) {

                int pos_occorrenza = line.rfind(digit_to_word.at(i));

                // se esiste un'occorrenza della cifra i come parola && 
                // occorre dopo la cifra migliore, rimpiazzala

                if ( (pos_occorrenza != std::string::npos) &&
                        (pos_occorrenza > last_digit_pos) ) {

                            last_digit = std::to_string(i);
                            last_digit_pos = pos_occorrenza;

                        }

            }

            local_number = first_digit + last_digit;

            int local_num_int = std::stoi(local_number); // doppia cifra sulla linea convertita a int
            sum += local_num_int; // aggiungi doppia cifra a somma totale

            std::cout << local_num_int << std::endl;

        }

    file.close();

    }

    std::cout << sum << std::endl;

    return 0;
    
}