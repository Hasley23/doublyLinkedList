// doubly linked list
#include <iostream>
#include <string>
#include <ctime>
#define TYPE double	// list typename
using namespace std;

// list node
template <typename T>
struct node
{
	T data;

	// previous node pointer
	node<T> *prev;

	// next node pointer
	node<T> *next;
};

template <typename T>
class List
{
		// first and last nodes
		node<T> *Head, *Tail;
		// length
		int Count;
	public:
		List();
		~List();

		// get list length
		int GetCount();
		// get node by index
		node<T>* GetElem(int);

		// destroy list
		void DelAll();
		// destroy node
		int Del(int);
		// insert new node
		int Insert(int, T);

		// insert as last node
		void AddTail(T n);

		// insert as first node
		void AddHead(T n);

		// display all nodes
		void Print();
		void PrintPtr();
};

template <typename T>
List<T>::List()
{
	// empty list
	Head = Tail = NULL;
	Count = 0;
}

template <typename T>
List<T>::~List()
{
	// delete all nodes
	DelAll();
}

template <typename T>
int List<T>::GetCount()
{
	return Count;
}

template <typename T>
node<T> * List<T>::GetElem(int pos)
{
	// set temporary to head
	node<T> *temp = Head;

	// check position
	if (pos < 1 || pos > Count)
		return 0;

	int i = 1;
	// search node among pointers
	while (i < pos && temp != 0)
	{
		temp = temp->next;
		i++;
	}

	if (temp == 0)
		return 0;
	else
		return temp;
}

template <typename T>
void List<T>::DelAll()
{
	// destroy nodes from head to end
	while (Count != 0)
		Del(1);		// endless shifting
}

template <typename T>
int List<T>::Del(int pos)
{
	// check position
	if (pos < 1 || pos > Count)
		return -1;

	// set temporary to head
	node<T> * Del = Head;

	int i = 1;
	while (i < pos)
	{
		//Search node
		Del = Del->next;
		i++;
	}

	// set previous node
	node<T> * prevTemp = Del->prev;
	// set next node
	node<T> * nextTemp = Del->next;

	// set new next node for list
	if (prevTemp != 0 && Count != 1)
		prevTemp->next = nextTemp;
	// set new previous node for list
	if (nextTemp != 0 && Count != 1)
		nextTemp->prev = prevTemp;

	// delete nodes on edges of list
	if (pos == 1)
		Head = nextTemp;
	if (pos == Count)
		Tail = prevTemp;

	// destroy node
	delete Del;
	// set new length
	Count--;
	return 0;
}

template <typename T>
int List<T>::Insert(int pos, T data)
{
	// check position
	if (pos < 1 || pos > Count + 1)
		return -1;

	// insert 
	if (pos == Count + 1)
	{
		// Add to end of list
		AddTail(data);
		return 0;
	}
	else if (pos == 1)
	{
		// Add to head of list
		AddHead(data);
		return 0;
	}

	node<T> * Ins = Head;

	int i = 1;
	while (i < pos)
	{
		// search for the node before which we insert
		Ins = Ins->next;
		i++;
	}

	// set previous node
	node<T> * prevTemp = Ins->prev;

	// create temp
	node<T> * temp = new node<T>;

	temp->data = data;

	// set new links
	if (prevTemp != 0 && Count != 1)
		prevTemp->next = temp;

	temp->next = Ins;
	temp->prev = prevTemp;
	Ins->prev = temp;

	// update length
	Count++;
	return 0;
}


template <typename T>
void List<T>::AddTail(T n)
{
	// create temp
	node<T> * temp = new node<T>;
	// insert data
	temp->data = n;
	// set new links
	temp->next = 0;
	temp->prev = Tail;

	// set link
	if (Tail != 0)
		Tail->next = temp;

	// check existence of nodes 
	if (Count == 0)
		Head = Tail = temp;
	else
		// insert temp
		Tail = temp;

	// update length
	Count++;
}

template <typename T>
void List<T>::AddHead(T n)
{
	// create temp
	node<T> * temp = new node<T>;
	// insert data
	temp->data = n;
	//set new links
	temp->prev = 0;
	temp->next = Head;

	// set link
	if (Head != 0)
		Head->prev = temp;

	// check existence of nodes
	if (Count == 0)
		Head = Tail = temp;
	else
		// insert temp
		Head = temp;

	// update length
	Count++;
}

template <typename T>
void List<T>::Print()
{
	// display nodes from first to last
	if (Count != 0)
	{
		node<T> * temp = Head;
		while (temp->next != 0)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}

		cout << temp->data << endl;
	}
	else
		cout << "Empty set!" << endl;
}

template <typename T>
void List<T>::PrintPtr()
{
	// display ptrs
	if (Count != 0)
	{
		node<T> * temp = Head;
		cout << temp->prev << ", ";
		while (temp->next != 0)
		{
			cout << temp->next << ", ";
			temp = temp->next;
		}

		cout << temp->next << endl;
	}
	else
		cout << "Empty set!" << endl;
}

int main() {
	srand(time(NULL));
	string choice;

	List<TYPE> iList;

	while (true)
	{
		cout << "--- LIST MENU ---" << endl << "Type:" << endl << 
			"\t 1. 'add' to add an node;" << endl <<
			"\t 2. 'del' to delete an node;" << endl <<
			"\t 3. 'dela' to delete all nodes;" << endl <<
			"\t 4. 'rand' to fill list with random values;" << endl <<
			"\t 5. 'ptrs' to show pointers;" << endl <<
			"\t 6. 'show' to display list;" << endl <<
			"\t 7. 'exit' to leave." << endl << "> ";
		getline(cin, choice);
		cout << endl;

		if (choice == "add")
		{
			TYPE data;
			cout << "Type data" << endl << "> ";
			cin >> data;
			cin.ignore();
			unsigned int start_time = clock();
			iList.AddTail(data);
			start_time = clock() - start_time;
			cout << "time: " << start_time << endl;
		}
		else if (choice == "del")
		{
			int del;
			cout << "Type index" << endl << "> ";
			cin >> del;
			cin.ignore();
			unsigned int start_time = clock();
			del = iList.Del(del);
			start_time = clock() - start_time;
			cout << "time: " << start_time << endl;

			if (del == -1)
				cout << "Fail" << endl;
		}
		else if (choice == "dela")
		{
			unsigned int start_time = clock();
			iList.DelAll();
			start_time = clock() - start_time;
			cout << "time: " << start_time << endl;
		}
		else if (choice == "rand")
		{
			cout << "Type count of nodes" << endl << "> ";
			int cnt;
			cin >> cnt;
			cin.ignore();
			TYPE data;
			unsigned int start_time = clock();
			for (int i = 0; i < cnt; ++i)
			{
				data = static_cast <TYPE> (rand()) / (static_cast <TYPE> (RAND_MAX / (cnt * 2.0)));
				iList.AddTail(data);
			}
			start_time = clock() - start_time;
			cout << "time: " << start_time << endl;
		}
		else if (choice == "ptrs")
		{
			iList.PrintPtr();
		}
		else if (choice == "show")
		{
			iList.Print();
		}
		else if (choice == "exit")
			break;
		else
			cout << "Unknown operation!" << endl;
		cout << endl;
	}
	return 0;
}
