#include <iostream>
#include "Graf_a.h"


/*
Aplicaţia 10.1
Se cere să se implementeze TDA graf (Varianta 1, Shiflet) utilizând matrici de adiacenţe.
Se vor implementa următorii operatori: InitGraf, GrafVid, GrafPlin, InserNod,
InserArc, SuprimNod, SuprimArc. Tabloul nodurilor se consideră neordonat. Se cere
să se precizeze performanţele operatorilor implementaţi în termenii funcţiei O.

=========================================================================================


Vom defini o structura de date "Node" care va reprezenta nodurile grafului

La inserarea fiecarui arc(link) vom cauta cele 2 noduri din graf dupa care le vom linkui unul cu celalalt(nod a-> nod b && nod b->nod a).

Vom afisa matricea de adiacenta la sfarsitul introducerii datelor.



Complexitatea acestui algorithm este O(n^2) deoarece avem o matrice de MxM
*/


namespace matrix_graf
{

	void menu(shared_ptr<Graf>);


	void MatrixGraf_main(shared_ptr<Graf> matrix_graf)
	{

		menu(matrix_graf);

	}





	void menu(shared_ptr<Graf> graf)
	{

		int optiune = 0;


		do
		{
			system("cls");
			cout << "\n\n======MENU======\n";

			cout << "1.Inserare nod.\n";
			cout << "2.Inserare arc.\n";

			cout << "3.Suprima nod\n";
			cout << "4.Suprima arc.\n";

			cout << "5.Graf vid.\n";
			cout << "6.Graf plin.\n";

			cout << "7.Afisare graf.\n";
			cout << "8.Afisare matrice.\n";

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
				graf->GrafVid();
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

			default:
				cout << "Optiune gresita...\n";
				cout << endl;
				break;
			};

			system("pause");
		} while (optiune != 0);

	}

}