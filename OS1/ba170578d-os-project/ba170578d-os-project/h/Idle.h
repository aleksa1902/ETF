/*
 * Idle.h
 *
 *  Created on: Sep 13, 2019
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"
#include "PCB.h"

class Idle:public Thread{
public:
	Idle();
	static PCB* dohvatiPCB();
	virtual ~Idle();
	static void deleteIdle();

	virtual void run();
	static Idle* praznaNit;
};



#endif /* IDLE_H_ */
