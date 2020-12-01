#include "pch.h"
#include "CppUnitTest.h"
#include "../binaryheap/Heap.h"
#include "../binaryheap/Heap.cpp"
#include "../binaryheap/LinkedList.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sortTest
{
	TEST_CLASS(sortTest)
	{
	public:
		Heap TestHeap;
		Iterator* TestIterator;
		/////////////////////////////////////////////////// insert
		TEST_METHOD(insert_first)
		{
			TestHeap.insert(10); // 10
			TestIterator = TestHeap.create_bft_iterator();
			Assert::AreEqual(TestIterator->next(), 10);
		}
		TEST_METHOD(insert_6elem)
		{
			TestHeap.insert(2); // 0
			TestHeap.insert(3); // 2 1
			TestHeap.insert(4); // 8 3 4
			TestHeap.insert(8);
			TestHeap.insert(1);
			TestHeap.insert(0);
			TestIterator = TestHeap.create_bft_iterator();
			Assert::AreEqual(TestIterator->next(), 0);
			Assert::AreEqual(TestIterator->next(), 2);
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 8);
			Assert::AreEqual(TestIterator->next(), 3);
			Assert::AreEqual(TestIterator->next(), 4);
		}
		TEST_METHOD(insert_1111)
		{
			TestHeap.insert(1); // 1
			TestHeap.insert(1); // 1 1
			TestHeap.insert(1); // 1
			TestHeap.insert(1);
			TestIterator = TestHeap.create_bft_iterator();
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 1);
		}
		/////////////////////////////////////////////////// bonus depth
		TEST_METHOD(found_depth)
		{
			// 0 // 0
			// 1 // 1 2
			// 2 // 3 4 5 6
			// 3 // 7 8 9 10 11 12 13 14
			// 4 // 15 16..
			Assert::AreEqual(TestHeap.depth(14), 3);
		}
		/////////////////////////////////////////////////// contains
		TEST_METHOD(contains_true)
		{
			TestHeap.insert(9); // 0
			TestHeap.insert(3); // 0 2
			TestHeap.insert(0); // 9 1 3
			TestHeap.insert(1);
			TestHeap.insert(0);
			TestHeap.insert(2);
			Assert::AreEqual(TestHeap.contains(1), true);
		}
		TEST_METHOD(contains_false)
		{
			TestHeap.insert(9); // 0
			TestHeap.insert(3); // 0 2
			TestHeap.insert(0); // 9 1 3
			TestHeap.insert(1);
			TestHeap.insert(0);
			TestHeap.insert(2);
			Assert::AreEqual(TestHeap.contains(404), false);
		}
		/////////////////////////////////////////////////// remove
		TEST_METHOD(remove)
		{
			TestHeap.insert(2); // (0)
			TestHeap.insert(3); // 2 1
			TestHeap.insert(4); // (8) 3 (4)
			TestHeap.insert(8);
			TestHeap.insert(1);
			TestHeap.insert(0);

			TestHeap.remove(0); // 1
			TestHeap.remove(8); // 2 3
			TestHeap.remove(4);
			TestIterator = TestHeap.create_bft_iterator();
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 2);
			Assert::AreEqual(TestIterator->next(), 3);
		}
		TEST_METHOD(remove_error)
		{
			TestHeap.insert(1);
			try
			{
				TestHeap.remove(33);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("not found", error.what());
			}
		}
		/////////////////////////////////////////////////// dft iterator
		TEST_METHOD(dft_iterator)
		{
			TestHeap.insert(2); // 0
			TestHeap.insert(3); // 2 1
			TestHeap.insert(4); // 8 3 4
			TestHeap.insert(8);
			TestHeap.insert(1);
			TestHeap.insert(0);
			TestIterator = TestHeap.create_dft_iterator();
			Assert::AreEqual(TestIterator->next(), 0);
			Assert::AreEqual(TestIterator->next(), 2);
			Assert::AreEqual(TestIterator->next(), 8);
			Assert::AreEqual(TestIterator->next(), 3);
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 4);
		}
		TEST_METHOD(dft_iterator_error)
		{
			TestHeap.insert(2);
			TestIterator = TestHeap.create_dft_iterator();
			try
			{
				TestIterator->next();
				TestIterator->next();
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("has_next is false", error.what());
			}
		}
		/////////////////////////////////////////////////// bft iterator
		TEST_METHOD(bft_iterator)
		{
			TestHeap.insert(2); // 0
			TestHeap.insert(3); // 2 1
			TestHeap.insert(4); // 8 3 4
			TestHeap.insert(8);
			TestHeap.insert(1);
			TestHeap.insert(0);
			TestIterator = TestHeap.create_bft_iterator();
			Assert::AreEqual(TestIterator->next(), 0);
			Assert::AreEqual(TestIterator->next(), 2);
			Assert::AreEqual(TestIterator->next(), 1);
			Assert::AreEqual(TestIterator->next(), 8);
			Assert::AreEqual(TestIterator->next(), 3);
			Assert::AreEqual(TestIterator->next(), 4);
		}
		TEST_METHOD(bft_iterator_error)
		{
			TestHeap.insert(2);
			TestIterator = TestHeap.create_bft_iterator();
			try
			{
				TestIterator->next();
				TestIterator->next();
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("has_next is false", error.what());
			}
		}
	};
}