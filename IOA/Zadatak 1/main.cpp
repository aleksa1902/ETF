#include <iostream>
#include <ctime>
using namespace std;

//ba170578_IOA_Zadatak_01

/* Napisati program koji izvrsava potpunu pretragu po
sve cetiri cene i pomocu njega odrediti cene. Izracunati
maksimalan broj poziva optimizacione funkcije.
*/
long long a() {
	const unsigned long suma = 711;
	const unsigned long product = 711000000;

	unsigned long long iteration = 0;

	for (long x1 = 1; x1 < 711; x1++) {
		for (long x2 = 1; x2 < 711; x2++) {
			for (long x3 = 1; x3 < 711; x3++) {
				for (long x4 = 1; x4 < 711; x4++) {

					long sum = x1 + x2 + x3 + x4;

					long pro = x1 * x2 * x3 * x4;

					iteration++;

					if (sum == suma && pro == product) {
						printf("Numbers : %lu %lu %lu %lu \n", x1, x2, x3, x4);
						printf("Iteration number : %llu \n", iteration);
					}

				}
			}
		}
	}

	printf("Final iteration number : %llu \n", iteration);

	return iteration;
}

/*
Napisati program koji izvrsava potpunu pretragu po
sve cetiri cene i pomocu njega odrediti cene. Izracunati
maksimalan broj poziva optimizacione funkcije. Izraziti jednu cenu preko ostalih i napisati program
koji izvrsava potpunu pretragu po (preostale) tri cene.
*/
long long b() {
	const unsigned long suma = 711;
	const unsigned long product = 711000000;

	unsigned long long iteration = 0;

	unsigned long x4 = 0;

	for (long x1 = 1; x1 < 711; x1++) {
		for (long x2 = 1; x2 < 711; x2++) {
			for (long x3 = 1; x3 < 711; x3++) {

				x4 = 711 - x3 - x2 - x1;

				long sum = x1 + x2 + x3 + x4;

				long pro = x1 * x2 * x3 * x4;

				iteration++;

				if (sum == suma && pro == product) {
					printf("Numbers : %lu %lu %lu %lu \n", x1, x2, x3, x4);
					printf("Iteration number : %llu \n", iteration);
				}


			}
		}
	}

	printf("Final iteration number : %llu \n", iteration);

	return iteration;
}

int main() {
	//program A
	printf("PROGRAM A \n\n");
	clock_t begin = clock();

	long long iterations_a = a();

	clock_t end = clock();
	double elapsed_secs_a = double(end - begin) / CLOCKS_PER_SEC;

	printf("Time between start and end : %lf s \n", elapsed_secs_a);
	printf("=======================================================\n");

	//program B
	printf("PROGRAM B \n\n");
	
	begin = clock();

	long long iterations_b = b();

	end = clock();
	double elapsed_secs_b = double(end - begin) / CLOCKS_PER_SEC;

	printf("Time between start and end : %lf s \n", elapsed_secs_b);
	printf("=======================================================\n\n");

	/*
	Izracunati maksimalan broj poziva opt. funkcije i
	uporediti brzinu programa u odnosu na program iz (a). 
	Koji od ova dva programa je brzi?
	*/

	printf("The number of iterations of program A is : %llu , and the number of iterations of program B is : %llu \n\n", iterations_a, iterations_b);

	printf("Program B is faster than program A in %lf s\n\n", elapsed_secs_a - elapsed_secs_b);

	return 1;
}