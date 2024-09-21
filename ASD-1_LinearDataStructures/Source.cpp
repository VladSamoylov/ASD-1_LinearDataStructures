#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;

template <typename T>
class DoubleLinkedList;

template <typename T>
class Node {
private:
	Node<T>* ptrnext;
	Node<T>* ptrprev;
	T data;
	friend class DoubleLinkedList<T>;
public:
	Node(const T& data) : data(data), ptrnext(nullptr), ptrprev(nullptr) {}
};

template <typename T>
class DoubleLinkedList {
private:
	Node<T>* first;
	Node<T>* last;
	Node<T>* current;
public:
	DoubleLinkedList() : first(nullptr), last(nullptr), current(nullptr) {}
	DoubleLinkedList(const int&, const vector<T>&);
	void AddToStart(const T&);
	void AddToPos(const int&, const T&);
	bool FindByPoz(const int&);
	void DeleteByPos(const int&);
	void ShowFirstToLast();
	void ShowLastToFirst();
	~DoubleLinkedList();
};

/**
 * @brief Параметричний конструктор Двозв'язного списку
 * @tparam T Тип даних двозвязного списку
 * @param size Розмір двозв'язного списку
 * @param data Дані двозв'язного списку
 */
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const int& size, const vector<T>& data) {
	
	this->first = new Node<T>(data[0]);
	this->last = this->first;
	this->current = nullptr;
	this->first->ptrprev = nullptr;
	this->first->ptrnext = nullptr;

	if (size > 1) {
		for (int i = 1; i < data.size(); i++) {
			Node<T>* node = new Node<T>(data[i]);
			node->ptrprev = this->last;
			this->last->ptrnext = node;
			this->last = node;
			this->last->ptrnext = nullptr;
		}
	}
}

/**
 * @brief Деструктор Двозв'язного списку
 * @tparam T Тип даних двозвязного списку
 */
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	
	while (this->first != nullptr) {
		this->current = this->first;
		this->first = this->first->ptrnext;
		delete this->current;
		this->current = nullptr;
		cout << "Delete Node" << endl;
	}
	this->last = nullptr;
}

/**
 * @brief Метод, який виводить ноди списку з початку до кінця
 * @tparam T Тип даних двозв'язного списку
 */
template <typename T>
void DoubleLinkedList<T>::ShowFirstToLast() {

	this->current = this->first;
	while (true) {
		cout << "Adress node: " << this->current << "| Data: " << this->current->data << endl;
		if (this->current == this->last) { break; }
		this->current = this->current->ptrnext;
	}
}

/**
 * @brief Метод, який виводить ноди з кінця до початку
 * @tparam T Тип даних двозв'язного списку
 */
template <typename T>
void DoubleLinkedList<T>::ShowLastToFirst() {

	this->current = this->last;
	while (true) {
		cout << "Adress node: " << this->current << "| Data: " << this->current->data << endl;
		if (this->current == this->first) break;
		this->current = this->current->ptrprev;
	}
}

/**
 * @brief Метод, який додає нод до початку списку
 * @tparam T Тип даних двозв'язного списку
 * @param data Дані двозв'язного списку
 */
template <typename T>
void DoubleLinkedList<T>::AddToStart(const T& data) {

	this->current = this->first;
	this->first = new Node<T>(data);
	this->current->ptrprev = this->first;
	this->first->ptrnext = this->current;
	this->first->ptrprev = nullptr;
	this->current = nullptr;
}

/**
 * @brief Метод, який шукає заданий нод в списку
 * @tparam T Тип даних двозв'язного списку
 * @param position Задане місце ноду
 * @return True - нод знайдений, інакше false
 */
template <typename T>
bool DoubleLinkedList<T>::FindByPoz(const int& position) {

	this->current = this->first;
	if (this->current == nullptr) { cout << "List is empty\n"; return false; }
	if (position < 1) { cout << "Invalid position\n"; return false; }
	for (int i = 0; i < position - 1; i++) {
		this->current = this->current->ptrnext;
		if (this->current == nullptr) { cout << "Don't find following Node\n"; return false; }
	}
	cout << "The #" << position << " has the following data: " << this->current->data << endl;
	return true;
}

/**
 * @brief Метод додавання вузла після заданого
 * @tparam T Тип даних двозв'язного списку
 * @param position  Задане місце ноду
 * @param data Дані двозв'язного списку
 */
