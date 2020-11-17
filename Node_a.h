#pragma once
#include<iostream>
#include<memory>
#include<list>

using namespace std;

namespace matrix_graf
{


	class Node
	{
	private:
		int data;//cheie

	public:
		void setData(int);
		int getData();

		//constructor pentru Node - initializam cheia la 0
		Node()
		{

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

}
