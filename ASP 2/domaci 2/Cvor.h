#ifndef __CVOR_H__
#define __CVOR_H__
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "Film.h"

class Cvor
{
public:
	int id;
	int month[9];
	int year[9];
	Cvor* pok[10];
	Cvor* sled;
	Cvor* preth;
	Film* film[9];
	Cvor* otac;
	int visina;

	Cvor(int br) {
		id = 0;
		visina = 0;
		for (int i = 0; i < br - 1; i++) {
			month[i] = 0; year[i] = 0; pok[i] = nullptr;
			film[i] = nullptr;
		}
		pok[br - 1] = nullptr;
		sled = nullptr;
		otac = nullptr;
		preth = nullptr;
	}

	~Cvor();

	int podeli(Cvor* tek, int br) {
		int broj = 0;
		Cvor* pom;
		if (tek == this) {
			return broj;
		}
		else {
			tek = tek->otac;
			if (tek->id < br - 1) return broj;

			while (tek != this) {
				pom = tek->otac;
				broj++;
				if (pom->id == br) tek = tek->otac;
				else {
					//prvi deo prebacivanje iz tekuceg sredisnji clan i prebacivanje ocu
					pom->month[pom->id] = tek->month[br / 2];
					pom->year[pom->id] = tek->year[br / 2];
					pom->id++;
					//drugi deo stvaranje novog cvora i prebacivanje iz tekuceg
					Cvor* cvor = new Cvor(br);
					cvor->otac = pom;
					cvor->visina = tek->visina;
					int i;
					for (i = br / 2 + 1; i < br; i++) {
						if (i < br - 1) {
							cvor->month[cvor->id] = tek->month[i];
							cvor->year[cvor->id] = tek->year[i];
							cvor->pok[cvor->id] = tek->pok[i];
							tek->pok[i]->otac = cvor;
							cvor->id++;
						}
						else {
							cvor->pok[cvor->id] = tek->pok[i];
							tek->pok[i]->otac = cvor;
						}
					}
					// treci deo - brisanje u tekucem cvoru
					for (i = br / 2; i < br; i++) {
						if (i < br - 1) {
							tek->month[i] = 0;
							tek->year[i] = 0;
							tek->id--;
						}
						if (i > br / 2 + 1) {
							tek->pok[i] = nullptr;
						}
					}
					// cetvrti deo - otac pokazuje na novog cvora
					pom->pok[pom->id] = cvor;

				}
				return broj;
			}
			//ako tekuci dodje do punog root

			Cvor* ot = new Cvor(br);
			ot->month[ot->id] = tek->month[br / 2];
			ot->year[ot->id] = tek->year[br / 2];
			ot->pok[ot->id] = tek;
			ot->id++;
			ot->visina = tek->visina + 1;
			Cvor* cvor = new Cvor(br);
			cvor->otac = ot;
			tek->otac = ot;
			cvor->visina = tek->visina;
			int i;
			for (i = br / 2 + 1; i < br; i++) {
				if (i < br - 1) {
					cvor->month[cvor->id] = tek->month[i];
					cvor->year[cvor->id] = tek->year[i];
					cvor->pok[cvor->id] = tek->pok[i];
					tek->pok[i]->otac = cvor;
					cvor->id++;
				}
				else {
					cvor->pok[cvor->id] = tek->pok[i];
					tek->pok[i]->otac = cvor;
				}
			}
			// treci deo - brisanje u tekucem cvoru
			for (i = br / 2; i < br; i++) {
				if (i < br - 1) {
					tek->month[i] = 0;
					tek->year[i] = 0;
					tek->id--;
				}
				if (i > br / 2) {
					tek->pok[i] = nullptr;
				}
			}
			// cetvrti deo - otac pokazuje na novog cvora
			ot->pok[ot->id] = cvor;

		}
	}