template <typename T>
void DoubleLinkedList<T>::AddToPos(const int& position, const T& data) {

	this->current = this->first;
	for (int i = 0; i < position - 1; i++) {
		this->current = this->current->ptrnext;
	}
	Node<T>* node = new Node<T>(data);
	if (this->current == this->last) {
		node->ptrnext = nullptr;
		this->last = node;
	}
	else {
		node->ptrnext = this->current->ptrnext;
		this->current->ptrnext->ptrprev = node;
	}
	this->current->ptrnext = node;
	node->ptrprev = this->current;
}

/**
 * @brief Метод видалення заданого ноду
 * @tparam T Тип даних двозв'язного списку
 * @param position Задане місце ноду
 */
template <typename T>
void DoubleLinkedList<T>::DeleteByPos(const int& position) {

	this->current = this->first;
	for (int i = 0; i < position - 1; i++) {
		this->current = this->current->ptrnext;
	}
	if (this->current == this->first) {
		this->current->ptrnext->ptrprev = nullptr;
		this->first = this->current->ptrnext;
	}
	else if (this->current == this->last) {
		this->current->ptrprev->ptrnext = nullptr;
		this->last = this->current->ptrprev;
	}
	else {
		this->current->ptrprev->ptrnext = this->current->ptrnext;
		this->current->ptrnext->ptrprev = this->current->ptrprev;
	}
	
	delete this->current;
}

class Student {
private:
	string name;
	string surname;
	string lastname;
	int specialty;
	vector<string> discipline;
	vector<chrono::year_month_day> data;
	vector<int> estimation;
	static int studentnumber;
public:
	Student();
};

class Heap {
private:
	vector<int> data;
	bool max_heap;

	void SiftUp();
	void SiftDown(int);
	int GetMinChild(const int&);
	int GetMaxChild(const int&);
	void Swap(const int&, const int&);
public:
	Heap(const vector<int>&);
	void InsertElem(const int&);
	void DeleteElem(const int&);
	int ExtractRoot();
	void RebuiltUnsortedData(const vector<int>&, const bool&);
	void RebuiltToMaxHeap();
	void RebuiltToMinHeap();
	void Show(const bool&);
	void HeapSort();
};

Heap::Heap(const vector<int>& unsortdata) {

	this->data.push_back(99);
	this->max_heap = true;
	for (int i = 0; i < unsortdata.size(); i++) {
		this->data.push_back(unsortdata[i]);
		SiftUp();
	}
}

void Heap::RebuiltUnsortedData(const vector<int>& unsortdata, const bool& max_heap) {

	this->data.clear();
	this->data.push_back(99);
	this->max_heap = max_heap;
	for (int i = 0; i < unsortdata.size(); i++) {
		this->data.push_back(unsortdata[i]);
		SiftUp();
	}
}

void Heap::RebuiltToMinHeap() {

	if (this->max_heap == false) { cout << "Error: <The Heap is current Min-Heap>" << endl; return; }
	vector<int> tmp(this->data);
	this->max_heap = false;
	this->data.clear();
	this->data.push_back(99);

	for (int i = 1; i < tmp.size(); i++) {
		this->data.push_back(tmp[i]);
		SiftUp();
	}
}

void Heap::RebuiltToMaxHeap() {

	if (this->max_heap == true) { cout << "Error: <The Heap is current Max-Heap>" << endl; return; }
	vector<int> tmp(this->data);
	this->max_heap = true;
	this->data.clear();
	this->data.push_back(99);

	for (int i = 1; i < tmp.size(); i++) {
		this->data.push_back(tmp[i]);
		SiftUp();
	}
}

void Heap::SiftUp() {

	int i = this->data.size() - 1;

	while (i > 1) {
		int parent = i / 2;
		if (this->max_heap) {
			if (this->data[parent] < this->data[i]) Swap(parent, i);
			else break;
		}
		else {
			if (this->data[parent] > this->data[i]) Swap(parent, i);
			else break;
		}
		
		i = parent;
	}
}

void Heap::SiftDown(int parent) {
	
	while (2 * parent <= this->data.size() - 1) {
		if (this->max_heap) {
			int max_child = GetMaxChild(parent);
			if (this->data[parent] < this->data[max_child]) {
				Swap(parent, max_child);
			}
			else break;
			parent = max_child;
		}
		else {
			int min_child = GetMinChild(parent);
			if (this->data[parent] > this->data[min_child]) {
				Swap(parent, min_child);
			}
			else break;
			parent = min_child;
		}
	}
}

