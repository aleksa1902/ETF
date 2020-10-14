#include <dos.h>
#include "PCB.h"
#include "ListaPCB.h"
#include "SCHEDULE.h"
#include "Timer.h"
#include "Thread.h"

PCB* PCB::running = 0;
ListaPCB* PCB::globalnaListaPCB = new ListaPCB();

PCB::PCB(Thread* t, StackSize s, Time tim){
	timeSlice = tim;
	stackSize = s;
	thread = t;
	ss = 0; bp = 0; sp = 0; stack=0;
	semaforBlok = 0;
	this->dodeliNova();
	list = new ListaPCB();
	dodajUGlobalnuListu(this);
}

void PCB::dodajUGlobalnuListu(PCB* pcb){
	globalnaListaPCB->dodajNaKraj(pcb);
}

PCB::~PCB(){
	if(thread != 0){
		thread->myPCB = 0;
		delete thread;
	}
	delete list;
	delete[] stack;
}

void PCB::napraviStek(){
	stack = new unsigned[stackSize];
#ifndef BCC_BLOCK_IGNORE
		stack[stackSize - 1] = 0x200;
		stack[stackSize - 2] = FP_SEG(PCB::wrapper);
		stack[stackSize - 3] = FP_OFF(PCB::wrapper);

		sp = FP_OFF(stack + (stackSize - 12));
		ss = FP_SEG(stack + (stackSize - 12));
		bp = FP_OFF(stack + (stackSize - 12));
#endif
}

Thread* PCB::getThread(){
	return thread;
}


void PCB::wrapper(){
	PCB::running->thread->run();
	PCB::running->timeSlice++;
	PCB::running->dodeliFinished();

	Timer::lockedFlag = 0;

	while(PCB::running->list->uzmiPoslednji() != 0){
		PCB::running->list->promeniStatus();

		Scheduler::put(PCB::running->list->uzmiPoslednji());

		PCB::running->list->izbaciPoslednji();
	}

	Timer::lockedFlag = 1;

	dispatch();
}


void PCB::dodeliReady(){
	this->trenStatus = ready;
}

void PCB::dodeliBlocked(){
	this->trenStatus = blocked;
}

void PCB::dodeliFinished(){
	this->trenStatus = finished;
}

void PCB::dodeliNova(){
	this->trenStatus = nova;
}

void PCB:: dodeliPrazna(){
	this->trenStatus = prazna;
}
