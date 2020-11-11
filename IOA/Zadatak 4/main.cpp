#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;



int main() {

	int n = 1;

	double low = 4;
	double high = 6;
	long double mid = 0;

	const double p = pow(10, - 12);

	//cout << precision << "\n";

	while (high - low > p) { 
		mid = (high + low) / 2;
		if (std::sph_bessel(n, mid) > 0)
			low = mid;
		else
			high = mid;
	}

	cout << "n = " << n << "\n";
	cout << "Prva nula : " << setprecision(18) << mid << "\n";

	low = 7;
	high = 9;

	while (high - low > p) {
		mid = (high + low) / 2;
		if (sph_bessel(n, mid) < 0)
			low = mid;
		else
			high = mid;

	}

	cout << "n = " << n << "\n";
	cout << "Druga nula : " << setprecision(18) << mid << "\n";


	n = 2;
	low = 5;
	high = 7;

	while (high - low > p) {
		mid = (high + low) / 2;
		if (sph_bessel(n, mid) > 0)
			low = mid;
		else
			high = mid;

	}
	
	cout << "n = " << n << "\n";
	cout << "Prva nula : " << setprecision(18) << mid << "\n";

	low = 8;
	high = 10;

	while (high - low > p) {
		mid = (high + low) / 2;
		if (sph_bessel(n, mid) < 0)
			low = mid;
		else
			high = mid;

	}

	
	cout << "Druga nula : " << setprecision(18) << mid << "\n";


	return 0;
}