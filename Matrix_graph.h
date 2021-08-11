#pragma once
#include"Matrix_node.h"

namespace matrix_graf
{
	using std::list;
	using std::queue;
	using std::shared_ptr;
	using std::make_shared;
	using std::cout;
	using std::cin;
	using std::endl;

	class Graf
	{

	private:
		list <shared_ptr<Node>> NoduriGraf;
		list < shared_ptr<Node> >NodesSearchedInGraf{};
		queue< shared_ptr<Node> > que{};

		static const int  MAX = 7;
		bool matrix[MAX][MAX]= {};

	public:
		
		//------------------------------------------------------------
		bool GrafVid();
		bool GrafPlin();

		void InsertNode();
		void InsertNodeParam(int);

		void SuprimNod();

		void InsertArc(bool);
		void InsertArcParam(bool,int,int);

		void DepthFirstSearch(shared_ptr<Node>& );
		void BreadthFirstSearch(shared_ptr<Node>& );

		void PrintNodesSearchedInGraf();
		bool NodeExistsInList(shared_ptr<Node>&, list<shared_ptr<Node>>&);

		void PrintMatrix();
		void afisareNoduriGraf();

		void clearSearchedList() { NodesSearchedInGraf.clear(); }
		auto getFirstNode() { return this->NoduriGraf.begin(); }

		size_t sizeof_NoduriGraf() { return NoduriGraf.size(); };

		list<shared_ptr<Node>> searchForArc(shared_ptr<Node>&, int);
		int nodePosition(shared_ptr<Node>&, list<shared_ptr<Node>>&);

		bool NodeExistsInQueue(shared_ptr<Node>&);
		bool NodeExistsInNodesSearchedInGraf(shared_ptr<Node>&);
		//------------------------------------------------------------

		Graf()
		{
			NoduriGraf.clear();
		}
		~Graf() = default;
	};
}
