#include <iostream>
#include "Graf_a.h"


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

			cout << "9. Cautare prin adancime - DFS.\n";
     		cout << "10.Cautare prin cuprindere - BFS.\n";

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
			case 9:
				graf->DepthFirstSearch();
				cout << endl;
				break;
			case 10:
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