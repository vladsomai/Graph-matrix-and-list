#include"Node_matrix.h"

namespace matrix_graf
{

	class Graf
	{

	private:
		list <shared_ptr<Node>> NoduriGraf;//vector care v-a retine adresele fiecarui nod din graf.
		list < shared_ptr<Node> >NodesSearchedInGraf{};//lista in care vom insera nodurile parcurse de BFS & DFS, dupa care o vom afisa in ordinea in care au fost inserate nodurile.
		queue< shared_ptr<Node> > que{};//queue(coada) pentru implementarea functiei de cautare prin cuprindere.

		static const int  MAX = 7;
		bool matrix[MAX][MAX];//matricea de adiacenta a grafului, se poate modifica variabila MAX pentru alte marimi ale grafului

	public:
		/*functiile grafului*/
		//------------------------------------------------------------
		bool GrafVid();
		bool GrafPlin();//aceasta functie  va verifica daca avem mai mult de MAX noduri alocate in vectorul "NoduriGraf", in cazul in care am ajuns la nr max de noduri ne oprim,

		void InsertNode();
		void InsertNodeParam(int);
		void SuprimNod();

		//functia de suprimare si inserare arc este la fel, vom diferentia suprimarea si inserarea prin parametrul de true sau false
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



		//constructor - initializare obiect graf
		Graf()
		{

			//initializam matricea de adiacenta cu false la crearea gafului
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

	
	//functie de afisare a unei liste parametru
	void print_list(list<shared_ptr<Node>>& li)
	{


		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			cout << iterator->get()->getData() << "->";

		}

		cout << endl;

	}


	//functie de afisare a unei liste parametru cu adresele fiecarui nod din componenta listei
	void print_list_verbose(list<shared_ptr<Node>>& li)
	{


		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			cout << iterator->get()->getData()
				<< " (" << *iterator << ") "
				<< "->";

		}

		cout << endl;

	}


	//functia de verificare daca un nod exista in coada
	bool matrix_graf::Graf::NodeExistsInQueue(shared_ptr<Node>& actual)
	{
		queue<shared_ptr<Node>> tempqueue = this->que;

		while (!tempqueue.empty())
		{

			if (tempqueue.front()->getData() == actual->getData())
			{

				return true;

			}

			tempqueue.pop();
		}

		return false;

	}


	//verificam daca un nod exista in lista rezultata din cautarea nodurilor 
	bool  matrix_graf::Graf::NodeExistsInNodesSearchedInGraf(shared_ptr<Node>& actual)
	{

		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{

			if (iterator->get()->getData() == actual->getData())
			{

				return true;

			}

		}

		return false;

	}


	//functie de afisare a matricei de adiacenta
	void Graf::PrintMatrix()
	{

		cout << "    ";
		for (auto j = NoduriGraf.begin(); j != NoduriGraf.end(); ++j)
		{

			//folosim acest if pentru a identa coloanele corect(fara deviatie) la afisarea matricei
			if (j->get()->getData() > 8)
			{

				cout << "" << j->get()->getData() << "  ";//afisam numerele de pe coloane

			}
			else
			{

				cout << "" << j->get()->getData() << "   ";//afisam numerele de pe coloane
			
			}

		}

		cout << endl;

		auto actual = NoduriGraf.begin();//inceped cu primul nod din vector
		for (size_t i = 0; i < NoduriGraf.size(); i++)
		{

			if (actual->get()->getData() < 10) cout << " ";
			cout << "" << actual->get()->getData() << ' ';//afisam numerele de pe linie

			actual++;//trecem la urmatorul nod din vector

			for (size_t j = 0; j < NoduriGraf.size(); j++)
			{

				cout << '(' << matrix[i][j] << ')' << ' ';//afisam matricea de adiacenta a grafului

			}

			cout << '\n';

		}

	}


	//functie verificare graf vid
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

		//verificam marimea vectorului, daca este mai mare decat numarul maxim de noduri ale matricei returnam true
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


