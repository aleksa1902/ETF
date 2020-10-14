/*
 * Event.h
 *
 *  Created on: Sep 15, 2019
 *      Author: OS1
 */

#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;

#include "EventKer.h"
#include "IvtEntry.h"

class KernelEv;
class PCB;

class Event{
public:
	Event (IVTNo ivt);
	~Event ();
	void wait ();

protected:
	friend class KernelEv;
	void signal(); // can call KernelEv

private:
	KernelEv* myImpl;
	PCB* nitVlasnik;
};

#define PREPAREENTRY(no, flag)\
	void interrupt intr##no(...);\
	IVTEntry ivte##no(no, intr##no);\
	void interrupt intr##no(...){\
		ivte##no.getkevent()->signal();\
		if(flag) ivte##no.calloldInterrupt();\
	}


#endif
