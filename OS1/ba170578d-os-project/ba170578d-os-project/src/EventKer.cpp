/*
 * EventKer.cpp
 *
 *  Created on: Sep 15, 2019
 *      Author: OS1
 */

#include "Timer.h"
#include "SCHEDULE.H"
#include "EventKer.h"
#include "IvtEntry.h"
#include "PCB.h"
#include "Event.h"

KernelEv::KernelEv(){
	nitVlasnik = 0;
	value = 0;
}

void KernelEv::wait(){
	Timer::lockedFlag = 0;
	if(value == 0){
		value = -1;
		nitVlasnik = PCB::running;

		PCB::running->dodeliBlocked();

		Timer::lockedFlag = 1;
		dispatch();
	}
	Timer::lockedFlag = 1;
}

void KernelEv::signal(){
	Timer::lockedFlag = 0;

	if(value == -1){
		if(nitVlasnik->trenStatus != finished){
			nitVlasnik->dodeliReady();
			Scheduler::put(nitVlasnik);
		}
		value = 0;
		nitVlasnik = 0;
	}

	Timer::lockedFlag = 1;

}

KernelEv* KernelEv::getkevent(IVTNo ivt){
	return IVTEntry::getablekevent(ivt);
}

KernelEv::~KernelEv(){}
