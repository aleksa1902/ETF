/*
 * Timer.cpp
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */

#include "SCHEDULE.H"
#include "Timer.h"
#include "PCB.h"
#include "KernelSe.h"
#include "ListKSem.h"
#include "Idle.h"
#include <dos.h>

#define lock asm cli //zabranjuje prekide

#define unlock asm sti //dozvoljava prekide

extern void tick();

unsigned tsp;
unsigned tss;
unsigned tbp;
unsigned Timer::brojac=0;
int Timer::lockedFlag = 1;


int Timer::zahtevana_promena_konteksta = 0;
pInterrupt Timer::oldTimerRoutine = 0;

void Timer::inic(){
#ifndef BCC_BLOCK_IGNORE
	lock
	Timer::oldTimerRoutine = getvect(8);
	setvect(8,Timer::timer);
	unlock
#endif
}

void Timer::restore(){
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(8,Timer::oldTimerRoutine);
	unlock
#endif
}

void interrupt Timer::timer(...){

	if(!zahtevana_promena_konteksta) {

		if(PCB::running->timeSlice != 0)
				Timer::brojac--;
			KernelSem::listaSemafora->proveravanjeNiti();
			tick();
		}

		if((Timer::brojac == 0 && PCB::running->timeSlice != 0) || zahtevana_promena_konteksta == 1){
			if(lockedFlag == 1){
				zahtevana_promena_konteksta = 0;

				asm{
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}

				PCB::running->sp = tsp;
				PCB::running->ss = tss;
				PCB::running->bp = tbp;


				if(PCB::running->trenStatus!=finished && PCB::running->trenStatus != blocked && PCB::running != Idle::dohvatiPCB()){
					PCB::running->dodeliReady();
					Scheduler::put(PCB::running);
				}

					PCB::running = Scheduler::get();


					if(PCB::running != 0)
						PCB::running->trenStatus = running;
					else
						ubaciPraznuNit();


					Timer::brojac = PCB::running->timeSlice;


					tsp=PCB::running->sp ;
					tss=PCB::running->ss ;
					tbp=PCB::running->bp ;

					asm{
						mov sp, tsp
						mov ss, tss
						mov bp, tbp
					}
				}else{
					zahtevana_promena_konteksta = 1;
				}
			}
	//}

	if(!zahtevana_promena_konteksta){
		Timer::oldTimerRoutine();
	}
}


void Timer::ubaciPraznuNit(){
	PCB::running =Idle::praznaNit->dohvatiPCB();
	PCB::running->dodeliPrazna();
}
