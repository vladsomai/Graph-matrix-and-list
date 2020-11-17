#include <iostream>
#include "app10_3a.h"
#include "app10_3b.h"

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



Folosindu-ne de implementarea de la punctele 1 si 2 vom crea 1 graf pentru matrix graf si unul pentru structure graf
graful v-a fi predefinit la rulare astfel economisind timp pentru verificari si schimbari.

Afisarea structurii si matricei grafului se poate face din meniul fiecarui graf

Facem implementarea cautarii prin adancime si cuprindere in aceeasi solutie.


*/

void menu(shared_ptr<matrix_graf::Graf> , shared_ptr<structure_graf::Graf>);
shared_ptr<matrix_graf::Graf> CreateMatrixGraf();
shared_ptr<structure_graf::Graf> CreateStructureGraf();


int main()
{

	menu(CreateMatrixGraf(), CreateStructureGraf());

}



void menu( shared_ptr<matrix_graf::Graf> matrixGraf, shared_ptr<structure_graf::Graf> structureGraf)
{

	int optiune = 0;


	do
	{
		system("cls");
		cout << "\n\n======MENU======\n";

		cout << "1.Matrix Graf.\n";
		cout << "2.Structure Graf.\n";

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
			matrix_graf::MatrixGraf_main(matrixGraf);
			cout << endl;
			break;
		case 2:
			structure_graf::StructureGraf_main(structureGraf);
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

shared_ptr<matrix_graf::Graf> CreateMatrixGraf()
{

	shared_ptr<matrix_graf::Graf> matrix_grafExample = make_shared<matrix_graf::Graf>();
	matrix_grafExample->InsertNodeParam(2);
	matrix_grafExample->InsertNodeParam(5);
	matrix_grafExample->InsertNodeParam(6);
	matrix_grafExample->InsertNodeParam(7);
	matrix_grafExample->InsertNodeParam(9);
	matrix_grafExample->InsertNodeParam(10);
	matrix_grafExample->InsertNodeParam(13);
	matrix_grafExample->InsertArcParam(true, 2, 10);
	matrix_grafExample->InsertArcParam(true, 2, 5);
	matrix_grafExample->InsertArcParam(true, 2, 9);
	matrix_grafExample->InsertArcParam(true, 5, 6);
	matrix_grafExample->InsertArcParam(true, 10, 9);
	matrix_grafExample->InsertArcParam(true, 9, 6);
	matrix_grafExample->InsertArcParam(true, 9, 13);
	matrix_grafExample->InsertArcParam(true, 6, 7);
	matrix_grafExample->InsertArcParam(true, 6, 13);
	matrix_grafExample->InsertArcParam(true, 7, 13);

	return matrix_grafExample;

}

shared_ptr<structure_graf::Graf> CreateStructureGraf()
{

	shared_ptr<structure_graf::Graf> structure_grafExample = make_shared<structure_graf::Graf>();
	structure_grafExample->InsertNodeParam(2);
	structure_grafExample->InsertNodeParam(5);
	structure_grafExample->InsertNodeParam(6);
	structure_grafExample->InsertNodeParam(7);
	structure_grafExample->InsertNodeParam(9);
	structure_grafExample->InsertNodeParam(10);
	structure_grafExample->InsertNodeParam(13);
	structure_grafExample->InsertArcParam(true, 2, 10);
	structure_grafExample->InsertArcParam(true, 2, 5);
	structure_grafExample->InsertArcParam(true, 2, 9);
	structure_grafExample->InsertArcParam(true, 5, 6);
	structure_grafExample->InsertArcParam(true, 10, 9);
	structure_grafExample->InsertArcParam(true, 9, 6);
	structure_grafExample->InsertArcParam(true, 9, 13);
	structure_grafExample->InsertArcParam(true, 6, 7);
	structure_grafExample->InsertArcParam(true, 6, 13);
	structure_grafExample->InsertArcParam(true, 7, 13);

	return structure_grafExample;

}