#include "Heap.h"

void Heap::init()
{
	first = last = nullptr;
}

void Heap::add(int elem, int & steps)
{
	if (first) {
		HeapNode* t = new HeapNode;
		t->level = 0;
		t->info = elem;
		//t->brat = first;
		t->sin = nullptr;
		t->par = nullptr;
		t->brat = nullptr;
		//first = t;
		Heap noviH;
		noviH.first = t;
		noviH.last = t;
		unija(noviH, steps);
		//delete noviH;
	}
	else {
		last = first = new HeapNode;
		first->info = elem;
		first->level = 0;
		first->brat = nullptr;
		first->sin = nullptr;
		first->par = nullptr;
	}

}

int Heap::get()
{
	int min = first->info;
	HeapNode* i = first->brat;
	while (i != nullptr) {
		if (i->info < min)
		{
			min = i->info;
		}
		i = i->brat;
	}
	return min;
}

void Heap::unija(Heap& h, int & steps)
{
	h.last->brat = first;
	first = h.first;
	HeapNode* tek = first, *pom1 = nullptr;
	HeapNode* pret = nullptr, *pret1 = nullptr, *min = nullptr, *pretmin = nullptr;
	HeapNode* sled = tek->brat;
	while (tek) {
		min = tek;
		pretmin = nullptr;
		sled = tek->brat;
		pret1 = tek;
		steps++;
		while (sled) {
			if (min->level > sled->level) {
				min = sled;
				pretmin = pret1;
			}
			sled = sled->brat;
			pret1 = pret1->brat;
		}
		if (min != tek) {
			if (tek->brat == min) {
				if (pret == nullptr) {
					tek->brat = min->brat;
					min->brat = tek;
					first = min;
					tek = min;
				}
				else {
					tek->brat = min->brat;
					min->brat = tek;
					pret->brat = min;
					tek = min;
				}
			}
			else {
				if (pret == nullptr) {
					pom1 = min->brat;
					min->brat = tek->brat;
					tek->brat = pom1;
					first = min;
					pretmin->brat = tek;
					tek = min;
				}
				else {
					pret->brat = min;
					pom1 = tek->brat;
					tek->brat = min->brat;
					min->brat = pom1;
					pretmin->brat = tek;
					tek = min;
				}
			}
		}
		if (tek == first) {
			pret = first;
		}
		else pret = pret->brat;
		tek = tek->brat;
	}



	if (first == nullptr)
	{
		return;
	}
	pret = nullptr;
	tek = first;
	sled = tek->brat;
	while (sled != nullptr)
	{
		if ((tek->level != sled->level) || (sled->brat != nullptr && sled->brat->level == tek->level))
		{
			pret = tek;
			tek = sled;
		}
		else
		{
			if (tek->info <= sled->info)
			{
				tek->brat = sled->brat;
				steps++;
				SpajanjeCvorova(tek, sled);
			}
			else
			{
				if (pret == nullptr)
				{
					first = sled;
				}
				else
				{
					pret->brat = sled;
				}
				steps++;
				SpajanjeCvorova(sled, tek);
				tek = sled;
			}
		}
		sled = tek->brat;
	}
	tek = first;
	while (tek) {
		last = tek;
		tek = tek->brat;
	}
}

void Heap::UnijaMax(Heap & h, int & steps)
{
	h.last->brat = first;
	first = h.first;
	steps++;
	HeapNode* tek = first, *pom1 = nullptr;
	HeapNode* pret = nullptr, *pret1 = nullptr, *min = nullptr, *pretmin = nullptr;
	HeapNode* sled = tek->brat;
	while (tek) {
		min = tek;
		pretmin = nullptr;
		sled = tek->brat;
		pret1 = tek;
		while (sled) {
			if (min->level > sled->level) {
				min = sled;
				pretmin = pret1;
			}
			steps++;
			sled = sled->brat;
			pret1 = pret1->brat;
		}
		if (min != tek) {
			if (tek->brat == min) {
				if (pret == nullptr) {
					tek->brat = min->brat;
					min->brat = tek;
					first = min;
				}
				else {
					tek->brat = min->brat;
					min->brat = tek;
					pret->brat = min;
				}
			}
			else {
				if (pret == nullptr) {
					pom1 = min->brat;
					min->brat = tek->brat;
					tek->brat = pom1;
					first = min;
					pretmin->brat = tek;
					tek = min;
				}
				else {
					pret->brat = min;
					pom1 = tek->brat;
					tek->brat = min->brat;
					min->brat = pom1;
					pretmin->brat = tek;
					tek = min;
				}
			}
		}
		if (tek == first) {
			pret = first;
		}
		else pret = pret->brat;
		tek = tek->brat;
	}



	if (first == nullptr)
	{
		return;
	}
	pret = nullptr;
	tek = first;
	sled = tek->brat;
	while (sled != nullptr)
	{
		if ((tek->level != sled->level) || (sled->brat != nullptr && sled->brat->level == tek->level))
		{
			pret = tek;
			tek = sled;
		}
		else
		{
			if (tek->info >= sled->info)
			{
				tek->brat = sled->brat;
				steps++;
				SpajanjeCvorova(tek, sled);
			}
			else
			{
				if (pret == nullptr)
				{
					first = sled;
				}
				else
				{
					pret->brat = sled;
				}
				steps++;
				SpajanjeCvorova(sled, tek);
				tek = sled;
			}
		}
		sled = tek->brat;
	}
	while (tek) {
		last = tek;
		tek = tek->brat;
	}
}

