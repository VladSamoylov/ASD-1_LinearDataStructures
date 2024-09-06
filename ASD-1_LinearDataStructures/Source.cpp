#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

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

int main() {

	int task = 9, ltask = 9;
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

	DoubleLinkedList<string> v(n, data);
	//DoubleLinkedList<int> v(n, data_int);

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