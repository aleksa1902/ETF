/*
 * Event.cpp
 *
 *  Created on: Sep 15, 2019
 *      Author: OS1
 */

#include "Event.h"
#include "EventKer.h"
#include "PCB.h"

Event::Event(IVTNo ivt){
	myImpl = KernelEv::getkevent(ivt);
	nitVlasnik = PCB::running;
}

void Event::wait(){
	if(PCB::running == nitVlasnik){
		myImpl->wait();
	}
}


void Event::signal(){
	myImpl->signal();
}

Event::~Event(){}