	bool ubaci(Film* film, int br) {
		Cvor *tek = this, *pom;
		int m = film->getMonth(); int y = film->getYear();
		if (id == 0) {
			this->month[this->id] = m;
			this->year[this->id] = y;
			this->film[this->id] = film;
			this->id++;
			return true;
		}
		while (tek->pok[tek->id]) {
			tek = tek->pok[tek->id]; // idemo na najdesniji cvor
		}
		if (tek->year[tek->id - 1] == y && tek->month[tek->id - 1] == m) return false; // jednaki mesec i godina

		if (tek->id < br - 1) {
			tek->month[tek->id] = m;
			tek->year[tek->id] = y;
			tek->film[tek->id] = film;
			tek->id++;
			return true;
		}
		if (tek->id == br - 1) {
			if (tek != this) {
				int num = 1;
				//sredjujem prvo sve sto ima iznad
				while (num) {
					num = this->podeli(tek, br);
				}
				//prvi deo prebacivanje sredinu na oca
				pom = tek->otac;

				pom->month[pom->id] = tek->month[br / 2];
				pom->year[pom->id] = tek->year[br / 2];
				pom->id++;
				// drugi deo stvaranje novog cvora
				Cvor* cvor = new Cvor(br);
				cvor->otac = pom;
				int i;
				for (i = br / 2 + 1; i < br; i++) {
					if (i < br - 1) {
						cvor->month[cvor->id] = tek->month[i];
						cvor->year[cvor->id] = tek->year[i];
						cvor->film[cvor->id] = tek->film[i];
						cvor->id++;
					}
				}
				cvor->month[cvor->id] = m;
				cvor->year[cvor->id] = y;
				cvor->film[cvor->id] = film;
				cvor->id++;
				cvor->visina = tek->visina;
				// cetvrti deo- brisanje u tekucem cvoru
				for (i = br / 2 + 1; i < br; i++) {
					if (i < br - 1) {
						tek->month[i] = 0;
						tek->year[i] = 0;
						tek->film[i] = nullptr;
						tek->id--;
					}
				}
				// peti deo - otac pokazuje na novog cvora
				pom->pok[pom->id] = cvor;
				// sesti deo prethodni cvor lista pokazuje na novi cvor lista
				tek->sled = cvor;
				cvor->preth = tek;
			}
			else {
				Cvor* ot = new Cvor(br);
				ot->month[ot->id] = tek->month[br / 2];
				ot->year[ot->id] = tek->year[br / 2];
				ot->pok[ot->id] = tek;
				ot->id++;
				Cvor* cvor = new Cvor(br);
				cvor->otac = ot;
				tek->otac = ot;
				ot->visina = tek->visina + 1;
				int i;
				for (i = br / 2 + 1; i < br; i++) {
					if (i < br - 1) {
						cvor->month[cvor->id] = tek->month[i];
						cvor->year[cvor->id] = tek->year[i];
						cvor->film[cvor->id] = tek->film[i];
						cvor->id++;
					}
				}
				cvor->month[cvor->id] = m;
				cvor->year[cvor->id] = y;
				cvor->film[cvor->id] = film;
				cvor->id++;
				cvor->visina = tek->visina;
				// cetvrti deo- brisanje u tekucem cvoru
				for (i = br / 2 + 1; i < br; i++) {
					if (i < br - 1) {
						tek->month[i] = 0;
						tek->year[i] = 0;
						tek->film[i] = nullptr;
						tek->id--;
					}
				}
				// peti deo - otac pokazuje na novog cvora
				ot->pok[ot->id] = cvor;
				tek->sled = cvor;
				cvor->preth = tek;

			}
		}
	}

