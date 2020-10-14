/*
 * KernelSe.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: OS1
 */

#include "KernelSe.h"
#include "ListKSem.h"
#include "ListaPCB.h"
#include "Semaphor.h"
#include "PCB.h"
#include "Timer.h"
#include "SCHEDULE.H"
#include "Thread.h"


	ListKernelSem* KernelSem::listaSemafora = new ListKernelSem();

	KernelSem::KernelSem(int init, Semaphore* semafor){
		value = init;
		sem = semafor;
		listWaitDifZero = new ListaPCB();
		listWaitIsZero = new ListaPCB();
	}

	KernelSem::~KernelSem (){
		if(sem != 0){
			sem->myImpl = 0;
			delete sem;
		}



		while(listWaitIsZero->uzmiPrvi()){
			listWaitIsZero->uzmiPrvi()->dodeliReady();
			Scheduler::put(listWaitIsZero->uzmiPrvi());
			listWaitIsZero->izbaciPrvi();
			}
		while(listWaitDifZero->uzmiPrvi()){
			listWaitDifZero->uzmiPrvi()->dodeliReady();
			Scheduler::put(listWaitDifZero->uzmiPrvi());
			listWaitDifZero->izbaciPrvi();
		}

		delete listWaitDifZero;
		delete listWaitIsZero;

		listWaitDifZero = 0;
		listWaitIsZero = 0;

		value = 0;

	}

	int KernelSem::wait (Time maxTimeToWait){
		Timer::lockedFlag=0;

		value--;

		if(value < 0){

			if(maxTimeToWait == 0){
				PCB::running->dodeliBlocked();
				listWaitIsZero->dodajNaKraj(PCB::running);
			}

			else if(maxTimeToWait > 0){
				PCB::running->dodeliBlocked();
				listWaitDifZero->prioritetnaLista(PCB::running, maxTimeToWait);
			}

			else if(maxTimeToWait < 0){
				Timer::lockedFlag = 1;

				return 1;
			}

			Timer::lockedFlag = 1;

			dispatch();

			return provera();

		}

		Timer::lockedFlag = 1;

		return 1;

	}


	int KernelSem::signal(int n){
		int brojOdblNiti = 0;

		Timer::lockedFlag = 0;

		if(n == 0){
			value++;

			if(value <= 0){
				if(listWaitIsZero->uzmiPrvi()){
					listWaitIsZero->uzmiPrvi()->trenStatus = ready;
					listWaitIsZero->uzmiPrvi()->dodeliReady();
					Scheduler::put(listWaitIsZero->uzmiPrvi());
					listWaitIsZero->izbaciPrvi();

					Timer::lockedFlag = 1;

					return 0;
				}else if(listWaitDifZero->uzmiPrvi()){
					listWaitDifZero->uzmiPrvi()->dodeliReady();
					listWaitIsZero->uzmiPrvi()->semaforBlok = 1;
					Scheduler::put(listWaitDifZero->uzmiPrvi());
					listWaitDifZero->izbaciPrvi();

					Timer::lockedFlag = 1;

					return 0;
				}else{
					Timer::lockedFlag = 1;

					return 0;
				}
			}
		}else if(n > 0){


			while(n > 0){
				value++;
				if(listWaitIsZero->uzmiPrvi() && value<=0){
					listWaitIsZero->uzmiPrvi()->dodeliReady();
					listWaitIsZero->uzmiPrvi()->semaforBlok = 1;
					Scheduler::put(listWaitIsZero->uzmiPrvi());
					listWaitIsZero->izbaciPrvi();
					n--;
					brojOdblNiti++;
				}else if(listWaitDifZero->uzmiPrvi() && value<=0){
					listWaitDifZero->uzmiPrvi()->dodeliReady();
					listWaitIsZero->uzmiPrvi()->semaforBlok = 1;
					Scheduler::put(listWaitDifZero->uzmiPrvi());
					listWaitDifZero->izbaciPrvi();
					n--;
					brojOdblNiti++;
				}else n--;

			}

			Timer::lockedFlag = 1;

			return brojOdblNiti;

		}else{
			Timer::lockedFlag = 1;

			return n;
		}
		Timer::lockedFlag = 1;
		return 0;

	}

	int KernelSem::val () const{
		return value;
	}




	int KernelSem::provera(){
			Timer::lockedFlag = 0;

			if(PCB::running->semaforBlok == 1){ //Unblokirano od signal()
				PCB::running->semaforBlok = 0;
				Timer::lockedFlag = 1;
				return 1;
			}

			PCB::running->semaforBlok = 0; //Unblokirano od Timera
			Timer::lockedFlag = 1;
			return 0;
		}

	void KernelSem::brisanjeSemafora(){
		if(listaSemafora){
			delete listaSemafora;
			listaSemafora = 0;
		}
	}