int Heap::GetMinChild(const int& parent) {

	if (2 * parent + 1 > this->data.size() - 1) return 2 * parent;
	else {
		if (this->data[2 * parent] < this->data[2 * parent + 1]) return 2 * parent;
		else return 2 * parent + 1;
	}
}

int Heap::GetMaxChild(const int& parent) {

	if (2 * parent + 1 > this->data.size() - 1) return 2 * parent;
	else {
		if (this->data[2 * parent] > this->data[2 * parent + 1]) return 2 * parent;
		else return 2 * parent + 1;
	}
}

void Heap::Swap(const int& first_index, const int& second_index) {

	int tmp = this->data[first_index];
	this->data[first_index] = this->data[second_index];
	this->data[second_index] = tmp;
}

int Heap::ExtractRoot() {

	if (this->data.empty()) { cout << "Error: <Heap is Empty>" << endl; }
	int root = this->data[1];
	this->data[1] = this->data[this->data.size() - 1];
	this->data.pop_back();
	SiftDown(1);

	return root;
}

void Heap::InsertElem(const int& element) {

	this->data.push_back(element);
	SiftUp();
}

void Heap::DeleteElem(const int& number_elem) {

	if (number_elem > this->data.size() - 1 || number_elem < 0) { cout << "Error: <Out of the Range>"; return; }
	if (number_elem == this->data.size() - 1) { this->data.pop_back(); cout << "The Last Element was Deleted" << endl; return; }
	this->data[number_elem] = this->data[this->data.size() - 1];
	this->data.pop_back();
	SiftDown(number_elem);
}

void Heap::HeapSort() {



}

void Heap::Show(const bool& ischild) {

	cout << "Max-Heap contains: ";
	for (int i = 1; i < this->data.size(); i++) {
		cout << this->data[i] << " ";
	} cout << endl;
	if (ischild) {
		cout << "Parent-child: \n";
		int n = 0;
		for (int i = 1; i < this->data.size(); i++) {
			if (this->data[i] / 10 == 0) n = 5;
			else if (this->data[i] / 10 < 10) n = 4;
			else n = 3;
			string space(n, ' ');
			cout << space << '(' << this->data[i] << ')';
			if (2 * i <= this->data.size() - 1) {
				cout << endl << space << '/';
				if (2 * i + 1 <= this->data.size() - 1) { 
					if (this->data[i] / 10 == 0) n = 1;
					else if (this->data[i] / 10 < 10) n = 2;
					else n = 0;
					space.resize(n, ' ');
					cout << space << '\\'; 
				}
				if (this->data[i] / 10 == 0) n = 3;
				else if (this->data[i] / 10 < 10) n = 1;
				else n = 0;
				space.resize(n, ' ');
				cout << endl << space << '(' << this->data[2 * i] << ')';
			}
			if (2 * i + 1 <= this->data.size() - 1) {
				if (this->data[i] / 10 == 0 && this->data[2 * i + 1] / 10 == 0) n = 1;
				else if (this->data[i] / 10 < 10 && (this->data[2 * i] / 10 < 10 && this->data[2 * i] / 10 > 0) && this->data[2 * i + 1] / 10 == 0) n = 2;
				else if (this->data[i] / 10 < 10 && this->data[2 * i + 1] / 10 == 0) n = 4;
				else if (this->data[i] / 10 == 0) n = 6;
				else if (this->data[i] / 10 < 10) n = 2;
				else n = 2;
				space.resize(n, ' ');
				cout << space << '(' << this->data[2 * i + 1] << ')' << endl;
			}
			else cout << endl;
		}
	}	
}

