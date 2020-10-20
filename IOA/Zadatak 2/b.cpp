#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <cmath>
#include <ctime>

double rangeBetweenTwoHoles(double x1, double x2, double y1, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    int permutation[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    double hole[20][2] = { {62.0, 58.4}, {57.5, 56.0}, {51.7, 56.0}, {67.9, 19.6}, {57.7, 42.1},
                        {54.2, 29.1}, {46.0, 45.1}, {34.7, 45.1}, {45.7, 25.1}, {34.7, 26.4},
                        {28.4, 31.7}, {33.4, 60.5}, {22.9, 32.7}, {21.5, 45.8}, {15.3, 37.8},
                        {15.1, 49.6}, {9.1 , 52.8}, {9.1 , 40.3}, {2.7 , 56.8}, {2.7 , 33.1}
    };
   
    double minimum = 0;

    int min_per[12];
    int iteracija = 0;

    clock_t begin = clock(); // pocetak vremena
    
    do {
        iteracija++;
        double range = 0;

        for (int i = 0; i < 11; i++) {
            range += rangeBetweenTwoHoles(hole[permutation[i]][0], hole[permutation[i + 1]][0], hole[permutation[i]][1], hole[permutation[i + 1]][1]); // racuna sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
               
            if (i == 10) { // ovu funkciju sam mogao da stavim unutar for petlje pa ako se nekad tokom racuna prekoraci minimum da se vise ne racuna
                if (minimum == 0 || minimum > range) {
                    minimum = range;

                    for (int i = 0; i < 12; i++) {
                        min_per[i] = permutation[i] + 1; // sabira se sa jedan jer su u nizu permutation indeksi
                    }
                }
            }
            else {
                if (minimum != 0 && range > minimum) {
                    break;
                }
            }
        }

        

    } while (std::next_permutation(permutation, permutation + 12)); // prolazi kroz permutaciju 8! u nizu permutation[]
    
    clock_t end = clock(); // kraj vremena

    //std::cout << iteracija << "\n";

    double elapsed_secs_b = double(end - begin) / CLOCKS_PER_SEC;

    printf("Time between start and end : %lf s \n\n", elapsed_secs_b);

    std::cout << "The length of the shortest path : " << minimum << "\n";

    std::cout << "Minimum tour order(combination of permutation where minimum is found):\n";

    for (int i = 0; i < 12; i++) {
        std::cout << min_per[i] << " ";
    }

    std::cout << "\n\n";

    return 0;
}