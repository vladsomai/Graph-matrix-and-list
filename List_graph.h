#pragma once
#include"List_node.h"
#include <queue>

namespace structure_graf
{
	using std::queue;
	using std::shared_ptr;
	using std::make_shared;
	using std::cout;
	using std::cin;
	using std::endl;

	class Graf
	{
	private:
		list<shared_ptr<Node>> NoduriGraf;
		queue< shared_ptr<Node> > que{};
		list < shared_ptr<Node> >NodesSearchedInGraf{};

	public:
		//------------------------------------------------------------
		bool GrafVid();

		void InsertNode();
		void SuprimNod();
		void InsertNodeParam(int);

		void InsertArc(bool);
		void InsertArcParam(bool, int, int);

		void DepthFirstSearch(shared_ptr<Node>&);
		void BreadthFirstSearch(shared_ptr<Node>&);

		bool NodeExistsInQueue(shared_ptr<Node>&);
		bool NodeExistsInNodesSearchedInGraf(shared_ptr<Node>&);
		bool NodeExistsInList(shared_ptr<Node>&, list < shared_ptr<Node>>&);

		void PrintStructure();
		void afisareNoduriGraf();
		void PrintNodesSearchedInGraf();

		size_t sizeof_NoduriGraf() { return NoduriGraf.size(); }

		void clearSearchedList() { NodesSearchedInGraf.clear(); }
		auto getFirstNode() { return this->NoduriGraf.begin(); }
		//------------------------------------------------------------

		Graf()
		{
			NoduriGraf.clear();
			NodesSearchedInGraf.clear();
		}
		~Graf() = default;
	};

	
}