int main() {

	int task = 99, ltask = 99, htask = 99;
	int n = 10;
	int position;
	vector<string> data;
	for (int i = 0; i < n; i++) {
		data.push_back("This data #" + to_string(i + 1));
	}
	vector<int> data_int;
	for (int i = 0; i < n; i++) {
		data_int.push_back(i + 1);
	}
	vector<int> data_heap{ 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };

	DoubleLinkedList<string> v(n, data);
	//DoubleLinkedList<int> v(n, data_int);

	Heap h(data_int);

	while (task != 0) {
		switch (task) {
		case 1:
			while (ltask != 0) {
				switch (ltask) {
				case 1:
					v.AddToStart("Data add to head list");
					break;
				case 2:
					try {
						cout << "Enter Node Position: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						if (!v.FindByPoz(position)) throw 404;
						v.AddToPos(position, "Data add to current pos");
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					catch (const int&) {
						cerr << "\nError: <Current Node Don't Find>" << endl;
					}
					break;
				case 3:
					try {
						cout << "Enter Node Position: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						v.FindByPoz(position);
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					break;
				case 4:
					try {
						cout << "Enter Node Position: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						if (!v.FindByPoz(position)) throw 404;
						v.DeleteByPos(position);
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					catch (const int&) {
						cerr << "\nError: <Current Node Don't Find>" << endl;
					}
					break;
				case 5:
					v.ShowFirstToLast();
					break;
				case 6:
					v.ShowLastToFirst();
					break;
				}
				cout << "\n________Work with Double Linked List________" << endl;
				cout << setw(30) << left << "Add Node to Head List " << " / Enter - 1" << endl;
				cout << setw(30) << left << "Add Node after Chosen " << " / Enter - 2" << endl;
				cout << setw(30) << left << "Find Chosen Node " << " / Enter - 3" << endl;
				cout << setw(30) << left << "Delete Chosen Node " << " / Enter - 4" << endl;
				cout << setw(30) << left << "Show Nodes from Head to Tail" << " / Enter - 5" << endl;
				cout << setw(30) << left << "Show Nodes from Tail to Head" << " / Enter - 6" << endl;
				cout << setw(30) << left << "Back " << " / Enter - 0" << endl;
				if (ltask != 0) {
					try {
						cout << "\nChoose the Task: ";
						cin >> ltask;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
					}
					catch (const char* err) {
						cerr << endl << err << endl;
						ltask = 99;
					}					
				}
			}			
			break;
		case 2:
			while (htask != 0) {
				switch (htask) {
				case 1:
					cout << "\n!-Insert 12 to Heap\n";
					h.InsertElem(12);
					break;
				case 2:
					try {
						cout << "\n!-Enter Elem Position: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						h.DeleteElem(position);
						cout << "Element was deleted..." << endl;
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					break;
				case 3:
					h.RebuiltToMaxHeap();
					h.Show(0);
					break;
				case 4:
					h.RebuiltToMinHeap();
					h.Show(0);
					break;
				case 5:
					h.Show(1);
					break;
				case 6:
					cout << "The root of Heap : " << h.ExtractRoot() << endl;
					break;
				case 7:
					cout << "Unsorted Data: ";
					for (int i : data_heap) {
						cout << i << " ";
					}cout << endl;
					h.RebuiltUnsortedData(data_heap, 0);
					h.Show(0);
					break;
				}
				cout << "\n________Work with Binary Heap________" << endl;
				cout << setw(30) << left << "Insert Element " << " / Enter - 1" << endl;
				cout << setw(30) << left << "Delete Chosen Element " << " / Enter - 2" << endl;
				cout << setw(30) << left << "Rebuild to Max-heap " << " / Enter - 3" << endl;
				cout << setw(30) << left << "Rebuild to Min-heap " << " / Enter - 4" << endl;
				cout << setw(30) << left << "Show Elements" << " / Enter - 5" << endl;
				cout << setw(30) << left << "Extract the root " << " / Enter - 6" << endl;
				cout << setw(30) << left << "Rebuild (unsorted data) " << " / Enter - 7" << endl;
				cout << setw(30) << left << "Back " << " / Enter - 0" << endl;
				if (htask != 0) {
					try {
						cout << "\nChoose the Task: ";
						cin >> htask;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
					}
					catch (const char* err) {
						cerr << endl << err << endl;
						htask = 99;
					}
				}
			}
			break;
		case 0:
			break;
		}

		cout << "\n________________Menu of action________________" << endl;
		cout << setw(30) << left << "Work with Double Linked List " << " / Enter - 1" << endl;
		cout << setw(30) << left << "Work with Heap " << " / Enter - 2" << endl;
		cout << setw(30) << left << "Work with Lab Task var 17 " << " / Enter - 3" << endl;
		cout << setw(30) << left << "Exit " << " / Enter - 0" << endl;

		if (task != 0) {
			ltask = 99;
			try {
				cout << "\nChoose the Task: ";
				cin >> task;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw "Error: <Incorrect Input Data>";
				}
			}
			catch (const char* err) {
				cerr << endl << err << endl;
				task = 99;
			}			
		}
	}

	return 0;
}