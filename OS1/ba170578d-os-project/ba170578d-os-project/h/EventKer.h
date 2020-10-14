/*
 * EventKer.h
 *
 *  Created on: Sep 15, 2019
 *      Author: OS1
 */

#ifndef EVENTKER_H_
#define EVENTKER_H_

class PCB;

typedef unsigned char IVTNo;

class KernelEv{
public:
	KernelEv ();
	~KernelEv ();
	void wait ();
	void signal();
	static KernelEv* getkevent(IVTNo ivt);

private:
	friend class Event;
	friend class IVTEntry;

	PCB* nitVlasnik;
	int value;
};



#endif /* EVENTKER_H_ */
