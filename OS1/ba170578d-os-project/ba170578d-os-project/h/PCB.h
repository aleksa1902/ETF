#ifndef PCB_H_
#define PCB_H_
#include "ListaPCB.h"
#include "Thread.h"

enum Status{nova ,blocked, running, ready, finished, prazna};

class PCB{
private:
	friend class Thread;
	Thread* thread;
	StackSize stackSize;
public:
	unsigned bp;
	unsigned sp;
	unsigned ss;

	int semaforBlok;

	Time timeSlice;
	enum Status trenStatus;

	static PCB* running;
	ListaPCB* list;
	unsigned* stack;

	static ListaPCB* globalnaListaPCB;

	PCB(Thread*, StackSize, Time);

	~PCB();

	void napraviStek();

	Thread* getThread();

	static void wrapper();

	void dodajUGlobalnuListu(PCB* pcb);

	void dodeliBlocked();
	void dodeliReady();
	void dodeliFinished();
	void dodeliPrazna();
	void dodeliNova();

};

#endif /* PCB_H_ */                                                                                                                                                                                                                                                 
