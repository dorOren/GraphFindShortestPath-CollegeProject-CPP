//A template file for implementing a Queue.
#pragma once
#include <iostream>

using namespace std;

namespace GraphTheory
{
	template <class T>
	class Queue
	{
		T* arr;         // array to store queue elements
		int capacity;   // maximum capacity of the queue
		int front;      // front points to the front element in the queue (if any)
		int rear;       // rear points to the last element in the queue
		int count;      // current size of the queue

	public:
		Queue(int i_Size);			 // constructor - input: size, output: Queue in the size given
		~Queue() { delete arr; }		 // distructor


		T Dequeue();				 // no input, output: oldest element in the queue
		void Enqueue(T t);			 // input: element, output: queue with the new element
		T Peek();					 // no input, output: oldest element in queue
		int Size();					 // no input, output: size of queue
		bool IsEmpty();				 // no input, output: true if queue is empty, false otherwise
		bool IsFull();				 // no input, output: true if queue reached full capacity, false otherwise
	};

	// Constructor to initialize a queue
	template <class T>
	Queue<T>::Queue(int i_Size)
	{
		arr = new T[i_Size];
		capacity = i_Size;
		front = 0;
		rear = -1;
		count = 0;
	}

	// Utility function to dequeue the front element
	template <class T>
	T Queue<T>::Dequeue()
	{
		// check for queue underflow
		if (IsEmpty())
		{
			cout << "CANT DEQUEUE IF QUEUE IS EMPTY";
			exit(1);
		}
		T temp = arr[front];
		front = (front + 1) % capacity;
		count--;
		return temp;
	}

	// Utility function to add an item to the queue
	template <class T>
	void Queue<T>::Enqueue(T i_Item)
	{
		// check for queue overflow
		if (IsFull())
		{
			cout << "CANT ENQUEUE IF QUEUE IS FULL";
			exit(1);
		}

		rear = (rear + 1) % capacity;
		arr[rear] = i_Item;
		count++;
	}

	// Utility function to return the front element of the queue
	template <class T>
	T Queue<T>::Peek()
	{
		if (!IsEmpty())
		{
			cout << "CANT PEEK IF QUEUE IS EMPTY";
			exit(1);
		}
		return arr[front];
	}

	// Utility function to return the size of the queue
	template <class T>
	int Queue<T>::Size() {
		return count;
	}

	// Utility function to check if the queue is empty or not
	template <class T>
	bool Queue<T>::IsEmpty() {
		return (count == 0);
	}

	// Utility function to check if the queue is full or not
	template <class T>
	bool Queue<T>::IsFull() {
		return (count == capacity);
	}
}

