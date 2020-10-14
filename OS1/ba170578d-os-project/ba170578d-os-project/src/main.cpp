#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include "Idle.h"
#include "KernelSe.h"
#include "Semaphor.h"
#include "Schedule.h"
#include "Event.h"
#include<dos.h>
#include <iostream.h>

#include <MALLOC.H>
#include <STDLIB.H>


extern int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]){
	new Thread(100);
	new Idle();

	Timer::inic();

	int ret;
	ret = userMain(argc,argv);



	PCB::globalnaListaPCB->~ListaPCB();
	KernelSem::brisanjeSemafora();

	Timer::restore();

	Idle::praznaNit->deleteIdle();

	return ret;
}



