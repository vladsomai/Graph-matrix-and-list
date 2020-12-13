#include"Node_structure.h"
#include <queue>

namespace structure_graf
{

	class Graf
	{

	private:
		list<shared_ptr<Node>> NoduriGraf;//lista care v-a retine adresele fiecarui nod din graf (fiecare nod este head - capul listei inlantuite)
		queue< shared_ptr<Node> > que{};//queue pentru implementarea functiei de cautare prin cuprindere
		list < shared_ptr<Node> >NodesSearchedInGraf{};//lista in care vom insera nodurile parcurse de BFS & DFS, dupa care o vom afisa in ordinea in care au fost inserate noduri.

	public:
        //------------------------------------------------------------
		bool GrafVid();

		void InsertNode();
		void SuprimNod();
		void InsertNodeParam(int);

		void InsertArc(bool);
		void InsertArcParam(bool, int, int);

		void DepthFirstSearch(shared_ptr<Node>&);
		void BreadthFirstSearch(shared_ptr<Node>&);

		bool NodeExistsInQueue(shared_ptr<Node>&);
		bool NodeExistsInNodesSearchedInGraf(shared_ptr<Node>&);
		bool NodeExistsInList(shared_ptr<Node>&, list < shared_ptr<Node>>&);

		void PrintStructure();
		void afisareNoduriGraf();
		void PrintNodesSearchedInGraf();

		size_t sizeof_NoduriGraf() { return NoduriGraf.size(); }
		
		void clearSearchedList() { NodesSearchedInGraf.clear(); }
		auto getFirstNode() { return this->NoduriGraf.begin(); }
		//------------------------------------------------------------

		
		//constructor - initializare obiect graf - InitGraf()
		Graf()
		{

			//cream lista fara noduri
			NoduriGraf.clear();
			NodesSearchedInGraf.clear();
		
		}

		~Graf() = default;

	};

	//functia de verificare graf vid
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


