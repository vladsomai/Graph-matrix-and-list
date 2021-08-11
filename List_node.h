#pragma once
#include<iostream>
#include<memory>
#include<list>

namespace structure_graf
{
	using std::list;
	using std::shared_ptr;
	class Node
	{
	private:
		int data;
		list<shared_ptr<Node>> next;

	public:
		void setData(int);
		int getData();

		void setNext(shared_ptr<Node>);
		list<shared_ptr<Node>> getNext();

		void clearNextList();
		void setNextList(list < shared_ptr<Node>>&);
		Node()
		{
			this->next.clear();
			this->data = 0;
		}
	};
}