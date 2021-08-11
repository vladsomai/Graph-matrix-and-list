#include <iostream>
#include "Matrix_main.h"

namespace matrix_graf
{
	using std::shared_ptr;

	void MatrixGraf_main(shared_ptr<Graf> matrix_graf)
	{
		menu(matrix_graf);
	}
	
	void menu(shared_ptr<Graf> graf)
	{
		int optiune = 0;
		size_t dfsOption{};
		size_t bfsOption{};
		bool grafVid{};
		auto it = graf->getFirstNode();

		do
		{
			system("cls");
			cout << "\n\n======MENU======\n";

			cout << "1.Insert node.\n";
			cout << "2.Insert arch.\n";

			cout << "3.Delete node.\n";
			cout << "4.Delete arch.\n";

			cout << "5.Is empty.\n";
			cout << "6.Is full.\n";

			cout << "7.Print graph nodes.\n";
			cout << "8.Print adjiancy Matrix.\n";

			cout << "9. Depth first search - DFS.\n";
     		cout << "10.Breadth first search - BFS.\n";

			cout << "0.Exit.\n";

			cout << "Your option: ";
			cin >> optiune;

			cout << "\n\n======OUTPUT======" << endl;
			switch (optiune)
			{
			case 0:
				cout << "\n\nExiting..." << endl;
				break;

			case 1:
				graf->InsertNode();
				cout << endl;
				break;

			case 2:
				graf->InsertArc(true);
				cout << endl;
				break;

			case 3:
				graf->SuprimNod();
				cout << endl;
				break;

			case 4:
				graf->InsertArc(false);
				cout << endl;
				break;

			case 5:
				if (graf->GrafVid()) cout << "True"; else cout << "False";
				cout << endl;
				break;

			case 6:
				graf->GrafPlin();
				cout << endl;
				break;

			case 7:
				graf->afisareNoduriGraf();
				cout << endl;
				break;

			case 8:
				graf->PrintMatrix();
				cout << endl;
				break;

			case 9:
				cout << "\n=======Depth first search=======" << endl;

				cout << "Enter the node index from which to start: "; cin >> dfsOption;
				if(dfsOption >= graf->sizeof_NoduriGraf())
				{
					cout << "The entered node is larger than the size of the graph" << endl;
					break;
				}

				graf->clearSearchedList();
				it = graf->getFirstNode();
				std::advance(it, dfsOption);
				graf->DepthFirstSearch(*it);//start the search from the specified node
				cout << endl;
				graf->PrintNodesSearchedInGraf();
				it = graf->getFirstNode();
				cout << endl;
				break;

			case 10:
				cout << "\n=======Breadth first search=======" << endl;

				cout << "Enter the node index from which to start: "; cin >> bfsOption;
				if (bfsOption >= graf->sizeof_NoduriGraf())
				{
					cout << "The entered node is larger than the size of the graph" << endl;
					break;
				}

				it = graf->getFirstNode();
				std::advance(it, bfsOption);
				graf->BreadthFirstSearch(*it);
				cout << endl;
				break;

			default:
				cout << "Wrong option...\n";
				cout << endl;
				break;
			};

			system("pause");
		} while (optiune != 0);

	}

}