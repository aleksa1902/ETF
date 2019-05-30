#ifndef _HEAPNODE_H_
#define _HEAPNODE_H_

#include <iostream>

using namespace std;


class HeapNode
{
public:
	HeapNode() {
		sin = brat = par = nullptr;
		level = -1; info = -1;
	}
	~HeapNode() {
		brisi();
	}
	void brisi() {
		//delete sin;
		//delete brat;
		//delete par;
		level = -1;
		info = -1;
	}
	HeapNode* sin;
	HeapNode* brat;
	HeapNode* par;
	int level;
	int info;
};

#endif // !_HEAPNODE_H_