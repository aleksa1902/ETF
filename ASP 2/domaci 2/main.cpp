#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <queue> 

#include "Film.h"
#include "Cvor.h"

using namespace std;

// prijavljivanje greske ukoliko otvaranje datoteke nije uspelo
static void greska(){
	cout << "Greska u otvaranju datoteke!" << endl;
	system("pause");
	exit(1);
}

// podela jednog reda
vector<string> split(string str, string sep){
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL){
		//string s(current);
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

// prebacivanje stringa u broj
int mojStoi(string str){
	int sum = 0, i;
	for (i = 0; i < str.size(); i++){
		if (!isdigit(str[i])) return sum;
		sum = sum * 10 + str[i] - '0';
	}
	return sum;
}

//sortiranje
void sortiraj(vector<Film*> filmovi, int br) {
	int d, dd, m, mm, g, gg, ddd, mmm, ggg;

	for (int i = 0; i < br; i++) {
		int loc = i;
		d = filmovi[i]->getDay();
		m = filmovi[i]->getMonth();
		g = filmovi[i]->getYear();
		ddd = d;
		mmm = m;
		ggg = g;
		for (int j = i + 1; j < br; j++) {
			dd = filmovi[j]->getDay();
			mm = filmovi[j]->getMonth();
			gg = filmovi[j]->getYear();

			if (ggg > gg) {
				loc = j;
				ddd = dd;
				mmm = mm;
				ggg = gg;
			}
			else if (ggg == gg) {
				if (mmm > mm) {
					loc = j;
					ddd = dd;
					mmm = mm;
					ggg = gg;
				}
				else if (mmm == mm && ddd > dd) {
					loc = j;
					ddd = dd;
					mmm = mm;
					ggg = gg;
				}
			}

		}
		if (loc != i) {
			string la1, la2;
			string na1, na2;
			int rev1, rev2;
			int run1, run2;
			la1 = filmovi[i]->getLang(); la2 = filmovi[loc]->getLang();
			na1 = filmovi[i]->getName(); na2 = filmovi[loc]->getName();
			rev1 = filmovi[i]->getRevenue(); rev2 = filmovi[loc]->getRevenue();
			run1 = filmovi[i]->getRuntime(); run2 = filmovi[loc]->getRuntime();
			filmovi[i]->setDay(ddd);
			filmovi[i]->setMonth(mmm);
			filmovi[i]->setYear(ggg);
			filmovi[i]->setLang(la2);
			filmovi[i]->setName(na2);
			filmovi[i]->setRuntime(run2);
			filmovi[i]->setRevenue(rev2);

			filmovi[loc]->setDay(d);
			filmovi[loc]->setMonth(m);
			filmovi[loc]->setYear(g); 
			filmovi[loc]->setLang(la1);
			filmovi[loc]->setName(na1);
			filmovi[loc]->setRuntime(run1);
			filmovi[loc]->setRevenue(rev1);

		}

	}
}

Cvor* proveriOca(Cvor* root) {
	Cvor* tek = root;
	while (tek->otac) {
		tek = tek->otac;
	}
	return tek;
}

bool pronadji(Cvor* root, int mesec, int godina, int red) {
	Cvor* tek = root;
	
	while (tek->pok[0]) {
		int bro = 0;
		while (bro < tek->id) {
			//prvi slucaj
			if (godina < tek->year[bro]) {
				tek = tek->pok[bro]; break;
			}
			//drugi slucaj
			if (godina == tek->year[bro] && mesec < tek->month[bro]) {
				tek = tek->pok[bro];
				break;
			}
			//treci slucaj
			if (godina > tek->year[bro]) bro++;
			//cetvrti slucaj
			if (godina == tek->year[bro] && mesec > tek->month[bro]) bro++;
			//peti slucaj
			if (godina == tek->year[bro] && mesec == tek->month[bro] && tek->sled == nullptr) {
				tek = tek->pok[bro];
				while (tek->pok[0]) tek = tek->pok[tek->id];
				break;
			}
		}
	} //kraj while
	int i = 0;
	while (i < tek->id) {
		if (godina == tek->year[i] && mesec == tek->month[i]) {
			return true;
		}
		i++;
	}
	return false;
}

void ispis(Cvor* root) {
	Cvor* tek = nullptr, *pom = nullptr;
	int br;
	int i = 0;
	int j;
	queue<Cvor*> red;

	red.push(root);

	while (red.size()) {
		pom = red.front();
		red.pop();
		i = 0;
		while (i <= pom->id) {
			if(pom->pok[i] != nullptr)
			red.push(pom->pok[i]);
			i++;
		}
		if (tek != nullptr) {
			if (pom->visina == tek->visina) {
				cout << "\t";
				i = 0;
				cout << "|";
				while (i < pom->id) {
					cout << pom->month[i] << "," << pom->year[i] << "-";
					i++;
				}
				cout << "|";
			} else {
				cout << endl;
				i = 0;
				cout << "|";
				while (i < pom->id) {
					cout << pom->month[i] << "," << pom->year[i] << "-";
					i++;
				}
				cout << "|";
			}
			tek = pom;
		}
		else {
			tek = pom;
			i = 0;
			cout << "|";
			while (i < pom->id) {
				cout << pom->month[i] << "," << pom->year[i] << "-";
				i++;
			}
			cout << "|";
		}
	}
	cout << endl;
}

void pretragaOpsega(Cvor* root, int m1, int m2, int y1, int y2) {
	Cvor* tek = root;

	while (tek->pok[0]) {
		int bro = 0;
		while (bro <= tek->id) {
			//prvi slucaj
			if (y1 < tek->year[bro]) {
				tek = tek->pok[bro]; break;
			}
			//drugi slucaj
			else if (y1 == tek->year[bro] && m1 < tek->month[bro]) {
				tek = tek->pok[bro];
				break;
			}
			else if (y1 > tek->year[bro] && bro == tek->id) {
				tek = tek->pok[tek->id];
				break;
			}
			//treci slucaj
			else if (y1 > tek->year[bro]) bro++;
			//cetvrti slucaj
			else if (y1 == tek->year[bro] && m1 > tek->month[bro]) bro++;
			//peti slucaj
			else if (y1 == tek->year[bro] && m1 == tek->month[bro] && tek->sled == nullptr) {
				tek = tek->pok[bro];
				while (tek->pok[0]) tek = tek->pok[tek->id];
				break;
			}
		}
		//tek = tek->pok[tek->id];

	} //kraj while
	int i = 0;
	while (i < tek->id) {
		if (y1 < tek->year[i] || y1 <= tek->year[i] && m1 <= tek->month[i]) {
		break;
	}
		i++;
	}
	int j = 1;
	while (j) {
		if (y2 > tek->year[i] && i < tek->id) {
			tek->film[i]->ispisFilma();
			i++;
		}
		else if (y2 == tek->year[i] && m2 > tek->month[i] && i < tek->id) {
			tek->film[i]->ispisFilma();
		}
		else if (i == tek->id) {
			tek = tek->sled;
			i = 0;
		}
		else {
			j = 0;
		}
	}

}


void izdavanjeSatistike(Cvor* root, int y) {
	Cvor* tek = root;

	while (tek->pok[0]) {
		int bro = 0;
		while (bro < tek->id) {
			//prvi slucaj
			if (y < tek->year[bro]) {
				tek = tek->pok[bro]; break;
			}
			//drugi slucaj
			else if (y == tek->year[bro]) {
				tek = tek->pok[bro];
				break;
			}
			else if (y > tek->year[bro] && bro == tek->id - 1) {
				tek = tek->pok[tek->id];
				break;
			}
			//treci slucaj
			else if (y > tek->year[bro]) bro++;
		}
	} //kraj while
	int i = 0;
	while (i < tek->id) {
		if (y == tek->year[i]) {
			break;
		}
		i++;
	}
	int brojac = 0;
	while (y == tek->year[i]) {
		brojac++;
		i++;
		if (i == tek->id) {
			tek = tek->sled;
			i = 0;
		}
	}
	cout << "U " << y << " je izdato " << brojac << "filmova." << endl;
}

void unistavanjeStabla(Cvor* root) {
	Cvor* tek = nullptr, *pom = nullptr;
	int br;
	int i = 0;
	queue<Cvor*> red;

	red.push(root);

	while (red.size()) {
		pom = red.front();
		red.pop();
		i = 0;
		while (i <= pom->id) {
			if(pom->pok[i] != nullptr)
			red.push(pom->pok[i]);
			i++;
		}
		if (pom == root) {
			root = nullptr;
			i = 0;
			while (i <= pom->id) {
				pom->pok[i] = nullptr;
				i++;
			}
			delete pom;
		}
		else if (pom->pok[0] == nullptr) {
			i = 0;
			pom->otac = nullptr;
			pom->sled = nullptr;
			pom->preth = nullptr;

			while (i < pom->id) {
				pom->film[i] = nullptr;
				i++;
			}
			delete pom;
		}
		else {
			i = 0;
			pom->otac = nullptr;
			while (i <= pom->id) {
				pom->pok[i] = nullptr;
				i++;
			}
			//delete pom;
		}

	}

	cout << "Stablo je uspesno obrisano!" << endl;

}

int main(){
	vector<Film*> filmovi;
	ifstream dat;
	string str;
	Cvor* root = nullptr;
	int index;
	int opt, izbor;
	opt = 1;
	vector<string> parts;
	vector<string> partsdate;
	int n;
	int redst;
	int mesec, godina;

	while (opt) {
		cout << endl << "====================================================================================================" << endl <<
			"GLAVNI MENI" << endl << endl <<
			"1. Stvaranje baze podataka:" << endl <<
			"2. Ispis baze podataka:" << endl <<
			"3. Sortiranje baze podataka:" << endl <<
			"4. Logicko markiranje jednog filma:" << endl <<
			"5. Brisanje baze podataka:" << endl <<
			"6. Stvaranje B+ stabla:" << endl <<
			"7. Pronalazenje kljuca u stablu:" << endl <<
			"8. Brisanje kljuca u stablu:" << endl <<
			"9. Ispis B+ stabla:" << endl <<
			"10. Unistavanje stabla:" << endl <<
			"11. Satistika izdavanja:" << endl <<
			"12. Pronalazenje svih filmova iz zadatog perioda:" << endl <<
			"13. Upis kljuca u stablo:" << endl <<
			"0. Izlaz" << endl << endl;

		cout << "Izbor: " << endl;
		cin >> izbor;
		cout << endl;

		switch (izbor) {
		case 0:
			exit(1);
			break;
		case 1: {
			dat.open("tmdb_movies.csv");
			if (!dat.is_open()) greska();

			getline(dat, str);

			int br = 0;

			while (getline(dat, str)) {

				parts = split(str, ",");

				int rev = mojStoi(parts[3]);
				int run = mojStoi(parts[4]);

				partsdate = split(parts[2], "/");
				int da = mojStoi(partsdate[1]);
				int mo = mojStoi(partsdate[0]);
				int ye = mojStoi(partsdate[2]);

				Film *F = new Film(parts[0], parts[1], da, mo, ye, rev, run);
				filmovi.push_back(F);
				br++;
				//if (br % 10 == 0) {
				//	cout << br << endl;
				//	system("pause");
				//}
				//if (br % 100 == 0)cout << br << endl;
				
			}
			dat.close();
		}
			break;
		case 2: {
			if (filmovi.size()) {
				cout << "Ukupno Filmova: " << filmovi.size() << endl;

				n = filmovi.size();
				for (int i = 0; i < n; i++) {
					filmovi[i]->ispisFilma();
				}
				//system("PAUSE");
			}
			else {
				cout << "Nemamo bazu filmova." << endl;
			}
		}
			break;
		case 3: {
			if (filmovi.size()) {
				n = filmovi.size();
				sortiraj(filmovi, n);
				system("PAUSE");
			}
			else {
				cout << "Nemamo bazu filmova." << endl;
			}
		}
			break;
		case 4: {
			//brisanje jednog filma
			if (filmovi.size()) {
				cout << "Izaberi film za brisanje :" << endl;
				cin >> index;
				filmovi[index]->brisanje();
			}
			else {
				cout << "Nemamo bazu filmova." << endl;
			}
		}
			break;
		case 5: {
			//brisanje baze podataka o filmovima
			//for (int i = 0; i < n; i++) {
			//	filmovi[i]->ispisFilma();
			//}
			n = filmovi.size();
			for (int i = 0; i < n; i++) {
				delete filmovi[i];
			}

			filmovi.clear();
		}
			break;
		case 6: {
			if (filmovi.size()) {
				cout << "Red B + stabla:" << endl;
				cin >> redst;
				if (redst < 10 || redst > 2)
					root = new Cvor(redst);

				//ubacivanje u b+ stablo
				for (int i = 0; i < n; i++) {
					root = proveriOca(root);
					if (root->ubaci(filmovi[i], redst)) cout << "Uspesno umetanje kljuca!" << endl;
					else cout << "Neuspesno umetanje kljuca" << endl;
				}
				//system("pause");
			}
			else {
				cout << "Nemamo bazu filmova." << endl;
			}
		}
			break;
		case 7: {
			//pronalazenje kljuca u stablu
			if (root != nullptr) {
				cout << "Ukucaj kljuc za pretragu:" << endl;

				cin >> mesec >> godina;
				if (pronadji(root, mesec, godina, redst)) cout << "Uspesna pretraga!" << endl;
				else cout << "Neuspesna pretraga!" << endl;
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 8: {
			// brisanje kljuca iz stabla
			if (root != nullptr) {
				cout << "Unesi kljuc za brisanje" << endl;
				cin >> mesec >> godina;
				root->brisi(mesec, godina, redst);
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 9:{
			//ispis
			if (root != nullptr) {
				ispis(root);
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 10: {
			//unistavanje
			if (root != nullptr) {
				unistavanjeStabla(root);
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 11:{
			//pretrazivanje opsega

			if (root != nullptr) {
				int m1, m2, y1, y2;
				cout << "Unesi pocetni mesec i godinu za pretragu:" << endl;
				cin >> m1 >> y1;
				cout << "Unesi krajnji mesec i godinu za pretragu:" << endl;
				cin >> m2 >> y2;
				pretragaOpsega(root, m1, m2, y1, y2);
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 12: {
			// satistika broja filmova
			if (root != nullptr) {
				int y;
				cout << "Unesi godinu za izdavanje satistike:" << endl;
				cin >> y;
				izdavanjeSatistike(root, y);
			}
			else {
				cout << "Nemamo stablo" << endl;
			}
		}
			break;
		case 13: {
			if (root == nullptr) {
				cout << "Red B + stabla:" << endl;
				cin >> redst;
				if (redst > 10 || redst < 2) break;

				root = new Cvor(redst);
			}
			int odluka;
			cout << "Ubacujemo sve filmove iz baze(1) ili umecem kljuc(0)" << endl;
			cin >> odluka;
			if (odluka) {
				//ubacivanje u b+ stablo
				for (int i = 0; i < n; i++) {
					int mese, godi;
					mese = filmovi[i]->getMonth();
					godi = filmovi[i]->getYear();
					root = proveriOca(root);
					if (root->umetanje2(redst, mese, godi, filmovi[i])) cout << "Uspesno umetanje kljuca!" << endl;
					else cout << "Neuspesno umetanje kljuca" << endl;
				}
				system("pause");
			}
			else {
				int mes, god;
				cout << "Unesite mesec i godinu:" << endl;
				cin >> mes >> god;
				root = proveriOca(root);
				if (root->umetanje2(redst, mes, god, nullptr)) cout << "Uspesno umetanje kljuca!" << endl;
				else cout << "Neuspesno umetanje kljuca" << endl;
			}
		}
			break;
		default:
			cout << "Greska" << endl;
		}

	}

	

	system("pause");
	return 0;
}
