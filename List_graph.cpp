#include "List_graph.h"

namespace structure_graf
{
	bool Graf::GrafVid()
	{
		if (NoduriGraf.empty())
		{
			cout << "Graf Vid!" << endl;
			return true;
		}
		else
			return false;

	}

	void DeleteNodeInList(shared_ptr<Node>& deleteNode, list < shared_ptr<Node>>& li)
	{
		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{
			if (*iterator == deleteNode)
			{
				li.erase(iterator);
				return;
			}
		}
	}

	void print_queue(queue<shared_ptr<Node>>& q)
	{
		cout << "Queue: ";
		while (!q.empty())
		{
			cout << q.front()->getData() << "\t";
			q.pop();
		}
	}


	void print_list(list<shared_ptr<Node>>& li)
	{
		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{
			cout << iterator->get()->getData() << "->";
		}
		cout << endl;
	}

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

	void Graf::SuprimNod()
	{
		if (this->GrafVid())
		{
			cout << "Graf vid - stergerea nu poate avea loc" << endl;
			return;
		}

		bool numberWasDeleted{ false };
		int toDelete{};

		shared_ptr<Node> DeletedNode;

		cout << "Introduceti numarul pe care doriti sa il stergeti: "; cin >> toDelete;

		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{
			if (toDelete == actual->get()->getData())
			{
				DeletedNode = *actual;
				cout << "Nodul: " << actual->get()->getData() << " va fi sters." << endl;
				NoduriGraf.erase(actual);

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

	void Graf::PrintStructure()
	{
		if (this->GrafVid())
			return;

		bool optiune{ false };

		cout << "Doriti sa afisati si adresele nodurilor? (1 - DA / 0 - NU)" << endl;
		cin >> optiune;

		cout << "====================Structura graf====================" << endl;
		if (optiune)
		{
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
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{
				auto tempList = actual->get()->getNext();

				cout << actual->get()->getData() << "  ->";
				print_list(tempList);

				cout << endl;
			}
			return;
		}
	}

	void Graf::InsertNode()
	{
		int newNumber{};
		bool numberAlreadyExists{ false };

		shared_ptr<Node> newNode = make_shared<Node>();

		cout << "\nIntroduceti un numar in noul nod: ";	cin >> newNumber;

		newNode->setData(newNumber);

		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{
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
			NoduriGraf.push_back(newNode);
		}
	}

	void Graf::InsertNodeParam(int newNumber)
	{
		bool numberAlreadyExists{ false };

		shared_ptr<Node> newNode = make_shared<Node>();

		cout << "\nIntroduceti un numar in noul nod: ";
		newNode->setData(newNumber);

		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{
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
			NoduriGraf.push_back(newNode);
		}
	}

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

	void  structure_graf::Graf::PrintNodesSearchedInGraf()
	{
		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{
			cout << iterator->get()->getData() << "  ";
		}
	}

	bool  structure_graf::Graf::NodeExistsInList(shared_ptr<Node>& actual, list<shared_ptr<Node>>& li)
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

	void structure_graf::Graf::BreadthFirstSearch(shared_ptr<Node>& firstNode)
	{
		this->NodesSearchedInGraf.clear();
		shared_ptr<Node> actual = nullptr;

		que.push(firstNode);

		list<shared_ptr<Node>> ConnectedNodesToActual{};

		while (!que.empty())
		{
			actual = que.front();
			NodesSearchedInGraf.push_back(actual);
			ConnectedNodesToActual = actual->getNext();

			for (auto iterator = ConnectedNodesToActual.begin(); iterator != ConnectedNodesToActual.end(); ++iterator)
			{
				if (NodeExistsInQueue(*iterator) || NodeExistsInNodesSearchedInGraf(*iterator))
				{
					continue;
				}
				else
				{
					que.push(*iterator);
				}
			}
			que.pop();
		}
		PrintNodesSearchedInGraf();
	}

	void structure_graf::Graf::DepthFirstSearch(shared_ptr<Node>& actual)
	{
		if (NodeExistsInList(actual, NodesSearchedInGraf))
			return;
		else
		{
			NodesSearchedInGraf.push_back(actual);
		}

		list<shared_ptr<Node>> ConnectedNodesToActual = actual->getNext();
		for (auto iterator : ConnectedNodesToActual)
		{
			DepthFirstSearch(iterator);
		}
	}

	void structure_graf::Graf::InsertArcParam(bool ConnectionType, int source, int target)
	{
		if (this->GrafVid())
			return;

		shared_ptr<Node> pointerToSourceNode;
		shared_ptr<Node> pointerToTargetNode;

		int targetWasFound{ false };
		int sourceWasFound{ false };

		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;

		cout << "Primul numar: ";
		cout << "Al doilea numar: ";


		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{
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

	void structure_graf::Graf::InsertArc(bool ConnectionType)
	{
		if (this->GrafVid())
			return;

		shared_ptr<Node> pointerToSourceNode;
		shared_ptr<Node> pointerToTargetNode;

		int targetWasFound{ false };
		int sourceWasFound{ false };

		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;

		int source{ 0 };
		int target{ 0 };

		cout << "Primul numar: ";   cin >> source;
		cout << "Al doilea numar: "; cin >> target;

		for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
		{
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
				//listele de next a celor doua noduri le vom retine intr-o variabila temporara
				auto tempListTarget = pointerToTargetNode->getNext();
				auto tempListSource = pointerToSourceNode->getNext();

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
				for (auto iterator = tempListSource.begin(); iterator != tempListSource.end(); ++iterator)
				{
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