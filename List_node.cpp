#include "List_node.h"

namespace structure_graf
{
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

	void Node::clearNextList()
	{
		this->next.clear();
	}

	void Node::setNextList(list < shared_ptr<Node>>& ListParam)
	{
		this->next = ListParam;
	}
}