	// brisanje kljuca B+ stabla
	bool brisi(int m, int g, int br) {
		int i; 
		Cvor *tek = this, *pom = nullptr;
		int bro = 0;
		int tacnost = 0;

		while (tek->pok[0]) {
			int bro = 0;
			while (bro <= tek->id) {
				//prvi slucaj
				if (g < tek->year[bro]) {
					tek = tek->pok[bro]; break;
				}
				//drugi slucaj
				else if (g == tek->year[bro] && m < tek->month[bro]) {
					tek = tek->pok[bro];
					break;
				}
				else if (g > tek->year[bro] && bro == tek->id) {
					tek = tek->pok[tek->id];
					break;
				}
				//treci slucaj
				else if (g > tek->year[bro]) bro++;
				//cetvrti slucaj
				else if (g == tek->year[bro] && m > tek->month[bro]) bro++;
				//peti slucaj
				else if (g == tek->year[bro] && m == tek->month[bro] && tek->sled == nullptr) {
					tek = tek->pok[bro];
					while (tek->pok[0]) tek = tek->pok[tek->id];
					break;
				}
			}
			
		} //kraj while

		i = 0;
		while (i < tek->id) {
			if (g == tek->year[i] && m == tek->month[i]) break;
			i++;
		}
		if (i >= tek->id) return false;


		//1.3
		if (i == tek->id - 1) {
			tek->id--;
			int info1 = tek->month[tek->id - 1];
			int info2 = tek->year[tek->id - 1];
			int j = 1;
			pom = tek->otac;
			while (j) {
				int k = 0;
				while (k < pom->id) {
					if (tek->year[tek->id] == pom->year[k] && tek->month[tek->id] == pom->month[k]) {
						pom->month[k] = info1; pom->year[k] = info2;
						j = 0;
						break;
					}
					k++;
				}
			pom = pom->otac;
			}
		}
		//1.1 i 1.2
		else {
			while (i < tek->id - 1) {
				tek->month[i] = tek->month[i + 1];
				tek->year[i] = tek->year[i + 1];
				tek->film[i] = tek->film[i + 1];
				i++;
			}
			tek->id--;
		}
		
		if (tek->id > br / 2 - 1) return true;
		else {
			pom = tek->sled;
			// da li desni brat i tek imamo istog oca
			if (pom != nullptr && tek->otac == pom->otac) {
				if (pom->id - 1 > br / 2 - 1) {
					tek->month[tek->id] = pom->month[0];
					tek->year[tek->id] = pom->year[0];
					tek->film[tek->id] = pom->film[0];
					tek->id++;
					//pomeramo podatke kod desnog brata kad smo vec prebacili info
					i = 0;
					while (i < pom->id - 1) {
						pom->month[i] = pom->month[i + 1];
						pom->year[i] = pom->year[i + 1];
						pom->film[i] = pom->film[i + 1];
						i++;
					}
					pom->id--;

					// menjamo od tekuceg najvecu info kod oca
					pom = tek->otac;
					int info1 = tek->month[tek->id - 1];
					int info2 = tek->year[tek->id - 1];
					int j = 1;
					while (j) {
						int k = 0;
						while (k < pom->id) {
							if (tek = pom->pok[k]) {
								pom->month[k] = info1; pom->year[k] = info2;
								j = 0;
								break;
							}
							k++;
						}
						pom = pom->otac;
					}
					return true;
				}
			}
			//odo kod levog brata sigurno imamo istog oca
			else {
				pom = tek->preth;
				if (pom->id - 1 > br / 2 - 1) {
					// oslobadjamo prvo mesto tekuceg da bi uzeo od brata
					i = tek->id;
					while (i > 0) {
						tek->month[i] = tek->month[i - 1];
						tek->year[i] = tek->year[i - 1];
						tek->film[i] = tek->film[i - 1];
						i--;
					}
					tek->id++;
					// brat daje info
					if (pom->id - 1 > br / 2 - 1) {
						tek->month[0] = pom->month[pom->id - 1];
						tek->year[0] = pom->year[pom->id - 1];
						tek->film[0] = pom->film[pom->id - 1];
						pom->id--;

						// menjamo od tekuceg najvecu info kod oca
						tek = pom->otac;
						int info1 = pom->month[pom->id - 1];
						int info2 = pom->year[pom->id - 1];
						int j = 1;
						while (j) {
							int k = 0;
							while (k < tek->id) {
								if (pom->year[pom->id] == tek->year[k] && pom->month[pom->id] == tek->month[k]) {
									tek->month[k] = info1; tek->year[k] = info2;
									j = 0;
									break;
								}
								k++;
							}
							tek = tek->otac;
						}
						return true;
					}
				}
			}
			//levi i desni brat nemaju vise od uslova pa onda radimo sledecu varijantu
			//opet sam u desnom bratu
			pom = tek->sled;
			if (pom != nullptr && tek->otac == pom->otac) {
				if(pom->id - 1 == br/2 - 1){
					i = 0;
					while (i < pom->id) {
						tek->month[tek->id] = pom->month[i];
						tek->year[tek->id] = pom->year[i];
						tek->film[tek->id] = pom->film[i];
						tek->id++; i++;
					}
					tek->sled = pom->sled;
					pom->sled->preth = tek;
					//prebacujem ga na oca da ga sredim
					Cvor* pomoc = pom->otac;
					if (pomoc->pok[pomoc->id] == pom) {
						pomoc->pok[pomoc->id] = nullptr;
						pomoc->id--;
					}
					else {
						//if (pomoc->id > 1) {
						i = 0;
						while (i < pomoc->id) {
							if (pomoc->pok[i] == pom) break;
							i++;
						}
						//azuriranje
						while (i < pomoc->id) {
							pomoc->month[i - 1] = pomoc->month[i];
							pomoc->year[i - 1] = pomoc->year[i];
							pomoc->pok[i] = pomoc->pok[i + 1];
							i++;
						}
						pomoc->id--;
						pom->otac = nullptr; pom->sled = nullptr; pom->preth = nullptr;
						delete pom;
						return true;
					}
				}
			}
			else {
				pom = tek->preth;
				if (pom->id - 1 == br / 2 - 1) {
					i = 0;
					while (i < tek->id) {
						pom->month[pom->id] = tek->month[i];
						pom->year[pom->id] = tek->year[i];
						pom->film[pom->id] = tek->film[i];
						pom->id++; i++;
					}
					pom->sled = tek->sled;
					tek->sled->preth = pom;
					//prebacujem ga na oca da ga sredim
					Cvor* pomoc = tek->otac;
					if (pomoc->pok[pomoc->id] == tek) {
						pomoc->pok[pomoc->id] = nullptr;
						pomoc->id--;
					}
					else {
						//if (pomoc->id > 1) {
						i = 0;
						while (i < pomoc->id) {
							if (pomoc->pok[i] == tek) break;
							i++;
						}
						//azuriranje
						while (i < pomoc->id) {
							pomoc->month[i - 1] = pomoc->month[i];
							pomoc->year[i - 1] = pomoc->year[i];
							pomoc->pok[i] = pomoc->pok[i + 1];
							i++;
						}
						pomoc->id--;
						tek->otac = nullptr; tek->sled = nullptr; tek->preth = nullptr;
						delete tek;
						return true;
					}
				}

			}

		}

	}


