/*
 * IvtEntry.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: OS1
 */

#include "IvtEntry.h"
#include "EventKer.h"
#include <DOS.H>

#define lock asm cli
#define unlock asm sti

IVTEntry* IVTEntry::tabela[256];

IVTEntry::IVTEntry(IVTNo ivt, ppInterrupt p){
#ifndef BCC_BLOCK_IGNORE
	staraPrekidnaRutina = getvect(ivt);
	setvect(ivt, p);
#endif
	ivtNo = ivt;
	kEvent = new KernelEv();
	tabela[ivt] = this;
}

KernelEv* IVTEntry::getkevent(){
	return kEvent;
}

void IVTEntry::calloldInterrupt(){
	staraPrekidnaRutina();
}

KernelEv* IVTEntry::getablekevent(IVTNo ivt){
	return tabela[ivt]->kEvent;
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(ivtNo, staraPrekidnaRutina);
	unlock
#endif
	staraPrekidnaRutina = 0;
	delete kEvent;
	kEvent = 0;
	tabela[ivtNo] = 0;
}
