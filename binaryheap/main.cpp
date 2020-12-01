#include <iostream>
#include "Heap.h"

using namespace std;

int main()
{
	Heap TestHeap;
	TestHeap.insert(2);
	TestHeap.insert(3); 
	TestHeap.insert(4); 
	TestHeap.insert(8);
	TestHeap.insert(1);
	TestHeap.insert(7);
	TestHeap.insert(6);
	TestHeap.insert(33);
	TestHeap.insert(9);
	TestHeap.print_to_console();
	cout << endl;
	TestHeap.remove(8);
	TestHeap.contains(33);
	TestHeap.print_to_console();

	cout << "\nBreadth-first traverse: ";
	Iterator* deep = TestHeap.create_bft_iterator();
	while (deep->has_next())
	{
		cout << deep->next() << " ";
	}

	cout << "\nDepth-first traverse: ";
	deep = TestHeap.create_dft_iterator();
	while (deep->has_next())
	{
		cout << deep->next() << " ";
	}
}