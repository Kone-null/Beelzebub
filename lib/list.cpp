#include "list.hpp"



template <typename DataType>
List<DataType>::List ()
{
	this->head = nullptr;
}

template <typename DataType>
void List<DataType>::InsertAtHead (DataType value)
{
	Node<DataType>* n = new Node<DataType>(value, this->head);
	this->head = n;

	this->total_nodes++;
}

template <typename DataType>
Node<DataType>* List<DataType>::Peek ()
{
	return this->head;
}

template <typename DataType>
void List<DataType>::DeleteFromHead ()
{
	if (this->head == nullptr)
	{
		return;
	}

	Node<DataType>* garbage = this->head;

	this->head = this->head->GetNext();

	delete garbage;
	this->total_nodes--;
}

template <typename DataType>
List<DataType>::~List ()
{
	while (this->head != nullptr)
	{
		this->DeleteFromHead();
	}
}

template <typename DataType>
int List<DataType>::GetSize()
{

	return this->total_nodes;
}



template class List<int>;

template class List<char>;

template class List<char*>;


template class List<std::string>;

template class List<std::vector<unsigned char>>;
