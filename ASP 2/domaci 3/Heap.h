#ifndef _HEAP_H_
#define _HEAP_H_

#include "HeapNode.h"
#include <queue>
#include <stack>

class Heap
{
public:
	HeapNode * first;
	HeapNode* last;
	Heap() {
		init();
	}
	void init();
	void add(int elem, int &steps);
	void AddMax(int elem, int &steps);
	int get();
	void unija(Heap& h, int &steps);
	void UnijaMax(Heap& h, int &steps);
	void Convert();
	int Delete(int &steps);
	void destroy();
	void SpajanjeCvorova(HeapNode* roditelj, HeapNode* dete);

	~Heap() {}
	void print(HeapNode* p);

};

#endif // !_HEAP_H_