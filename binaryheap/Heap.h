#pragma once
#include "Iterator.h"
#include "LinkedList.h"

template <class Any> void SWAP(Any& a, Any& b); // swap

class Heap
{
public:
	Heap(int* heapArr = nullptr, size_t heapSize = 0, size_t heapMaxSize = 1)
	{
		this->heapSize = heapSize;
		this->heapMaxSize = heapMaxSize;
		this->heapArr = new int[heapMaxSize];
	};
	~Heap()
	{
		delete heapArr;
		heapSize = 0;
	};
	// metods
	void print_to_console();

	void siftUp(int cur);
	void siftDown(int cur);

	int depth(size_t cur);
	bool contains(int data); // 1 //
	void insert(int data);   // 2 //
	void remove(int data);   // 3 //

private:
	size_t heapSize;
	size_t heapMaxSize;
	int* heapArr;

public:
	Iterator* create_bft_iterator(); // 5 // straight breadth-first traverse
	Iterator* create_dft_iterator(); // 4 // depth-first traverse



	class bft_iterator : public Iterator
	{
	public:
		bft_iterator(int* start, int max)
		{
			curSize = max;
			current = start;
			i = 0;
		};
		~bft_iterator()
		{
			delete current;
		};

		bool has_next() override;
		int next() override;

	private:
		int* current;
		int curSize;
		int i;
	};

	class dft_iterator : public Iterator // straight depth-first traverse
	{
	public:
		dft_iterator(int* start, int max)
		{
			current = start;
			curSize = max;
			stack = new LinkedList; // index stack
			index = 0; // current index
			i = 0; // number of passed elements
			stack->push_back(index);
		};
		~dft_iterator()
		{
			delete stack;
			delete current;
		};
		bool has_next() override;
		int next() override;
	private:
		LinkedList* stack;
		int* current;
		int curSize;
		int index;
		int i;
	};
};
