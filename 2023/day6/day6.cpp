#include <iostream>
#include <vector>

std::vector<int> tempi = {44, 89, 96, 91};
std::vector<int> distanze = {277, 1136, 1890, 1768};

int wins(int tempo, int distanza) {

    int counter = 0;
    int button_press = 0;
    int distanza_percorsa = 0;

    for (int i = 0; i < tempo; i++) {

        button_press = i;
        distanza_percorsa = i*(tempo-i);
        
        if (distanza_percorsa > distanza) {
            counter++;
        }

    }

    return counter;

}

int main() {
    
    int tempo = 0;
    int distanza = 0;
    int result = 1;

    for (int i = 0; i < tempi.size(); i++) {

        tempo = tempi[i];
        distanza = distanze[i];

        result *= wins(tempo, distanza);

    }

    std::cout << result << std::endl;

    return 0;

}