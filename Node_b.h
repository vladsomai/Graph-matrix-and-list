#pragma once
#include<iostream>
#include<memory>
#include<list>

using namespace std;

namespace structure_graf
{

	class Node
	{
	private:
		int data;//cheie
		shared_ptr<Node> next;//nodul urmator

	public:
		void setData(int);
		int getData();

		void setNext(shared_ptr<Node>);
		shared_ptr<Node> getNext();

		//constructor pentru Node - initializam cheia la 0
		Node()
		{

			this->next = nullptr;
			this->data = 0;

		}


	};

	int Node::getData()
	{

		return this->data;

	}

	void Node::setData(int newData)
	{

		this->data = newData;

	}


	void Node::setNext(shared_ptr<Node> nextParam)
	{

		this->next = nextParam;

	}
	shared_ptr<Node> Node::getNext()
	{

		return this->next;

	}

}