	bool umetanje2(int br, int m, int g, Film* film) {
		int i;
		Cvor *tek = this, *pom = nullptr;
		int bro = 0;
		int tacnost = 0;

		while (tek->pok[0]) {
			int bro = 0;
			while (bro <= tek->id) {
				//prvi slucaj
				if (g < tek->year[bro]) {
					tek = tek->pok[bro]; break;
				}
				//drugi slucaj
				else if (g == tek->year[bro] && m < tek->month[bro]) {
					tek = tek->pok[bro];
					break;
				}
				else if (g > tek->year[bro] && bro == tek->id) {
					tek = tek->pok[tek->id];
					break;
				}
				//treci slucaj
				else if (g > tek->year[bro]) bro++;
				//cetvrti slucaj
				else if (g == tek->year[bro] && m > tek->month[bro]) bro++;
				//peti slucaj
				else if (g == tek->year[bro] && m == tek->month[bro] && tek->sled == nullptr) {
					return false;
				}
			}
			//tek = tek->pok[tek->id];

		} //kraj while
		i = 0;
		//trazim gde mogu da umetnem
		while (i < tek->id) {
			if (g < tek->year[i]) break;
			else if (g == tek->year[i] && m == tek->month[i]) return false;
			else if (g == tek->year[i] && m < tek->month[i]) break;
			i++;
		}
		//ako je to poslednje mesto umetni odmah
		if (i == tek->id) {
			tek->month[i] = m; tek->year[i] = g; tek->film[i] = film;
			tek->id++;
		}
		//ako nije uradi pomeraj od tog mesta pa nadalje
		else if (i < tek->id) {
			int j = tek->id;
			while (j > i) {
				tek->month[j] = tek->month[j - 1]; tek->year[j] = tek->year[j - 1]; tek->film[j] = tek->film[j - 1];
				j--;
			}
			//ummetni sad
			tek->month[i] = m; tek->year[i] = g; tek->film[i] = film;
			tek->id++;
		}
		//da li je validno da je manji od reda
		if (tek->id < br) {
			return true;
		}
		//ako nije delim ga
		else {
			Cvor* novi = new Cvor(br);
			if (br % 2) {
				i = br / 2 + 1;
			}
			else {
				i = br / 2;
			}
			int j = 0;
			while (i < tek->id) {
				novi->month[j] = tek->month[i]; novi->year[j] = tek->year[i]; novi->film[j] = tek->film[i];
				i++; j++; novi->id++;
			}
			tek->sled = novi; 
			novi->preth = tek; 
			novi->otac = tek->otac; 
			tek->id = br/2 + 1;
			//ako nema oca napravi ga
			if (tek->otac == nullptr) {
				Cvor* otac = new Cvor(br);
				if (br % 2) {
					i = br / 2;
				}
				else {
					i = br / 2 - 1;
				}
				otac->month[otac->id] = tek->month[i]; 
				otac->year[otac->id] = tek->year[i]; 
				otac->pok[otac->id] = tek;
				otac->id++; 
				otac->pok[otac->id] = novi; 
				tek->otac = otac; 
				novi->otac = otac;
				return true;
			}
			// ako ima oca predji i prebaci mu pokazivac i sredinu
			else {
				Cvor* otac = tek->otac;
				i = 0;
				while (i < otac->id) {
					if (tek->year[br / 2 - 1] < otac->year[i]) break;
					else if (tek->year[br / 2 - 1] == otac->year[i] && tek->month[br / 2 - 1] < otac->month[i]) break;
					i++;
				}

				if (i == otac->id) {
					otac->month[i] = tek->month[br / 2 - 1]; otac->year[i] = tek->year[br / 2 - 1]; otac->pok[otac->id + 1]= novi;
					otac->id++;
				}
				else if (i < otac->id) {
					int j = otac->id;
					while (j > i) {
						otac->month[j] = otac->month[j - 1]; otac->year[j] = otac->year[j - 1]; otac->pok[j + 1] = tek->pok[j];
						j--;
					}
					//ovde
					otac->month[i] = tek->month[tek->id - 1]; otac->year[i] = tek->year[tek->id - 1]; otac->pok[i + 1] = novi;
					otac->id++;
				}

				int ok = 1;
				while (ok) {
					//provera
					if (otac->id < br) ok = 0;
					else {
						tek = otac;

						novi = new Cvor(br);
						if (br % 2) {
							i = br / 2 + 1;
						}
						else {
							i = br / 2;
						}
						int j = 0;
						while (i < tek->id) {
							novi->month[j] = tek->month[i]; novi->year[j] = tek->year[i]; novi->pok[j] = tek->pok[i];
							i++; j++; novi->id++;
						}
						novi->pok[j] = tek->pok[i];
						//stani
						novi->otac = tek->otac;
						tek->id = br / 2 + 1;
						//ako nema oca napravi ga
						//prebacujem mu najveci od desnog sina i tamo dekrementiram id
						if (tek->otac == nullptr) {
							otac = new Cvor(br);
							i = tek->id - 1;
							otac->month[otac->id] = tek->month[i];
							otac->year[otac->id] = tek->year[i];
							otac->pok[otac->id] = tek;
							otac->id++;
							tek->id--;
							otac->pok[otac->id] = novi;
							tek->otac = otac;
							novi->otac = otac;
							return true;
						}
						// ako ima oca predji i prebaci mu pokazivac i sredinu
						else {
							otac = tek->otac;
							i = 0;
							while (i < otac->id) {
								if (tek->year[br / 2 - 1] < otac->year[i]) break;
								else if (tek->year[br / 2 - 1] == otac->year[i] && tek->month[br / 2 - 1] < otac->month[i]) break;
								i++;
							}

							if (i == otac->id) {
								otac->month[i] = tek->month[tek->id - 1]; otac->year[i] = tek->year[tek->id - 1]; otac->pok[otac->id + 1] = novi;
								otac->id++;
								tek->id--;
							}
							else if (i < otac->id) {
								int j = otac->id;
								while (j > i) {
									otac->month[j] = otac->month[j - 1]; otac->year[j] = otac->year[j - 1]; otac->pok[j + 1] = tek->pok[j];
									j--;
								}
								//ovde
								otac->month[i] = tek->month[tek->id - 1]; otac->year[i] = tek->year[tek->id - 1]; otac->pok[i + 1] = novi;
								otac->id++;
								tek->id--;
							}
						}
					



					}
				}



			}



		}

		return true;




	}

};


#endif // !__CVOR_H__