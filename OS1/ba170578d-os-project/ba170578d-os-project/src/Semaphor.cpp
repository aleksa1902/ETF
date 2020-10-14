/*
 * Semaphor.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: OS1
 */
#include "KernelSe.h"
#include "ListKSem.h"
#include "Semaphor.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init,this);
	KernelSem::listaSemafora->ubaciNaKraj(myImpl);
}
Semaphore::~Semaphore (){
	if(myImpl != 0){
		KernelSem::listaSemafora->izbaci(myImpl);
		myImpl->sem = 0;
		delete myImpl;
	}
}
int Semaphore::wait (Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}
int Semaphore::signal(int n){
	return myImpl->signal(n);
}
int Semaphore::val () const{
	return myImpl->val();
}