void Heap::Convert()
{
	int br;
	int s;
	stack <int> st;
	while (first) {
		br = get();
		st.push(br);
		Delete(s);
	}
	while (!st.empty()) {
		br = st.top();
		st.pop();
		AddMax(br, s);
	}
}

int Heap::Delete(int & steps)
{
	HeapNode* i = first;
	HeapNode* min = i;
	HeapNode* prevmin = nullptr;
	while (i->brat != nullptr)
	{
		if (i->brat->info < min->info)
		{
			steps++;
			prevmin = i;
			min = i->brat;
		}
		i = i->brat;
	}

	i = first;
	if (prevmin == nullptr)
	{
		first = first->brat ? first->brat : first->sin;
	}
	else
	{
		prevmin->brat = (min->brat == nullptr ? nullptr : min->brat);
	}
	if (last == min) {
		if (prevmin)
			last = prevmin;
		else {
			i = first;
			while (i) {
				last = i;
				i = i->brat;
			}
		}
	}
	if (prevmin == nullptr && min->brat == nullptr) {
		min->brisi();
		return steps;
	}
	if (min->sin != nullptr) {
		min->brat = nullptr;
		HeapNode* tek = min->sin, *l = min->sin;
		while (tek) {
			tek->par = nullptr;
			if (tek->brat == nullptr) l = tek;
			tek = tek->brat;
		}
		tek = min->sin;
		min->brisi();
		Heap hp;
		hp.first = tek;
		hp.last = l;
		unija(hp, steps);
		return steps;
	}
	min->brisi();
	return steps;
}

void Heap::destroy()
{
	HeapNode * next = first, *gran = new HeapNode, *tek = nullptr, *pom = nullptr;
	gran->info = -10;
	//int i;
	queue <HeapNode*> q;
	while (next) {
		q.push(next);
		next = next->brat;
	}
	q.push(gran);
	while (!q.empty()) {
		next = q.front();
		q.pop();
		//q.push(gran);
		while (next != gran) {
			tek = next->sin;
			//cout << next->info;

			//next->brisi();
			while (tek) {
				q.push(tek);
				tek = tek->brat;
			}
			delete next;
			next = q.front();
			q.pop();
		}
		if (!q.empty()) q.push(gran);
		//cout << endl;
	}
}

void Heap::SpajanjeCvorova(HeapNode* roditelj, HeapNode* dete)
{
	dete->par = roditelj;
	dete->brat = roditelj->sin;
	roditelj->sin = dete;
	roditelj->level++;
}

void Heap::print(HeapNode * p)
{
	HeapNode * next = p, *gran = new HeapNode, *tek;
	gran->info = -10;
	//int i;
	queue <HeapNode*> q;
	while (next) {
		q.push(next);
		next = next->brat;
	}
	q.push(gran);
	while (!q.empty()) {
		next = q.front();
		q.pop();
		//q.push(gran);
		while (next != gran) {
			cout << next->info << "  ";
			tek = next->sin;
			while (tek) {
				q.push(tek);
				tek = tek->brat;
			}
			next = q.front();
			q.pop();
		}
		if (!q.empty()) q.push(gran);
		cout << endl;
	}
}


void Heap::AddMax(int elem, int& steps) {
	if (first) {
		HeapNode* t = new HeapNode;
		t->level = 0;
		t->info = elem;
		//t->brat = first;
		t->sin = nullptr;
		t->par = nullptr;
		t->brat = nullptr;
		//first = t;
		Heap noviH;
		noviH.first = t;
		noviH.last = t;
		UnijaMax(noviH, steps);
		//delete noviH;
	}
	else {
		last = first = new HeapNode;
		first->info = elem;
		first->level = 0;
		first->brat = nullptr;
		first->sin = nullptr;
		first->par = nullptr;
	}
}



