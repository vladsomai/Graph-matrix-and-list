#include <iostream>
#include "Graf_b.h"


/*
Aplicaţia 10.3
Se cere să se redacteze un program care realizează următoarele activităţi:
 (1) Acceptă la intrare un graf precizat prin mulţimea nodurilor şi arcelor sale;
 (2) Vizualizează graful afişând lista nodurilor şi lista arcelor sale
 (3) Listează nodurile în ordinea parcurgerii lor pe baza căutării în adâncime;
Programul se va realiza în două variante:
a) Graf reprezentat prin matrice de adiacenţe;
b) Graf reprezentat prin structuri de adiacenţe.
Se vor utiliza reprezentările şi operatorii de la problemele 10.1 respectv 10.2

*/

namespace structure_graf
{


	void menu(shared_ptr<Graf>);


	void StructureGraf_main(shared_ptr<Graf> structure_graf)
	{

		menu(structure_graf);

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


			cout << "6.Afisare noduri graf.\n";
			cout << "7.Afisare structura.\n";

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
				graf->afisareNoduriGraf();
				cout << endl;
				break;
			case 7:
				graf->PrintStructure();
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