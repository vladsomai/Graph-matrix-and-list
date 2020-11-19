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
		list<shared_ptr<Node>> next;//lista cu nodurile urmatoare

	public:
		void setData(int);
		int getData();

		void setNext(shared_ptr<Node>);
		list<shared_ptr<Node>> getNext(); // functie care va returna lista nodurilor la care suntem linkuiti

		//constructor pentru Node - initializam cheia la 0
		Node()
		{

			this->next.clear();
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

		this->next.push_back(nextParam);

	}
	list<shared_ptr<Node>> Node::getNext()
	{

		return this->next;

	}

}