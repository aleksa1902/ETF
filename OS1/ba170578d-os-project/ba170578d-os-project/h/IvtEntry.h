/*
 * IvtEntry.h
 *
 *  Created on: Sep 15, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "EventKer.h"

typedef void interrupt (*ppInterrupt)(...);
typedef unsigned char IVTNo;

class IVTEntry{
public:
	IVTEntry(IVTNo ivt, ppInterrupt p);
	~IVTEntry();

	void calloldInterrupt();

	KernelEv* getkevent();
	static KernelEv* getablekevent(IVTNo ivt);

private:
	friend class KernelEv;

	IVTNo ivtNo;
	static IVTEntry* tabela[256];
	KernelEv* kEvent;
	ppInterrupt staraPrekidnaRutina;
};



#endif /* IVTENTRY_H_ */
