/*
 * KernelSe.h
 *
 *  Created on: Sep 6, 2019
 *      Author: OS1
 */

#ifndef KERNELSE_H_
#define KERNELSE_H_

#include "Semaphor.h"

typedef unsigned int Time;

class ListaPCB;
class ListKernelSem;

class KernelSem{
public:
	int value;


	ListaPCB* listWaitIsZero;
	ListaPCB* listWaitDifZero;
	static ListKernelSem* listaSemafora;

	KernelSem(int init=1, Semaphore* semafor);
	virtual ~KernelSem ();
	int wait (Time maxTimeToWait);
	int signal(int n=0);
	int val () const; // Returns the current value of the semaphore

	int provera();

	static void brisanjeSemafora();

private:
	friend class Semaphore;
	Semaphore* sem;


};



#endif /* KERNELSE_H_ */
