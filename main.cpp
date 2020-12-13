#include <iostream>
#include "app10_matrix.h"
#include "app10_structure.h"

/*
Implementam toate problemele propuse in tema de la punctele 10.1 , 10.2, 10.3 si 10.4 in aceeasi solutie pentru a avea toate uneltele disponibile in acelasi program


Vom crea un graf pentru matrix graf si unul pentru structure graf.
Graful v-a fi predefinit la rulare astfel economisind timp pentru verificari si schimbari.

Afisarea structurii si matricei grafului se poate face din meniul fiecarui graf

*/

//declaram functiile de meniu - creare graf bazat pe matrice de adiacenta si graf bazat pe structuri de liste
void menu(shared_ptr<matrix_graf::Graf>, shared_ptr<structure_graf::Graf>);
shared_ptr<matrix_graf::Graf> CreateMatrixGraf();
shared_ptr<structure_graf::Graf> CreateStructureGraf();


int main()
{

	menu(CreateMatrixGraf(), CreateStructureGraf());

}

//functia de meniu principal care va dirija programul, de aici putem sa trecem in oricare reprezentare dorim
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

	} while (optiune != 0);

}


//functie care va crea un graf bazat pe matrice de adiacenta si il va definii cu noduri
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


//functie care va crea un graf bazat pe structuri de liste si il va definii cu noduri
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

