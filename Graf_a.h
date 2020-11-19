#include"Node_a.h"

namespace matrix_graf
{

	class Graf
	{

	private:

		list <shared_ptr<Node>> NoduriGraf;//vector care v-a retine adresele fiecarui nod din graf

		static const int  MAX = 7;
		bool matrix[MAX][MAX];//matricea de adiacenta a grafului

	public:

		/*functiile grafului*/
		//------------------------------------------------------------
		//void InitGraf();graful se va initializa cu un graf vid atunci cand cream un obiect de tip "Graf", contructorul clasei "Graf" creaza o multime vida de noduri.
		bool GrafVid();
		bool GrafPlin();//aceasta functie  va verifica daca avem mai mult de MAX noduri alocate in vectorul "NoduriGraf", in cazul in care am ajuns la nr max de noduri ne oprim,
		//toate alocarile de memorie sunt facute prin alocare dinamica, la inserare nod verificam daca am putut aloca memorie pentru noul nod.



		void InsertNode();
		void SuprimNod();

		void InsertNodeParam(int);
		//functia de suprimare si inserare arc este la fel, vom diferentia suprimarea si inserarea prin parametrul de true sau false
		//true - inseram
		//false - stergem
		void InsertArc(bool);
		void InsertArcParam(bool,int,int);

		void DepthFirstSearch();
		void BreadthFirstSearch();

		void PrintMatrix();
		//------------------------------------------------------------


		void afisareNoduriGraf();


		//constructor - initializare obiect graf
		Graf()
		{

			//initializam matricea de adiacenta cu false
			for (int i = 0; i < MAX; i++)
			{

				for (int j = 0; j < MAX; j++)
				{

					matrix[i][j] = false;

				}

			}

			//cream vector fara noduri
			NoduriGraf.clear();

		}

		~Graf() = default;
	};



	//Performanta : O(n*n)
	void Graf::PrintMatrix()
	{

		cout << "   ";
		for (auto j = NoduriGraf.begin(); j != NoduriGraf.end(); ++j)
		{

			cout << "" << j->get()->getData() << "   ";//afisam pe coloana

		}

		cout << endl;

		auto actual = NoduriGraf.begin();//inceped cu primul nod din vector
		for (size_t i = 0; i < NoduriGraf.size(); i++)
		{


			cout << "" << actual->get()->getData() << ' ';//afisam numarul nodului pe linie

			actual++;//trecem la urmatorul nod din vector

			for (size_t j = 0; j < NoduriGraf.size(); j++)
			{

				cout << '(' << matrix[i][j] << ')' << ' ';//afisam matricea de adiacenta a grafului

			}

			cout << '\n';

		}

	}

	bool Graf::GrafVid()
	{

		//daca marimea vectorului NoduriGraf care retine adresele nodurilor din graf e 0 avem graf vid.
		if (NoduriGraf.empty())
		{

			cout << "Graf Vid!" << endl;
			return true;

		}
		else
		{

			return false;

		}

	}


	bool Graf::GrafPlin()
	{

		//verificam marimea vectorului
		if (NoduriGraf.size() >= MAX)
		{

			cout << "Graf Plin, nu mai putem efectua nici o operatie de insertie!" << endl;
			return true;

		}
		else
		{

			return false;

		}

	}


	//Performanta O(n)
	void Graf::InsertNode()
	{
		//verificam prima data daca avem loc de insertie
		if (GrafPlin())
		{

			return;

		}

		try
		{

			int newNumber{};
			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului

			cout << "\nIntroduceti un numar in noul nod: ";	cin >> newNumber;

			newNode->setData(newNumber);


			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//insemana ca avem deja numarul in list, deci nu putem face insertia
				if (actual->get()->getData() == newNode->getData())
				{

					numberAlreadyExists = true;
					break;

				}

			}

			if (numberAlreadyExists)
			{

				cout << "Numarul introdus exista deja in graf." << endl;
				return;

			}
			else
			{

				NoduriGraf.push_back(newNode);//introducem noul nod in lista care va retine adresele nodurilor grafului

			}

		}

