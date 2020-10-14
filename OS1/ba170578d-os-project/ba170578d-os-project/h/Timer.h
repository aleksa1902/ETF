#ifndef TIMER_H_
#define TIMER_H_

typedef void interrupt (*pInterrupt)(...);

class Timer{

public:
	static int zahtevana_promena_konteksta;
	static pInterrupt oldTimerRoutine;
	static unsigned brojac;
	static void inic();
	static void restore();
	static void interrupt timer(...);
	static int lockedFlag;

	static void ubaciPraznuNit();

};





#endif /* TIMER_H_ */