	//functie de inserare un nod in graf
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
			//daca nu putem aloca memorie - functia make_share va arunca un obiect de tipul bad_alloc pe care il tratam in blocul catch

			cout << "\nIntroduceti un numar in noul nod: ";	cin >> newNumber;

			newNode->setData(newNumber);


			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf, iteram in lista de noduri din graf
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca numarul la care am ajuns este egal cu noul numar introdus, insemana ca avem deja numarul in list, deci nu putem face insertia
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


	//functia de inserare arc - va avea ca si parametru true sau false si in functie de acest parametru vom adauga link sau vom sterge link
	void Graf::InsertArc(bool ConectionType)
	{
		 
		//verificam pentru graf gol
		if (this->GrafVid())
		{

			return;

		}

		int number1{}, number2{};
		
		//variabile folosite pentru a inregistra daca am gasit numerele la care dorim sa adaugam un arc
		int number1WasFound{ false };
		int number2WasFound{ false };

		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati" << endl;
		cout << "Primul numar: "; cin >> number1;
		cout << "Al doilea numar: "; cin >> number2;

	
		//cautam primul numar in graf pe linie.
		size_t i = 0, j = 0;//index-urile folosite pentru introducerea linkului in matrice

		//iteram in lista de nodrui pana ajungem la nodul la care dorim sa stergem / adaugam un arc
		//cautam primul numar pe linie
		for (auto actual_i = NoduriGraf.begin(); actual_i != NoduriGraf.end(); ++actual_i)
		{

			j = 0;//resetam indexul j al coloanei de fiecare data cand ajungem la o noua linie

			if (number1 == actual_i->get()->getData())
			{

				cout << "Primul nod introdus : " << actual_i->get()->getData() << " a fost gasit in graf." << endl;
				number1WasFound = true;

				//cautam al doilea numar in graf pe coloana.
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

						//setam pe true / false linia si coloana cu numerele pe care dorim sa le linkuim.
						matrix[i][j] = ConectionType;
						matrix[j][i] = ConectionType;

						return; //iesim din functie daca am sters / adaugat link 

					}

					j++;

				}

			}

			i++;

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


	//functia de suprimare nod din lista, vom trata si de-linkuirea nodurilor legate la nodul sters si vom pregati matricea pentru adaugarea unui nou nod.
	void Graf::SuprimNod()
	{

		//verificam daca putem efectua stergerea
		if (this->GrafVid())
		{

			cout << "Graf vid - stergerea nu poate avea loc" << endl;
			return;

		}

		shared_ptr<Node> DeletedNode = nullptr;//pointer la nodul pe care il vom sterge din lista de noduriGraf
		bool numberWasDeleted{ false };
		int toDelete = 0;
		int DeletedNodeIndex = 0;//variabila pentru a retine pozitia nodului sters din matrice

		cout << "Introduceti numarul pe care doriti sa il stergeti: ";
		cin >> toDelete;


		//iteram in noduri graf pentru a verifica daca exista nodul pe care dorim sa il stergem
		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{

			if (toDelete == actual->get()->getData())
			{

				cout << "Nodul " << actual->get()->getData() << " va fi sters." << endl;
			    DeletedNodeIndex = nodePosition(*actual, NoduriGraf);//inregistram index-ul nodului pe care il stergem pentru a sterge si linia si coloana din matrice

				NoduriGraf.erase(actual);//efectuam stergerea nodului

				numberWasDeleted = true;
				break;

			}

		}

		cout << "Stergem link-urile..." << endl;

		//cautam pe linie deoarece deja stim pozitia pe linie(node_position).
		for (int i =0 ; i < MAX ;i++)
		{

			//daca numarul de pe linie la care am ajuns are setat true in matrice inseamna ca trebuie sa stergem linkurile- punem pe false.
				matrix[i][DeletedNodeIndex] = false;//daca avem link, il stergem

		}

		for (int i = 0; i < MAX; i++)
		{

			//daca numarul de pe coloana la care am ajuns are setat true in matrice inseamna ca trebuie sa stergem linkurile- punem pe false.
			matrix[DeletedNodeIndex][i] = false;//daca avem link, il stergem

		}


		//facem tranzitiile necesare in matrice pentru a repozitiona linkurile din matrice la nodurile corespunzatoare
		for (int transition = DeletedNodeIndex; transition < MAX; transition++)
		{

			//verificam ca indexul nodului sters sa nu fie ultimul, daca este ultimul iesim din loop-ul de rearanjare a matricei
			if (DeletedNodeIndex == MAX-1 && transition == MAX-1)
			{

				break;

			}
			
			//interschimbam fiecare element pe pe pozitia (i,del) cu (i,del+1) - interschimbarea coloanelor
			for (int i = 0; i < MAX; i++)
			{

				matrix[i][transition] = matrix[i][transition + 1];

			}
		
			//interschimbam fiecare element pe pe pozitia (del,j) cu (del+1,j) - interschimbarea liniilor
			for (int j = 0; j < MAX; j++)
			{

				matrix[transition][j] = matrix[transition +1][j];

			}

		}


		//ne asiguram ca pe ultima coloana vom avea doar false - pentru a pregati introducerea unui nou nod in graf
		for (int i = 0; i < MAX; i++)
		{

			matrix[i][MAX-1] = false;//trecem toate elementele de pe coloana in false

		}

		for (int j = 0; j < MAX; j++)
		{

			matrix[MAX-1][j] = false;//trecem toate elementele de pe linie in false

		}
		

			
	
		if (!numberWasDeleted)
		{

			cout << "Numarul " << toDelete << " nu exista in graf" << endl;

		}

	}