		//verificam daca alocarea memoriei a avut loc(daca functia "make_shared" nu poate aloca memorie aceasta arunca un obiect de tipul "bad_alloc" -> alocarea memoriei dinamica pentru "newNode" nu mai are loc
		catch (const bad_alloc& e)
		{

			cout << "Nu am putut aloca memorie pentru un nou nod.\n" << e.what() << '\n';
			return;

		}

	}



	//Performanta O(n^2)
	void Graf::InsertArc(bool ConectionType)
	{

		if (this->GrafVid())
		{

			return;

		}

		int number1{}, number2{};
		int number1WasFound{ false };
		int number2WasFound{ false };
		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati" << endl;

		cout << "Primul numar: "; cin >> number1;
		cout << "Al doilea numar: "; cin >> number2;

		try
		{

			//cautam primul numar in graf.
			size_t i = 0, j = 0;
			for (auto actual_i = NoduriGraf.begin(); actual_i != NoduriGraf.end(); ++actual_i)
			{

				j = 0;
				if (number1 == actual_i->get()->getData())
				{

					cout << "Primul nod introdus : " << actual_i->get()->getData() << " a fost gasit in graf." << endl;
					number1WasFound = true;

					//cautam al doilea numar in graf.
					for (auto actual_j = NoduriGraf.begin(); actual_j != NoduriGraf.end(); ++actual_j)
					{

						if (number2 == actual_j->get()->getData())
						{

							cout << "Al doilea nod introdus : " << actual_j->get()->getData() << " a fost gasit in graf." << endl;
							number2WasFound = true;

							if (ConectionType)
								cout << "Vom efectua linkuirea.." << endl;
							else
								cout << "Vom efectua delinkuriea" << endl;

							cout << "i: " << i << endl;
							cout << "j: " << j << endl;

							//setam pe true / false linia si coloana cu numerele pe care dorim sa le linkuim.
							matrix[i][j] = ConectionType;
							matrix[j][i] = ConectionType;

							break;

						}

						j++;

					}

				}

				i++;

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;
			return;

		}

		if (!number1WasFound)
		{

			cout << "Numarul " << number1 << " nu exista in graf" << endl;
			return;

		}

		if (!number2WasFound)
		{

			cout << "Numarul " << number2 << " nu exista in graf" << endl;
			return;

		}

	}



	//Performanta : O(n)
	void Graf::SuprimNod()
	{
		//verificam daca putem efectua stergerea
		if (this->GrafVid())
		{

			cout << "Graf vid - stergerea nu poate avea loc" << endl;
			return;

		}

		bool numberWasDeleted{ false };
		int toDelete{};

		cout << "Introduceti numarul pe care doriti sa il stergeti: ";
		cin >> toDelete;

		try
		{

			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				if (toDelete == actual->get()->getData())
				{

					cout << "Nodul " << actual->get()->getData() << " va fi sters." << endl;
					NoduriGraf.erase(actual);//efectuam stergerea nodului

					numberWasDeleted = true;
					break;

				}

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;

		}
		if (!numberWasDeleted)
		{

			cout << "Numarul " << toDelete << " nu exista in graf" << endl;

		}

	}




	//Performanta : O(n)
	//functia de afisare noduri graf, iteram pur si simplu in vectorul care retine adresa nodurilor
	void Graf::afisareNoduriGraf()
	{
		if (this->GrafVid())
		{
			return;
		}
		else
		{

			cout << "Graful contine:\n";

			try
			{

				for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
				{

					cout << actual->get()->getData() << "\t";

				}


			}
			catch (exception e)
			{

				cout << e.what() << endl;

			}

		}

	}


	//Performanta O(n)
	void Graf::InsertNodeParam(int newNumber)
	{
		//verificam prima data daca avem loc de insertie
		if (GrafPlin())
		{

			return;

		}

		try
		{

		//	int newNumber{};
			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului

			cout << "\nIntroduceti un numar in noul nod: ";//	cin >> newNumber;

			newNode->setData(newNumber);


			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//insemana ca avem deja numarul in list, deci nu putem face insertia
				if (actual->get()->getData() == newNode->getData())
				{

					numberAlreadyExists = true;
					break;

				}

			}

			if (numberAlreadyExists)
			{

				cout << "Numarul introdus exista deja in graf." << endl;
				return;

			}
			else
			{

				NoduriGraf.push_back(newNode);//introducem noul nod in lista care va retine adresele nodurilor grafului

			}

		}

		//verificam daca alocarea memoriei a avut loc(daca functia "make_shared" nu poate aloca memorie aceasta arunca un obiect de tipul "bad_alloc" -> alocarea memoriei dinamica pentru "newNode" nu mai are loc
		catch (const bad_alloc& e)
		{

			cout << "Nu am putut aloca memorie pentru un nou nod.\n" << e.what() << '\n';
			return;

		}

	}




	//Performanta O(n^2)
	void Graf::InsertArcParam(bool ConectionType,int number1,int number2)
	{

		if (this->GrafVid())
		{

			return;

		}

		//int number1{}, number2{};
		int number1WasFound{ false };
		int number2WasFound{ false };
		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati" << endl;

		cout << "Primul numar: ";    //cin >> number1;
		cout << "Al doilea numar: "; //cin >> number2;

		try
		{

			//cautam primul numar in graf.
			size_t i = 0, j = 0;
			for (auto actual_i = NoduriGraf.begin(); actual_i != NoduriGraf.end(); ++actual_i)
			{

				j = 0;
				if (number1 == actual_i->get()->getData())
				{

					cout << "Primul nod introdus : " << actual_i->get()->getData() << " a fost gasit in graf." << endl;
					number1WasFound = true;

					//cautam al doilea numar in graf.
					for (auto actual_j = NoduriGraf.begin(); actual_j != NoduriGraf.end(); ++actual_j)
					{

						if (number2 == actual_j->get()->getData())
						{

							cout << "Al doilea nod introdus : " << actual_j->get()->getData() << " a fost gasit in graf." << endl;
							number2WasFound = true;

							if (ConectionType)
								cout << "Vom efectua linkuirea.." << endl;
							else
								cout << "Vom efectua delinkuriea" << endl;

							cout << "i: " << i << endl;
							cout << "j: " << j << endl;

							//setam pe true / false linia si coloana cu numerele pe care dorim sa le linkuim.
							matrix[i][j] = ConectionType;
							matrix[j][i] = ConectionType;

							break;

						}

						j++;

					}

				}

				i++;

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;
			return;

		}

		if (!number1WasFound)
		{

			cout << "Numarul " << number1 << " nu exista in graf" << endl;
			return;

		}

		if (!number2WasFound)
		{

			cout << "Numarul " << number2 << " nu exista in graf" << endl;
			return;

		}

	}


	void matrix_graf::Graf::DepthFirstSearch()
	{
		cout << "\n=======Cautare prin adancime=======" << endl;




	}

	/*
	functia de cautare prin cuprindere va fi implementata folosind o structura de date de tipul queue
	incepem intotdeauna de la primul nod din lista de noduri ale grafului(NoduriGraf)
	folosim variabila "actual" pentru a itera in graf
	*/
	void matrix_graf::Graf::BreadthFirstSearch()
	{

		cout << "\n=======Cautare prin cuprindere=======" << endl;

	}


}