	//functie de stergere nod parametru dintr-o lista parametru
	void DeleteNodeInList(shared_ptr<Node>& deleteNode, list < shared_ptr<Node>>& li)
	{

		//folosim un obiect de tipul std::list<>::iterator pentru iteratie in lista parametru
		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			//daca nodul pe care dorim sa il stergem este cel la care am ajuns in iteratie apelam functia de erase
			if (*iterator == deleteNode)
			{

				li.erase(iterator);
				return;
			
			}

		}

	}


	//functie de afisare a coadei
	void print_queue(queue<shared_ptr<Node>>& q)
	{
		cout << "Queue: ";

		while (!q.empty())
		{

			cout << q.front()->getData() << "\t";
			q.pop();

		}

	}


	//functie de afisare a unei liste oarecare
	void print_list(list<shared_ptr<Node>>& li)
	{


		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			cout << iterator->get()->getData()<< "->";

		}

		cout << endl;

	}


	//functie de afisare lista cu adresele fiecarui element din lista
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


	//functie de suprimare nod din graf
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

		shared_ptr<Node> DeletedNode;

		/*
		retinem adresa nodului pe care dorim sa il stergem pentru a face modificarile in tot graful dupa stergere;
		daca stergem un nod care are arc existent catre alt nod, va trebui sa cautam acel nod pe care l-am sters in listele de next ale nodurilor din graf.
		Ex: avem nodurile "2" si "6" in graf cu arc intre ele 2->6->null respectiv 6->2->null
		Dorim sa stergem nodul 6, facem call de functia erase de nodul "6", dupa care trebuie sa cautam in tot graful daca exista un link catre "6" si sa il stergem si de acolo.
		*/

		cout << "Introduceti numarul pe care doriti sa il stergeti: "; cin >> toDelete;

		//iteram in lista pana cand gasim nodul pe care dorim sa il stergem
		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{

			//daca cheia nodului din iteratie este egala cu numarul pe care dorim sa il stergem
			if (toDelete == actual->get()->getData())
			{

				DeletedNode = *actual;//dereferentiem iteratorul actual si retinem adresa la nodul pe care doirm sa il stergem pentru a sterge si link-urile atasate acestui nod
				cout << "Nodul: " << actual->get()->getData() << " va fi sters." << endl;
				NoduriGraf.erase(actual);//efectuam stergerea nodului din lista nodurilor grafului
				
				cout << "Success! Nod sters." << endl;

				numberWasDeleted = true;
				break;

			}

		}

		if (numberWasDeleted)
		{

			cout << "Stergem linkurile.." << endl;

			//verificam in lista de noduri ale grafului daca avem link catre nodul sters
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				auto paramlist = actual->get()->getNext(); //punem in variabila paramlist, lista nodului din iteratie
				DeleteNodeInList(DeletedNode, paramlist);//apelam functia de stergere a nodului din lista

				actual->get()->setNextList(paramlist);//setam lista nodului actual cu cea updatata de functia "DeleteNodeInList".

			}

			return;

		}
		else 
		{

			cout << "Numarul " << toDelete << " nu exista in graf" << endl;
			return;

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

			shared_ptr<Node> temp{};

			for (auto i = NoduriGraf.begin(); i != NoduriGraf.end(); ++i)
			{

				cout << i->get()->getData() << endl;

			}

		}

	}


	//functie de afisare structura a grafului - afisam fiecare arc pe care il are un nod pe o linie
	void Graf::PrintStructure()
	{

		if (this->GrafVid())
		{

			return;

		}

		bool optiune{ false };

		cout << "Doriti sa afisati si adresele nodurilor? (1 - DA / 0 - NU)" << endl;
		cin >> optiune;

		cout <<"====================Structura graf===================="<< endl;
		if (optiune)
		{

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				auto tempList = actual->get()->getNext();

				cout << actual->get()->getData()
					<< " (" << *actual << ") "
					<< "  ->";
				print_list_verbose(tempList);

				cout << endl;

			}

			return;

		}
		else
		{

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				auto tempList = actual->get()->getNext();

				cout << actual->get()->getData()<< "  ->";
				print_list(tempList);

				cout << endl;

			}
			
			return;

		}

	}


	//functie de inserare nod in graf
	void Graf::InsertNode()
	{
		
    	try
		{

			int newNumber{};
			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului
			//daca alocarea memorie nu are loc, sarim in blocul de catch;

			cout << "\nIntroduceti un numar in noul nod: ";	cin >> newNumber;

			newNode->setData(newNumber);//adaugam noua cheie in nod


			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf, vom parcurge lista de noduri ale grafului
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

			cout << "Nu am putut aloca memorie pentru un nou nod.\n" << e.what() << endl;
			return;

		}

	}

	
	void Graf::InsertNodeParam(int newNumber)
	{

		try
		{

			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului
			//daca alocarea memorie nu are loc, sarim in blocul de catch;

			cout << "\nIntroduceti un numar in noul nod: ";	//cin >> newNumber;
			newNode->setData(newNumber);


			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca avem deja numarul in list, deci nu putem face insertia
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


	//verificam daca un nod exista in coada clasei graf
	bool structure_graf::Graf::NodeExistsInQueue(shared_ptr<Node>& actual)
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
	bool  structure_graf::Graf::NodeExistsInNodesSearchedInGraf(shared_ptr<Node>& actual)
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


	//functie de afisare a numerelor gasita de functiile BFS si DFS
	void  structure_graf::Graf::PrintNodesSearchedInGraf()
	{

		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{

			cout << iterator->get()->getData()<<"  ";

		}

	}
	

	//verificam daca un nod exista in lista
	bool  structure_graf::Graf::NodeExistsInList(shared_ptr<Node>& actual , list<shared_ptr<Node>>& li)
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


	/*
	-functia de cautare prin cuprindere va fi implementata folosind o structura de date de tipul queue(coada);
	-incepem intotdeauna de la primul nod din lista de noduri ale grafului(NoduriGraf), se poate schimba aceasta variabila in ordinea preferintelor;
	-folosim variabila "actual" pentru a itera in graf;

	Punem in queue nodurile adiacente a nodului actual(acestea trebuie sa indeplineasca conditia de a nu fi deja 
	in queue sau in lista cu noduri pe care le-am gasit,
	dupa care iteram in queue atata timp cat nu este gol
	*/
	void structure_graf::Graf::BreadthFirstSearch(shared_ptr<Node>& firstNode)
	{

		this->NodesSearchedInGraf.clear();//vom da clear la lista in care punem nodurile gasite
		shared_ptr<Node> actual = nullptr;
		
		que.push(firstNode);//punem primul nod  in queue de la care dorim sa incepem, poate fi oricare nod din graf.

		list<shared_ptr<Node>> ConnectedNodesToActual{}; // cream un pointer catre lista nodurilor la care este conectat actual (actual->getNext())

		while (!que.empty())//atata timp cat in queue avem noduri vom face traversarea grafului
		{

			actual = que.front();//punem in actual primul nod din queue
			NodesSearchedInGraf.push_back(actual);//punem nodul la care am ajuns intr-o lista pe care o vom afisa la sfarsit ul functiei.
			//Putem de asemenea sa facem afisarea nodului la care am ajuns aici, dar avem nevoie oircum de lista "NodeSearchedInGraf" pentru a tine evidenta nodurilor deja gasite.

			ConnectedNodesToActual = actual->getNext();//setam connected nodes
			
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


	/*
	-functia de cautare prin adancime implementata folosind recursivitate;
	-nodul de start se poate schimba in ordinea preferintelor, incrementand iteratorul din meniul clasei;
	-folosim variabila "actual" pentru a itera in graf;

	-verificam daca nodul la care am ajuns are noduri de next pe care le-am vizitat deja, apeland functia "NodeExistsInList", daca nu avem nodul in lista il punem(marcam ca si vizitat);
	-daca nodul este deja vizitat, implicit se foloseste procedeul de back-tracking, iesim din functie si revenim cu pointerul de pe stack la functia care a ramas intrerupta in loop-ul for;

	-apelam functia de cautare in adancime de fiecare node din lista de next a lui actual;
	*/
	void structure_graf::Graf::DepthFirstSearch(shared_ptr<Node>& actual)
	{

			//verificam ca nodul sa nu fie deja vizitat
			if (NodeExistsInList(actual, NodesSearchedInGraf))
			{

				return;

			}
			else
			{
				//daca nu este vizitat, il adaugam in lista cu nodurile gasite.
				NodesSearchedInGraf.push_back(actual);

			}

			list<shared_ptr<Node>> ConnectedNodesToActual = actual->getNext();//lista care va contine toate nodurile adiacente lui actual
			for (auto iterator : ConnectedNodesToActual)
			{

				DepthFirstSearch(iterator);//apelam functia de cautare pentru fiecare nod din lista de adiacenta

			}

		
		
	}


    //functia de inserare nod cu parametrii - cititi comentariile functiei "InsertArc" pentru detaliile pasilor facuti
	void structure_graf::Graf::InsertArcParam(bool ConnectionType, int source, int target)
	{

		if (this->GrafVid())
		{

			return;

		}

		//aceste nodri vor retine adresele nodurilor la care dorim sa inseram un arc (source - target)
		shared_ptr<Node> pointerToSourceNode;
		shared_ptr<Node> pointerToTargetNode;

		int targetWasFound{ false };
		int sourceWasFound{ false };

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
				if (source == actual->get()->getData())
				{

					cout << "Primul numar a fost gasit in graf" << endl;
					sourceWasFound = true;
					pointerToSourceNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

				if (target == actual->get()->getData())
				{
					cout << "Al doilea numar a fost gasit in graf" << endl;
					targetWasFound = true;
					pointerToTargetNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

			}

			//dupa ce am gasit numerele facem legaturile
			if (sourceWasFound && targetWasFound)
			{

				//--------------------------------------Nodul 1------------------------------------------------------------
				//daca dorim sa facem legatura apelam functia de set next a nodului source
				if (ConnectionType == true)
				{

					pointerToSourceNode->setNext(pointerToTargetNode);//stabilim legaturile source
					pointerToTargetNode->setNext(pointerToSourceNode);//stabilim legaturile target
					cout << "Succes, link creat!" << endl;

				}
				else//daca dorim sa stergem legatura prima data trebuie sa cautam ca exista un link intre cele doua noduri, dupa care le vom sterge.
				{

					//iteram in lista nodurilor legate la target pentru a verifica daca source exista in aceasta lista, daca exista vom sterge adresa din lista.
					//pentru nodul target
					auto tempListTarget = pointerToTargetNode->getNext();
					auto tempListSource = pointerToSourceNode->getNext();

					cout << "Lista lui target: ";
					print_list(tempListTarget);
					cout << "Lista lui source: ";
					print_list(tempListSource);


					for (auto iterator = tempListTarget.begin(); iterator != tempListTarget.end(); ++iterator)
					{

						if (*iterator == pointerToSourceNode)
						{

							cout << "Nodul " << iterator->get()->getData() << " va fi sters!" << endl;
							tempListTarget.erase(iterator);//stergem nodul source din lista

							pointerToTargetNode->clearNextList();//stergem lista principala
							pointerToTargetNode->setNextList(tempListTarget);//trimitem ca si parametru lista temporara in lista principala(refresh list)

							break;

						}

					}


					//pentru nodul source
					for (auto iterator = tempListSource.begin(); iterator != tempListSource.end(); ++iterator)
					{

						if (*iterator == pointerToTargetNode)
						{

							cout << "Nodul " << iterator->get()->getData() << " va fi sters!" << endl;
							tempListSource.erase(iterator);//stergem nodul source din lista

							pointerToSourceNode->clearNextList();//stergem lista principala
							pointerToSourceNode->setNextList(tempListSource);//trimitem ca si parametru lista temporara in lista principala(refresh list)

							break;

						}

					}

				}

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;
			return;

		}

		if (!sourceWasFound)
		{

			cout << "Numarul " << source << " nu exista in graf" << endl;
			return;

		}

		if (!targetWasFound)
		{

			cout << "Numarul " << target << " nu exista in graf" << endl;
			return;

		}


	}

	//functie de inserare nod manuala din menuil clasei
	void structure_graf::Graf::InsertArc(bool ConnectionType)
	{

		//verificarea grafului - daca avem graf vid, ne oprim
		if (this->GrafVid())
		{

			return;

		}

		//aceste nodri vor retine adresele nodurilor la care dorim sa inseram un arc (source - target)
		shared_ptr<Node> pointerToSourceNode;
		shared_ptr<Node> pointerToTargetNode;

		//variabile pentru a marca faptul ca am gasit nodurile in graf la care dorim sa adaugam un link
		int targetWasFound{ false };
		int sourceWasFound{ false };

		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;
		
		int source{0};
		int target{0};

		cout << "Primul numar: ";   cin >> source;
		cout << "Al doilea numar: ";cin >> target;

		//ne asiguram prima data ca numerele la care dorim sa introducem un arc exista in graf
		//iteram in lista pana cand gasim nodul la care dorim sa ii adaugam un arc
		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{

			//daca cheia nodului din iteratie este egala cu numarul pe care dorim sa il aflam, 
			//setam pe true ca am gasit nodul si inregistram adresa nodului in variabila pointerToSource / pointerToTarget
			if (source == actual->get()->getData())
			{

				cout << "Primul numar a fost gasit in graf" << endl;
				sourceWasFound = true;
				pointerToSourceNode = *actual;//salvam adresa nodului pentru operatii viitoare

			}

			if (target == actual->get()->getData())
			{

				cout << "Al doilea numar a fost gasit in graf" << endl;
				targetWasFound = true;
				pointerToTargetNode = *actual;//salvam adresa nodului pentru operatii viitoare

			}

		}

		//dupa ce am gasit numerele facem legaturile
		if (sourceWasFound && targetWasFound)
		{

			//--------------------------------------Nodul 1------------------------------------------------------------
			//daca dorim sa facem legatura apelam functia de set next a nodului source
			if (ConnectionType == true)
			{

				//target are link catre source si vice-versa
				pointerToSourceNode->setNext(pointerToTargetNode);//stabilim legaturile source
				pointerToTargetNode->setNext(pointerToSourceNode);//stabilim legaturile target
				cout << "Succes, link creat!" << endl;

			}
			else//daca dorim sa stergem legatura prima data trebuie sa cautam ca exista un link intre cele doua noduri, dupa care le vom sterge.
			{

				//iteram in lista nodurilor legate la target(target->getNext()) pentru a verifica daca source exista in aceasta lista, daca exista vom sterge adresa din lista.
				
				//listele de next a celor doua noduri le vom retine intr-o variabila temporara
				auto tempListTarget = pointerToTargetNode->getNext();
				auto tempListSource = pointerToSourceNode->getNext();

				//iteram in lista lui target
				for (auto iterator = tempListTarget.begin(); iterator != tempListTarget.end(); ++iterator)
				{

					//daca am gasit in lista lui target nodul source, vom sterge nodul source(astfel eliminam arcul de la target la source) 
					if (*iterator == pointerToSourceNode)
					{

						cout << "Nodul " << iterator->get()->getData() << " va fi sters!" << endl;
						tempListTarget.erase(iterator);//stergem nodul source din lista

						pointerToTargetNode->clearNextList();//stergem lista principala
						pointerToTargetNode->setNextList(tempListTarget);//trimitem ca si parametru lista temporara,modificata, in lista principala(refresh list)

						break;

					}

				}

				//iteram in lista lui source
				for (auto iterator = tempListSource.begin(); iterator != tempListSource.end(); ++iterator)
				{

					//daca am gasit in lista lui source nodul target, vom sterge nodul target(astfel eliminam arcul de la source la target) 
					if (*iterator == pointerToTargetNode)
					{

						cout << "Nodul " << iterator->get()->getData() << " va fi sters!" << endl;
						tempListSource.erase(iterator);//stergem nodul target din lista

						pointerToSourceNode->clearNextList();//stergem lista principala
						pointerToSourceNode->setNextList(tempListSource);//trimitem ca si parametru lista temporara,modificata, in lista principala(refresh list)

						break;

					}

				}
				
			}

		}

		if (!sourceWasFound)
		{

			cout << "Numarul " << source << " nu exista in graf" << endl;
			return;

		}

		if (!targetWasFound)
		{

			cout << "Numarul " << target << " nu exista in graf" << endl;
			return;

		}


	}


}

