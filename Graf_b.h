#include"Node_b.h"

namespace structure_graf
{


	class Graf
	{

	private:
		list<shared_ptr<Node>> NoduriGraf;//lista care v-a retine adresele fiecarui nod din graf (head - capul listei inlantuite)

	public:

		/*functiile grafului*/
//------------------------------------------------------------
       //void InitGraf();graful se va initializa cu un graf vid atunci cand cream un obiect de tip "Graf", contructorul clasei "Graf" creaza o multime vida de noduri.
		bool GrafVid();

		void InsertNode();
		void SuprimNod();


		void InsertNodeParam(int);
		//functia de insertie sau suprimare arc - parametrul bool decide daca inseram sau stergem
		void InsertArc(bool);
		void InsertArcParam(bool,int,int);


		void DepthFirstSearch();
		void BreadthFirstSearch();


		void PrintStructure();
		//------------------------------------------------------------

		void afisareNoduriGraf();

		//constructor - initializare obiect graf
		Graf()
		{

			//cream lista fara noduri
			NoduriGraf.clear();

		}

		~Graf() = default;

	};



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


	// Performanta : O(n)
	void Graf::InsertNode()
	{

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

	//Performanta : O(3n)
	//Prima cautare in Lista grafulu
	//A doua cautare in lista primul nod
	//A treia cautare in lista nodului 2
	void Graf::InsertArc(bool ConnectionType)
	{

		if (this->GrafVid())
		{

			return;

		}

		int number1{}, number2{};

		//aceste nodri vor retine adresele nodurilor la care dorim sa inseram un arc (source - target)
		shared_ptr<Node> pointerToFirstNode;
		shared_ptr<Node> pointerToSecondNode;




		int number1WasFound{ false };
		int number2WasFound{ false };
		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;

		cout << "Primul numar: "; cin >> number1;
		cout << "Al doilea numar: "; cin >> number2;

		try
		{


			//ne asiguram prima data ca numerele la care dorim sa introducem un arc exista in graf
			//iteram in lista pana cand gasim nodul la care dorim sa ii adaugam un arc
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca cheia nodului urmator din iteratie este egala cu numarul pe care dorim sa il aflam setam pe true si inregistram adresa nodului in variabila pointerToNode
				if (number1 == actual->get()->getData())
				{

					cout << "Primul numar a fost gasit in graf" << endl;
					number1WasFound = true;
					pointerToFirstNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

				if (number2 == actual->get()->getData())
				{
					cout << "Al doilea numar a fost gasit in graf" << endl;
					number2WasFound = true;
					pointerToSecondNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

			}

			//dupa ce am gasit numerele facem legaturile
			if (number1WasFound && number2WasFound)
			{

				//cream doua noduri noi care vor copia cheia nodurilor la care dorim sa inseram un arc
				shared_ptr<Node> pointerToNextNode1 = make_shared<Node>();
				shared_ptr<Node> pointerToNextNode2 = make_shared<Node>();

				//--------------------------------------Nodul 1------------------------------------------------------------

				shared_ptr<Node> temp1 = pointerToFirstNode;//retinem adresa primului nod

				//iteram in lista inlantuita ale nodului la care dorim sa adaugam /stergem un link
				while (pointerToFirstNode != nullptr)
				{

					//daca dorim sa facem legatura
					if (ConnectionType == true)
					{

						if (pointerToFirstNode->getNext() == nullptr)//daca nodul are adresa de next nullptr inseamna ca putem adauga un nod in coada
						{

							//setam valorile noului nod ca si cele ale nodului 2
							pointerToNextNode1->setData(pointerToSecondNode->getData());//atribuim noului nod creat valoarea de la nodul 2

							pointerToFirstNode->setNext(pointerToNextNode1);//punem adresa noului nod in next-ul listei capului de graf

							cout << "Succes! Link creat pentru nodul 1 catre nodul 2" << endl;
							break;

						}

					}
					else//daca dorim sa stergem legatura
					{

						if (pointerToFirstNode->getNext()->getData() == pointerToSecondNode->getData())//daca nodul next are are cheia egala cu nodul 2 atunci putem efectua delinkuirea
						{

							pointerToFirstNode->setNext(pointerToFirstNode->getNext()->getNext());//punem adresa nodului actual->next->next in actual->next(ocolim nodul cu cheia din nodul 2)

							cout << "Succes! Link sters pentru nodul 1 de la nodul 2" << endl;
							break;

						}

					}


					pointerToFirstNode = pointerToFirstNode->getNext();//setam adresa urmatoare in loop daca nu am intrat in "if"

				}

				pointerToFirstNode = temp1;//restabilim adresa primului nod

				//----------------------------------------Nodul 2-----------------------------------------------------------

				shared_ptr<Node> temp2 = pointerToSecondNode;//retinem adresa nodului 2

				//iteram in lista inlantuita ale nodului la care dorim sa adaugam un link
				while (pointerToSecondNode != nullptr)
				{

					if (ConnectionType == true)
					{

						if (pointerToSecondNode->getNext() == nullptr)
						{

							//setam valorile noului nod ca si cele ale nodului 1
							pointerToNextNode2->setData(pointerToFirstNode->getData());//atribuim noului nod creat valoarea de la nodul 1

							pointerToSecondNode->setNext(pointerToNextNode2);//punem adresa noului nod in next-ul listei capului de graf
							cout << "Succes! Link creat pentru nodul 2 catre nodul 1" << endl;
							break;

						}

					}
					else
					{

						if (pointerToSecondNode->getNext()->getData() == pointerToFirstNode->getData())//daca nodul next are are cheia egala cu nodul 2 atunci putem efectua delinkuirea
						{

							pointerToSecondNode->setNext(pointerToSecondNode->getNext()->getNext());//punem adresa nodului actual->next->next in actual->next(ocolim nodul cu cheia din nodul 2)

							cout << "Succes! Link sters pentru nodul 2 la nodul 1" << endl;
							break;

						}

					}

					pointerToSecondNode = pointerToSecondNode->getNext();//setam adresa urmatoare in loop daca nu am intrat in "if"

				}

				pointerToSecondNode = temp2;//restabilim adresa nodului doi

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





	//Performanta O(2n)
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

		shared_ptr<Node> DeletedNode = make_shared<Node>();

		/*
		retinem adresa nodului pe care dorim sa il stergem pentru a face modificarile in tot graful dupa stergere
		daca stergem un nod care are arc existent catre alt nod, va trebui sa cautam acel nod cu cheia egala cu nodul pe care l-am sters.
		Ex: avem nodurile "2" si "6" in graf cu arc intre ele 2->6->null respectiv 6->2->null
		Dorim sa stergem nodul 6, facem call de functia erase de nodul "6", dupa care trebuie sa cautam in tot graful daca exista un link catre "6" si sa il stergem si de acolo.
		*/


		cout << "Introduceti numarul pe care doriti sa il stergeti: ";
		cin >> toDelete;

		try
		{

			//iteram in lista pana cand gasim nodul pe care dorim sa il stergem
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca cheia nodului din iteratie este egala cu numarul pe care dorim sa il stergem
				if (toDelete == actual->get()->getData())
				{

					DeletedNode = *actual;//dereferentiam iteratorul listei - retinem adresa nodului pe care il stergem
					cout << "Nodul: " << actual->get()->getData() << " va fi sters." << endl;

					actual = NoduriGraf.erase(actual);//efectuam stergerea nodului din lista nodurilor grafului

					numberWasDeleted = true;
					break;

				}

			}



			cout << "Efectuam stergerea din linkuri.." << endl;
			shared_ptr<Node> temp{};

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				temp = *actual;

				//iteram in lista inlantuita ale nodului la care dorim sa afisam nodurile de next
				while (temp != nullptr)
				{

					//daca adresa next este nula iesim din while deoarece am parcurs toata lista de legaturi
					if (temp->getNext() == nullptr)
					{

						break;

					}
					//verificam daca exista nodul sters intr-unul din nodurile grafului
					if (temp->getNext()->getData() == DeletedNode->getData())
					{

						cout << "Nodul sters are arc catre nodul " << actual->get()->getData() << endl;

						temp->setNext(temp->getNext()->getNext());//facem linkul catre urmatorul nod

						break;

					}


					temp = temp->getNext();//setam adresa urmatoare in loop

				}

				cout << endl;

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

	//functia de afisare noduri graf, iteram in lista care retine adresa nodurilor aici afisam doar nodurile prezente in graf, nu si structura grafului
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

				shared_ptr<Node> temp{};

				for (auto i = NoduriGraf.begin(); i != NoduriGraf.end(); ++i)
				{

					cout << i->get()->getData() << endl;

				}

			}
			catch (exception e)
			{

				cout << e.what() << endl;

			}

		}

	}



	//Performanta : O(n * nr arce)
	//functia de afisare a structurii grafului - afisam pe linie capul listei si arcele catre noduri
	void Graf::PrintStructure()
	{

		if (this->GrafVid())
		{

			return;

		}

		try
		{

			shared_ptr<Node> temp{};

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				temp = *actual;

				//iteram in lista inlantuita ale nodului la care dorim sa afisam nodurile de next
				while (temp != nullptr)
				{

					cout << temp->getData() << " -> ";//afisam cheia
					temp = temp->getNext();//setam adresa urmatoare in loop

				}

				cout << endl;

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;
			return;

		}

	}




	// Performanta : O(n)
	void Graf::InsertNodeParam(int newNumber)
	{

		try
		{

			//int newNumber{};
			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului

			cout << "\nIntroduceti un numar in noul nod: ";	//cin >> newNumber;

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


	//Performanta : O(3n)
	//Prima cautare in Lista grafulu
	//A doua cautare in lista primul nod
	//A treia cautare in lista nodului 2
	void Graf::InsertArcParam(bool ConnectionType,int number1,int number2)
	{

		if (this->GrafVid())
		{

			return;

		}

		//int number1{}, number2{};

		//aceste nodri vor retine adresele nodurilor la care dorim sa inseram un arc (source - target)
		shared_ptr<Node> pointerToFirstNode;
		shared_ptr<Node> pointerToSecondNode;




		int number1WasFound{ false };
		int number2WasFound{ false };
		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;

		cout << "Primul numar: ";   // cin >> number1;
		cout << "Al doilea numar: ";// cin >> number2;

		try
		{


			//ne asiguram prima data ca numerele la care dorim sa introducem un arc exista in graf
			//iteram in lista pana cand gasim nodul la care dorim sa ii adaugam un arc
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca cheia nodului urmator din iteratie este egala cu numarul pe care dorim sa il aflam setam pe true si inregistram adresa nodului in variabila pointerToNode
				if (number1 == actual->get()->getData())
				{

					cout << "Primul numar a fost gasit in graf" << endl;
					number1WasFound = true;
					pointerToFirstNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

				if (number2 == actual->get()->getData())
				{
					cout << "Al doilea numar a fost gasit in graf" << endl;
					number2WasFound = true;
					pointerToSecondNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

			}

			//dupa ce am gasit numerele facem legaturile
			if (number1WasFound && number2WasFound)
			{

				//cream doua noduri noi care vor copia cheia nodurilor la care dorim sa inseram un arc
				shared_ptr<Node> pointerToNextNode1 = make_shared<Node>();
				shared_ptr<Node> pointerToNextNode2 = make_shared<Node>();

				//--------------------------------------Nodul 1------------------------------------------------------------

				shared_ptr<Node> temp1 = pointerToFirstNode;//retinem adresa primului nod

				//iteram in lista inlantuita ale nodului la care dorim sa adaugam /stergem un link
				while (pointerToFirstNode != nullptr)
				{

					//daca dorim sa facem legatura
					if (ConnectionType == true)
					{

						if (pointerToFirstNode->getNext() == nullptr)//daca nodul are adresa de next nullptr inseamna ca putem adauga un nod in coada
						{

							//setam valorile noului nod ca si cele ale nodului 2
							pointerToNextNode1->setData(pointerToSecondNode->getData());//atribuim noului nod creat valoarea de la nodul 2

							pointerToFirstNode->setNext(pointerToNextNode1);//punem adresa noului nod in next-ul listei capului de graf

							cout << "Succes! Link creat pentru nodul 1 catre nodul 2" << endl;
							break;

						}

					}
					else//daca dorim sa stergem legatura
					{

						if (pointerToFirstNode->getNext()->getData() == pointerToSecondNode->getData())//daca nodul next are are cheia egala cu nodul 2 atunci putem efectua delinkuirea
						{

							pointerToFirstNode->setNext(pointerToFirstNode->getNext()->getNext());//punem adresa nodului actual->next->next in actual->next(ocolim nodul cu cheia din nodul 2)

							cout << "Succes! Link sters pentru nodul 1 de la nodul 2" << endl;
							break;

						}

					}


					pointerToFirstNode = pointerToFirstNode->getNext();//setam adresa urmatoare in loop daca nu am intrat in "if"

				}

				pointerToFirstNode = temp1;//restabilim adresa primului nod

				//----------------------------------------Nodul 2-----------------------------------------------------------

				shared_ptr<Node> temp2 = pointerToSecondNode;//retinem adresa nodului 2

				//iteram in lista inlantuita ale nodului la care dorim sa adaugam un link
				while (pointerToSecondNode != nullptr)
				{

					if (ConnectionType == true)
					{

						if (pointerToSecondNode->getNext() == nullptr)
						{

							//setam valorile noului nod ca si cele ale nodului 1
							pointerToNextNode2->setData(pointerToFirstNode->getData());//atribuim noului nod creat valoarea de la nodul 1

							pointerToSecondNode->setNext(pointerToNextNode2);//punem adresa noului nod in next-ul listei capului de graf
							cout << "Succes! Link creat pentru nodul 2 catre nodul 1" << endl;
							break;

						}

					}
					else
					{

						if (pointerToSecondNode->getNext()->getData() == pointerToFirstNode->getData())//daca nodul next are are cheia egala cu nodul 2 atunci putem efectua delinkuirea
						{

							pointerToSecondNode->setNext(pointerToSecondNode->getNext()->getNext());//punem adresa nodului actual->next->next in actual->next(ocolim nodul cu cheia din nodul 2)

							cout << "Succes! Link sters pentru nodul 2 la nodul 1" << endl;
							break;

						}

					}

					pointerToSecondNode = pointerToSecondNode->getNext();//setam adresa urmatoare in loop daca nu am intrat in "if"

				}

				pointerToSecondNode = temp2;//restabilim adresa nodului doi

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



	void DepthFirstSearch()
	{

	}
	void BreadthFirstSearch()
	{

	}


}