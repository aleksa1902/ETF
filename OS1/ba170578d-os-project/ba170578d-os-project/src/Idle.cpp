/*
 * Idle.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: OS1
 */

#include "Idle.h"
#include "Thread.h"

Idle* Idle::praznaNit = 0;

	Idle::Idle():Thread(defaultStackSize, 1){
		praznaNit = this;
		praznaNit->myPCB->dodeliPrazna();
		start();
	}

	PCB* Idle::dohvatiPCB(){
		return praznaNit->myPCB;
	}

	Idle::~Idle(){}

	void Idle::deleteIdle(){
		if(praznaNit != 0){
			delete praznaNit;
			praznaNit = 0;
		}
	}

	void Idle::run(){
		while(1){}
	}
