#include <iostream>
#include <ctime>
#include <fstream>

#define N 10

int price[N][N] = { {0,374,200,223,108,178,252,285,240,356},
					{374,0,255,166,433,199,135,95,136,17},
					{200,255,0,128,277,821,180,160,131,247},
					{223,166,128,0,430,47,52,84,40,155},
					{108,433,277,430,0,453,478,344,389,423},
					{178,199,821,47,453,0,91,110,64,181},
					{252,135,180,52,478,91,0,114,83,117},
					{285,95,160,84,344,110,114,0,47,78},
					{240,136,131,40,389,64,83,47,0,118},
					{356,17,247,155,423,181,117,78,118,0}
};

char city[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

void SequenceToSpanningTree(int* P, int len, int* T){ //kod sa prezentacije
	int i, j, q = 0;
	int n = len + 2;
	int* V = new int[n];

	for (i = 0; i < n; i++)
		V[i] = 0;

	for (i = 0; i < len; i++)
		V[P[i] - 1] += 1;

	for (i = 0; i < len; i++) {
		for (j = 0; j < n; j++) {
			if (V[j] == 0) {
				V[j] = -1;
				T[q++] = j + 1;
				T[q++] = P[i];
				V[P[i] - 1]--;
				break;
			}
		}
	}

	j = 0;

	for (i = 0; i < n; i++) {
		if (V[i] == 0 && j == 0) {
			T[q++] = i + 1;
			j++;
		}
		else if (V[i] == 0 && j == 1) {
			T[q++] = i + 1;
			break;
		}
	}

	delete[] V;
}

int newCost(int* T, int sizeT) { // racunanje nove cene puta
	int cost = 0;

	int numCity[10] = {0}; // broj ponavljanja gradova

	for (int i = 0; i < sizeT; i++) {
		if ((i + 1) % 2 == 0) {
			cost += price[T[i] - 1][T[i - 1] - 1];
		}

		numCity[T[i] - 1]++;
	}

	for (int i = 0; i < N; i++) {
		if (numCity[i] >= 4) cost += (numCity[i] - 3) * 100;
	}

	return cost;
}

int main() {
	int permutation;
	int numBranch = N - 2; //broj grana

	const int sizeOutput = 2 * (numBranch + 1);

	int minCost = 0;

	int* P = new int[numBranch]; // niz za grane

	for (int i = 0; i < numBranch; i++) {
		P[i] = 1; // inicijalizacija niza P koji se koristi za permutaciju
	}

	int* T = new int[sizeOutput]; // niz za povezane cvorove
	int* bestFit = new int[sizeOutput];

	int iteration = 0;

	clock_t begin = clock();

	do {
		iteration++;
		//std::cout << iteration << "\n";

		SequenceToSpanningTree(P, numBranch, T);
		int costNewSequence = newCost(T, sizeOutput);

		if (minCost == 0 || minCost > costNewSequence) {
			minCost = costNewSequence;

			for (int i = 0; i < sizeOutput; i++) {
				bestFit[i] = T[i];
			}
		}

		permutation = numBranch - 1;

		while (permutation >= 0) {
			P[permutation]++;

			if (P[permutation] == N + 1) {
				P[permutation] = 1;
				permutation--;
			}
			else {
				break;
			}
		}

	} while (permutation >= 0);

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Numbers iterations : " << iteration << "\n";

	std::cout << "Time between start and end : " << elapsed_secs << " s \n";

	std::cout << "Minimal cost is : " << minCost << "\n";

	std::cout << "Minimal graph : ";

	for (int i = 0; i < sizeOutput; i++) {
		std::cout << bestFit[i] << " ";

		if ((i + 1) % 2 == 0 && i < 2 * numBranch)
			std::cout << " - ";
	}
	std::cout << "\n";

	for (int i = 0; i < sizeOutput; i++) {
		std::cout << city[bestFit[i] - 1] << " ";

		if ((i + 1) % 2 == 0 && i < 2*numBranch)
			std::cout << " - ";
	}

	std::cout << "\n\n";

	std::ofstream myfile;
	myfile.open("finalOutput.txt");
	myfile << "Numbers iterations : " << iteration << "\n";
	myfile << "Time between start and end : " << elapsed_secs << " s \n";
	myfile << "Minimal cost is : " << minCost << "\n";
	myfile << "Minimal graph : ";

	//for (int i = 0; i < sizeOutput; i++) {
		//myfile << << bestFit[i] << " ";

	//	if ((i + 1) % 2 == 0 && i < 2 * numBranch)
	//		myfile << " - ";
	//}

	for (int i = 0; i < sizeOutput; i++) {
		myfile << city[bestFit[i] - 1] << " ";

		if ((i + 1) % 2 == 0 && i < 2 * numBranch)
			myfile << " - ";
	}

	myfile.close();

	delete[] T;
	delete[] P;
	delete[] bestFit;


	return 0;
}