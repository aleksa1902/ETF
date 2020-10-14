/*
ba170578_Bonus_01
Napisati program koji resava ovaj problem u
opstem slucaju. Poznat je broj ljudi N, broj ljudi
koji moze da istovremeno predje most M i vreme
prelaska za svakog od njih.
*/

#include <iostream>
#include <list>
using namespace std;

int nChoosek(unsigned n, unsigned k){
	if (k > n) return 0;
	if (k * 2 > n) /*return*/ k = n - k; 
	if (k == 0) return 1;

	int result = n;
	for (int i = 2; i <= k; ++i) {
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}

int main() {
	int n;
	cout << "Enter the number of people crossing the bridge : ";
	cin >> n;

	list<int> lista = {};

	int min = 0, min_val = 0;

	for (int i = 1; i <= n; i++) {
		int m;
		cout << "Enter the time of crossing the bridge person number " << i << " : ";
		cin >> m;

		if (i == 1) {
			min_val = m;
			min = i;
		}

		if (min_val > m) {
			min_val = m;
			min = i;
		}

		lista.push_back(m);
	}

	cout << "=================================================================\n";

	cout << "We have " << n << " people crossing the bridge\n\n";
	int i = 1;
	for (list<int>::iterator it = lista.begin(); it != lista.end(); ++it) {
		cout << "Person number " << i << " crosses the bridge for " << *it << " min ";
		if (i == min) cout << "= MINIMUM";
		cout << "\n\n";
		i++;
	}
	
	cout << "We have " << n - 1 << " crossings and " << n - 2 << " returns\n\n";

	int pro = 1;
	for (int i = n; i > 0; i--) {
		if (i >= 2) {
			pro *= nChoosek(i, 2);
		}	
	}

	cout << "We have a " << pro << " possible combinations\n\n";

	int suma = 0;

	i = 1;
	for (list<int>::iterator it = lista.begin(); it != lista.end(); ++it) {
		if (i != min) {
			cout << "The bridge is crossed by persons number " << i << " and " << min << "\n";
			
			suma += *it; //prelazak
			
			if (i != n) {
				cout << "Person number " << min << " goes back\n";
				suma += min_val; //povratak
			}
		}
		
		i++;
	}

	cout << "\n\n";
	
	cout << "The total value of crossing the bridge is : " << suma << " minutes.\n\n";
	
	return 1;
}