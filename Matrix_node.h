#pragma once
#include<iostream>
#include<memory>
#include<list>
#include <queue>

namespace matrix_graf
{
	class Node
	{
	private:
		int data;

	public:
		void setData(int);
		int getData();

		Node()
		{
			this->data = 0;
		}
	};


}
