// A template file for implementing a linked list
#pragma once
#include <iostream>

using namespace std;
namespace GraphTheory
{
	template <class T>
	struct node
	{
		T data;
		struct node* next;
	};

	template <class T>
	class LinkedList
	{
	private:
		node<T>* head;

	public:
		LinkedList() { head = nullptr; }				// constructor - no input, output: empty list
		~LinkedList();									// distructor

		int IsEmpty();									// no input, output: true if list is empty, false otherwise
		node<T>* GetListHead();							// no input, output: head of the list
		node<T>* CreateListItem(T i_Data);				// input: data, output: node with the data
		void InsertAfter(node<T>* i_Item, T i_Data);	// input: father node and data, output: list including new node after the father node
		void RemoveAfter(node<T>* i_Item);				// input: node, output: list without the node next to the input node
		void RemoveNode(T i_Data);						// input: data, output: remove the node that contains the data
		void DeleteList();								// no input, delete list
		bool IsItemExist(T i_Data);						// input: data, output: true if there is a node containing the date, false otherwise
		void PrintList();								// no input, output: printed list on screen
	};

	// Distructor
	template <class T>
	LinkedList<T>::~LinkedList()
	{
		DeleteList();
	}

	// Utility function to create a new node for the List
	template <class T>
	node<T>* LinkedList<T>::CreateListItem(T i_Data)
	{
		node<T>* result = new node<T>();
		result->data = i_Data;
		result->next = nullptr;
		return result;
	}

	// Utility function to return the Linked List
	template <class T>
	node<T>* LinkedList<T>::GetListHead()
	{
		return head;
	}

	// Utility function to check if the List is empty or not
	template <class T>
	int LinkedList<T>::IsEmpty()
	{
		return (head == nullptr);
	}

	// Utility function to add a node to the List
	template <class T>
	void LinkedList<T>::InsertAfter(node<T>* i_PrevItem, T i_Data)
	{
		// insert a new node with data i_Data after the node i_PrevItem
		// if i_PrevItem is nullptr, insert a new head
		if (i_PrevItem != nullptr)
		{
			node<T>* newItem = CreateListItem(i_Data);
			newItem->next = i_PrevItem->next;
			i_PrevItem->next = newItem;
		}
		else
		{
			node<T>* newItem = CreateListItem(i_Data);
			newItem->next = head;
			head = newItem;
		}
	}

	// Utility function to remove a node from the List
	template <class T>
	void LinkedList<T>::RemoveAfter(node<T>* i_PrevItem)
	{
		// remove the node after the node i_PrevItem
		// if i_PrevItem is nullptr, remove the head
		if (i_PrevItem != nullptr)
		{
			node<T>* toDelete = i_PrevItem->next;
			i_PrevItem->next = toDelete->next;
			delete toDelete;
		}
		else
		{
			node<T>* toDelete = head;
			head = toDelete->next;
			delete toDelete;
		}
	}

	// Utility function to remove a node from the List
	template <class T>
	void LinkedList<T>::RemoveNode(T i_Data)
	{
		if (head->data == i_Data)
			RemoveAfter(nullptr);
		else
		{
			node<T>* newNode = head;
			while (newNode->next != nullptr)
			{
				if (newNode->next->data == i_Data)
				{
					RemoveAfter(newNode);
					break;
				}

				newNode = newNode->next;
			}
		}
	}

	// Utility function to delete the entire List
	template <class T>
	void LinkedList<T>::DeleteList()
	{
		if (!IsEmpty())
		{
			node<T>* currentNode = head;
			while (currentNode->next != nullptr)
			{
				RemoveAfter(currentNode);
			}
			RemoveAfter(nullptr);  // delete head
		}
	}

	// Utility function to find an element within the list
	template <class T>
	bool LinkedList<T>::IsItemExist(T i_Data)
	{
		if (!IsEmpty())
		{
			node<T>* newItem = head;
			while (newItem != nullptr)
			{
				if (newItem->data == i_Data)
					return true;

				newItem = newItem->next;
			}
		}
		return false;
	}

	// Utility function to print the List
	template <class T>
	void LinkedList<T>::PrintList()
	{
		if (!IsEmpty())
		{
			node<T>* currentNode = head;
			while (currentNode != nullptr)
			{
				cout << currentNode->data << ", ";
				currentNode = currentNode->next;
			}
		}
	}

}