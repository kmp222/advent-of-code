#include <iostream>
#include <vector>

int wins(long long tempo, long long distanza) {

    long long counter = 0;
    long long button_press = 0;
    long long distanza_percorsa = 0;

    for (long long i = 0; i < tempo; i++) {

        button_press = i;
        distanza_percorsa = i*(tempo-i);
        
        if (distanza_percorsa > distanza) {
            counter++;
        }

    }

    return counter;

}

int main() {

    long long tempo = 44899691;
    long long distanza = 277113618901768;

    long long result = wins(tempo, distanza);

    std::cout << result << std::endl;

    return 0;

}