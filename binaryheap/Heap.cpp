#include "Heap.h";
#include "LinkedList.h"
#include <Windows.h>
#include <iostream>


template <class Any> void SWAP(Any& a, Any& b) // swap
{
	Any buf = a; a = b; b = buf;
}

void Heap::siftUp(int cur)
{
	if (cur < heapSize)
		while (heapArr[cur] < heapArr[(cur - 1) / 2]) // (cur - 1) / 2 - parent index
		{
			SWAP(heapArr[cur], heapArr[(cur - 1) / 2]);
			cur = (cur - 1) / 2;
		}
}

void Heap::siftDown(int cur)
{
	int Child_L; // child left
	int Child_R; // child right
	int Min_Child;
	while (cur * 2 + 1 < heapSize) 
	{	// cur - parent
		Child_L = cur * 2 + 1; // child left
		Child_R = cur * 2 + 2; // child right
		if ((Child_R < heapSize) && (heapArr[Child_R] <= heapArr[Child_L]))
		{
			Min_Child = Child_R;
		}
		else// if (heapArr[Child_L] < heapArr[Child_R])
		{
			Min_Child = Child_L;
		}
		if (heapArr[cur] > heapArr[Min_Child]) // if parent is bigger that child
		{
			SWAP(heapArr[cur], heapArr[Min_Child]);
			cur = Min_Child;
		}
		else break;
	}
}

void Heap::print_to_console()
{
	int changedepth = 0;
	int index = 1;
	if (heapSize == 0) std::cout << "\nHeap is empty";
	else
		for (int i = 0; i < heapSize; i++)
		{
			if (i * 2 + 1 == index)
			{
				std::cout << std::endl;
				index = index * 2 + 1;
			}
			std::cout << heapArr[i] << " ";
		}
	std::cout << "\nSize heap: " << heapSize;
}

int Heap::depth(size_t index) // found depth of an element by index
{
	int child = 1, depth = 0;
	while (child <= index)
	{
		child = child * 2 + 1;
		depth++;
	}
	return depth;
}

bool Heap::contains(int data) // 1 // found element
{
	for (int i = 0; i < heapSize; i++)
	{
		if (heapArr[i] == data) // element found
		{
			std::cout << "\nDepth of a "<< data << " node = " << depth(i);
			return true;
		}
	}
	return false;
}

void Heap::insert(int data) // 2 //
{
	heapSize++;
	if (heapSize > heapMaxSize) // heap is full
	{
		int* update;
		heapMaxSize = heapMaxSize * 2 + 1;
		update = (int*)realloc(heapArr, heapMaxSize * sizeof(int));
		if (!update)
		{
			throw std::out_of_range("Update error");
		}
		else
		{
			heapArr = update;
		}
	}
	heapArr[heapSize - 1] = data; 
	siftUp(heapSize - 1);
};

void Heap::remove(int data) // (remove the first found elemnt)
{
	int i = 0;
	while ((i < heapSize) && (heapArr[i] != data))
	{
		i++;
	}
	if (heapArr[i] != data)
	{
		throw std::out_of_range("not found");
	}
	SWAP(heapArr[i], heapArr[heapSize - 1]);
	heapSize--;
	siftDown(i);
}

Iterator* Heap::create_bft_iterator()
{
	return new bft_iterator(heapArr, heapSize);
}
bool Heap::bft_iterator::has_next()
{
	return (i < curSize);
}
int Heap::bft_iterator::next()
{
	if (!has_next()) throw std::out_of_range("has_next is false");
	i++;
	return current[i - 1];
}



Iterator* Heap::create_dft_iterator()
{
	return new dft_iterator(heapArr, heapSize);
}
bool Heap::dft_iterator::has_next()
{
	return (i < curSize);
}
int Heap::dft_iterator::next()
{
	if (!has_next()) throw std::out_of_range("has_next is false");
	i++;
	index = stack->return_back();
	int bonus_return = stack->return_pop_back(); // return at the beginning
	if (index * 2 + 2 < curSize)
	{
		stack->push_back(index * 2 + 2);
	}
	if (index * 2 + 1 < curSize)
	{
		stack->push_back(index * 2 + 1);
	}
	return current[bonus_return];
}