#include <iostream>
#include "Graf_b.h"


namespace structure_graf
{
	//declaram functia de meniu
	void menu(shared_ptr<Graf>);

	//functie principala care va chema meniul
	void StructureGraf_main(shared_ptr<Graf> structure_graf)
	{

		menu(structure_graf);

	}

	//definim functia meniu al grafului bazat pe structuri de liste
	void menu(shared_ptr<Graf> graf)
	{

		bool grafVid{};
		int optiune = 0;
		auto it = graf->getFirstNode();

		do
		{

			system("cls");
			cout << "\n\n======MENU======\n";

			cout << "1.Inserare nod.\n";
			cout << "2.Inserare arc.\n";

			cout << "3.Suprima nod\n";
			cout << "4.Suprima arc.\n";

			cout << "5.Graf vid.\n";


			cout << "6.Afisare noduri graf.\n";
			cout << "7.Afisare structura.\n";

			cout << "8.Cautare prin adancime - DFS.\n";
			cout << "9.Cautare prin cuprindere - BFS.\n";


			cout << "0.Exit.\n";

			cout << "Optiunea dvs. : ";
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
				grafVid = graf->GrafVid();
				if (grafVid) cout << "True"; else cout << "False";
				cout << endl;
				break;
			case 6:
				graf->afisareNoduriGraf();
				cout << endl;
				break;
			case 7:
				graf->PrintStructure();
				cout << endl;
				break;
			case 8:
				cout << "\n=======Cautare prin adancime=======" << endl;
				graf->clearSearchedList();
				advance(it, 3);//setam al catelea element din lista sa fie luat ca si parametru
			    graf->DepthFirstSearch(*it);
				graf->PrintNodesSearchedInGraf();
				cout << endl;
				it = graf->getFirstNode();//resetam iteratorul la primul nod dupa ce am terminat executia
				break;
			case 9:
				cout << "\n=======Cautare prin cuprindere=======" << endl;
				graf->clearSearchedList();
				graf->BreadthFirstSearch();
				cout << endl;
				break;

			default:
				cout << "Optiune gresita...\n";
				cout << endl;
				break;
			};

			system("pause");

		} while (optiune != 0);

	}

}