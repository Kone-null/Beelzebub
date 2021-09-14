#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include <string>
#include <vector>

template <typename DataType>
class List
{
	private:
		Node<DataType>* head;
		int  total_nodes = 0;
	public:
		List ();
		~List ();
		int GetSize();
		void InsertAtHead (DataType value);
		Node<DataType>* Peek ();
		void DeleteFromHead ();
};

#endif