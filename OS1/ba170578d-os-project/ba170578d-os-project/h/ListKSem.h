/*
 * ListKSem.h
 *
 *  Created on: Sep 6, 2019
 *      Author: OS1
 */

#ifndef LISTKSEM_H_
#define LISTKSEM_H_

#include "KernelSe.h"

class ListKernelSem{
private:
	struct Polje{
		KernelSem* kernelSem;
		Polje* sled;

		Polje(KernelSem* ks){
			kernelSem = ks;
			sled = 0;
		}
		~Polje(){}
	};

public:
	Polje *prvi, *poslednji;

	ListKernelSem();
	void ubaciNaPocetak(KernelSem* ks);
	void ubaciNaKraj(KernelSem* ks);
	void izbaciSaPocetka();
	void izbaciSaKraja();
	void izbaci(KernelSem* ks);
	KernelSem* uzmiPrvi();
	KernelSem* uzmiPosl();

	void proveravanjeNiti();

	~ListKernelSem();

};



#endif /* LISTKSEM_H_ */
