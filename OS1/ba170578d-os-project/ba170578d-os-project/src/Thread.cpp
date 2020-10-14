#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Timer.h"

ID Thread::Id = 0;


#define lock asm cli

#define unlock asm sti

	Thread::Thread (StackSize stackSize, Time timeSlice){
		myPCB = new PCB(this, stackSize, timeSlice);
		id = Id++;
	}

	void Thread::start(){
		myPCB->napraviStek();
		if(myPCB->trenStatus!=prazna && myPCB->trenStatus == nova){
			myPCB->dodeliReady();
			Scheduler::put(myPCB);
		}
	}

	void Thread::waitToComplete(){
		if(myPCB->trenStatus != finished && myPCB->trenStatus != prazna){
			if(myPCB != PCB::running){
				PCB::running->dodeliBlocked();
				myPCB->list->dodajNaKraj(PCB::running);


				dispatch();
			}
		}
	}


	Thread::~Thread(){
		waitToComplete();

		if(myPCB != 0){
			myPCB->thread = 0;
			delete myPCB;
		}
	}

	ID Thread::getId(){
		return id;
	}

	ID Thread::getRunningId(){
		return PCB::running->getThread()->id;
	}

	Thread * Thread::getThreadById(ID id){
		if(id == 0) return 0;

		PCB* p = PCB::globalnaListaPCB->pretraga(id);

		if(p == 0) return 0;
		else return p->getThread();
	}

	void dispatch(){
#ifndef BCC_BLOCK_IGNORE
		lock;
		Timer::zahtevana_promena_konteksta = 1;
		Timer::timer();
		unlock;
#endif
	}


	Thread::Thread(int i){
		myPCB = new PCB(this, defaultStackSize, 20);
		id = Id++;
		PCB::running = myPCB;
		Timer::brojac = 20;

		myPCB->trenStatus = running;
		PCB::globalnaListaPCB->dodajNaKraj(myPCB);


	}




