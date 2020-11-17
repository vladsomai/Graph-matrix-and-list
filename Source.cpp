#include <iostream>
#include "app10_3a.h"
#include "app10_3b.h"


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