	//functia de afisare ale nodurilor din graf
	void Graf::afisareNoduriGraf()
	{
		if (this->GrafVid())
		{
			return;
		}
		else
		{

			cout << "Graful contine:\n";


			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				cout << actual->get()->getData() << "\t";

			}

		}

	}


	//pentru detalii, verifica comentariile din functia InsertNode
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


	//pentru detalii, verifica comentariile din functia InsertArc
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


	//functia de afisare a nodurilor cautate prin BFS si DFS
	void  matrix_graf::Graf::PrintNodesSearchedInGraf()
	{

		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{

			cout << iterator->get()->getData() << "  ";

		}

	}


	//verificam daca un nod exista intr-o lista
	bool  matrix_graf::Graf::NodeExistsInList(shared_ptr<Node>& actual, list<shared_ptr<Node>>& li)
	{

		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			if (*iterator == actual)
			{

				return true;

			}

		}

		return false;

	}


	//functie care ne va returna pozitia pe care se afla un nod intr-o lista
	int matrix_graf::Graf::nodePosition(shared_ptr<Node>& actual, list<shared_ptr<Node>>& li)
	{

		int position{ 0 };
		int counter{ 0 };

		for (auto actualNode : li)
		{

			if (actualNode == actual)
			{
				break;
			}

			counter++;

		}

		return counter;

	}


	//functie care ne va returna o lista cu toate nodurile adiacente lui actual
	//parametrul functiei va fi pozitia nodului pe care dorim sa il verificam din NoduriGraf si nodul in sine 
	list<shared_ptr<Node>> matrix_graf::Graf::searchForArc(shared_ptr<Node>& actual, int node_position)
	{

		list<shared_ptr<Node>> ConnectedNodesToActual{};//lista care va contine toate nodurile adiacente lui actual
		auto it = this->getFirstNode(); //iterator folosit pentru a adauga nodul la care gasim legatura, in lista connectedNodeToActual

		//cautam nodurile adiacente a lui actual.
		size_t j = 0;
			//cautam pe coloana deoarece deja stim pozitia pe linie(node_position).
			for (auto actual_j = NoduriGraf.begin(); actual_j != NoduriGraf.end(); ++actual_j)
			{

				//daca numarul de pe coloana la care am ajuns are setat true in matrice inseamna ca trebuie sa il adaugam in lista de connected.
				if (matrix[node_position][j] == true)
				{

					advance(it, j);//ducem iteratorul cu j pozitii in NoduriGraf dupa care il adaugam in lista ConnectedNodesToActual
					ConnectedNodesToActual.push_back(*it);

				}
				it = this->getFirstNode();//reinitializam iteratorul cu primul nod din NoduriGraf, deoarece dorim ca in urmatoarea iteratie sa avansam cu j pozitii din nou in cazul in care gasim un nod cu link.
				j++;//incrementam pozitia coloanei

			}
			
			return ConnectedNodesToActual;//returnam lista gasita

	}


	//functia de cautare in adancime va fi implementata folosind recursivitate, acelasi principiu ca si la implementarea prin structura
	void matrix_graf::Graf::DepthFirstSearch(shared_ptr<Node>& actual)
	{

		
		//verificam ca nodul la nu fie deja vizitat
		if (NodeExistsInList(actual, NodesSearchedInGraf))
		{

			return;

		}
		else
		{

			//daca nu este vizitat, il adaugam in lista cu nodurile gasite.
			NodesSearchedInGraf.push_back(actual);

		}

		list<shared_ptr<Node>> ConnectedNodesToActual = searchForArc(actual, nodePosition(actual, NoduriGraf));//lista care va contine toate nodurile adiacente lui actual
		
		for (auto iterator : ConnectedNodesToActual)
		{

			DepthFirstSearch(iterator);//apelam functia de cautare pentru fiecare nod din lista de adiacenta

		}

	}


	//functia de cautare prin cuprindere primeste ca si parametru nodul de start
	void matrix_graf::Graf::BreadthFirstSearch(shared_ptr<Node>& firstNode)
	{

			this->NodesSearchedInGraf.clear();//vom da clear la lista in care punem nodurile gasite
			shared_ptr<Node> actual = nullptr;//nodul la care ajungem

			que.push(firstNode);//punem primul nod in queue de la care dorim sa incepem, poate fi oricare nod din graf.

			list<shared_ptr<Node>> ConnectedNodesToActual{}; // cream un pointer catre lista nodurilor la care este conectat actual (actual->getNext())

			while (!que.empty())//atata timp cat in queue avem noduri vom face traversarea grafului
			{

				actual = que.front();//punem in actual primul nod din queue
				NodesSearchedInGraf.push_back(actual);//punem nodul la care am ajuns intr-o lista pe care o vom afisa la sfarsit ul functiei.
				//Putem de asemenea sa facem afisarea nodului la care am ajuns aici, dar avem nevoie oircum de lista "NodeSearchedInGraf" pentru a tine evidenta nodurilor deja gasite.

				ConnectedNodesToActual = searchForArc(actual, nodePosition(actual, NoduriGraf));//lista care va contine toate nodurile adiacente lui actual

				//verificam ca nodurile pe care le-am gasit adiacente la actual sa nu fie in lista sau queue de noduri deja parcurse.
				for (auto iterator = ConnectedNodesToActual.begin(); iterator != ConnectedNodesToActual.end(); ++iterator)
				{

					if (NodeExistsInQueue(*iterator) || NodeExistsInNodesSearchedInGraf(*iterator))
					{

						continue;//atata timp nodul la care am ajuns in iteratie exista in queue sau in lista de noduri cautate, trecem la urmatorul

					}
					else
					{

						//cand ajungem la un nod care nu exista in queue si nici in lista de nodrui cautate inseamna ca trebuie sa il traversam, deci il punem in queue
						que.push(*iterator);//adaugam nodul in queue daca nu a fost deja 

					}

				}

				que.pop();//dupa ce am verificat nodurile de next ale lui actual, putem sa il stergem din queue si trecem la urmatorul ciclu

			}

			PrintNodesSearchedInGraf(); //afisam lista nodurilor gasita in ciclul de mai sus, in ordinea in care au fost gasite.

	}


}
