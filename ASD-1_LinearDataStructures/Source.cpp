#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include "tinyxml2.h"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

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
	Student() {};
	Student(const bool&);
	void GenerateXMLData(const int&);
	void GetXMLData(vector<Student>&);
	int GetArithmeticMean();
	int GetAmountDebts();
	void Show();
	void SortInfo(vector<Student>&);
	void TaskSortInfo(vector<Student>&);
};

int Student::studentnumber = 0;

Student::Student(const bool& generate) {

	if (generate) {
		this->studentnumber++;
		this->name = "SomeName #" + to_string(this->studentnumber);
		this->surname = "SomeSurname #" + to_string(this->studentnumber);
		this->lastname = "SomeLastName #" + to_string(this->studentnumber);
		this->specialty = rand() % 150 + 1;
		int amout_discipline = rand() % 64 + 1;
		amout_discipline = amout_discipline - (amout_discipline % 8);
		if (amout_discipline < 8) amout_discipline = 8;
		chrono::year exzama_year = chrono::year(2016 + rand() % 8);
		chrono::month exzama_month = chrono::month(12);;
		int random = 0;
		for (int i = 0; i < amout_discipline; i++) {
			int estimate_rnd = rand() % 3;
			if (exzama_year > chrono::year(2024)) break;
			this->discipline.push_back("SomeDiscipline #" + to_string(i + 1));
			if (estimate_rnd == 0) this->estimation.push_back(rand() % 100 + 1);
			else this->estimation.push_back(60 + (rand() % 40 + 1));
			if ((i + 1) % 8 == 0 && random == 0) { exzama_month = chrono::month(6); random = 1; }
			else if ((i + 1) % 8 == 0 && random == 1) { exzama_month = chrono::month(12); random = 0; }
			if ((i + 1) % 16 == 0) exzama_year += chrono::years(1);
			this->data.push_back(chrono::year(exzama_year) / chrono::month(exzama_month) / chrono::day(21));
		}
	}	
}

/**
 * @brief Метод запису даних класу Student до .xml файлу
 * @param n Кількість елементів для запису
 */
void Student::GenerateXMLData(const int& n) {
	using namespace tinyxml2;

	ostringstream oss;
	XMLDocument doc;
	XMLDeclaration* declaration = doc.NewDeclaration("xml version\"1.0\" encoding=\"UTF-8\"");
	doc.InsertFirstChild(declaration);

	XMLElement* root = doc.NewElement("Students");
	doc.InsertEndChild(root);
	Student s = *this;
	for (int i = 0; i < n; i++) {
		XMLElement* student = doc.NewElement("Student");
		root->InsertEndChild(student);
		XMLElement* name = doc.NewElement("Name");
		name->SetText(s.name.c_str());
		student->InsertEndChild(name);
		XMLElement* surname = doc.NewElement("Surname");
		surname->SetText(s.surname.c_str());
		student->InsertEndChild(surname);
		XMLElement* lastname = doc.NewElement("Lastname");
		lastname->SetText(s.lastname.c_str());
		student->InsertEndChild(lastname);
		XMLElement* specialty = doc.NewElement("Specialty");
		specialty->SetText(s.specialty);
		student->InsertEndChild(specialty);
		for (int j = 0; j < s.discipline.size(); j++) {
			XMLElement* debts = doc.NewElement("Discipline");
			student->InsertEndChild(debts);
			XMLElement* discipline = doc.NewElement("Dis_name");
			discipline->SetText(s.discipline[j].c_str());
			debts->InsertEndChild(discipline);
			chrono::year_month_day date = s.data[j];
			oss << int(date.year()) << "-" << unsigned(date.month()) << "-" << unsigned(date.day());
			XMLElement* data = doc.NewElement("Date");
			data->SetText(oss.str().c_str());
			debts->InsertEndChild(data);
			XMLElement* estimate = doc.NewElement("Estimate");
			estimate->SetText(s.estimation[j]);
			debts->InsertEndChild(estimate);
			oss.str("");
			oss.clear();
		}
		s = Student(1);		
	}	
	XMLError savetofile = doc.SaveFile("students.xml");
	if (savetofile != XML_SUCCESS) {
		throw "Error <Save .xml file>";
	}
	else cout << ".xml file was generated" << endl;
}

/**
 * @brief Метод отримання даних з .xml файлу до елемента типу Student
 * @param s Вектор, що містить інформацію про студентів
 */
void Student::GetXMLData(vector<Student>& s) {
	using namespace tinyxml2;

	XMLDocument doc;
	XMLError load = doc.LoadFile("students.xml");
	if (load != XML_SUCCESS) throw "Error: <Don't reading the file>";
	XMLElement* root = doc.FirstChildElement("Students");
	if (root == nullptr) throw "Error: <Don't find the root>";
	XMLElement* student = root->FirstChildElement("Student");
	for (int i = 0; i < s.size(); i++) {
		XMLElement* name = student->FirstChildElement("Name");
		if (name != nullptr) s[i].name = name->GetText();
		XMLElement* surname = student->FirstChildElement("Surname");
		if (surname != nullptr) s[i].surname = surname->GetText();
		XMLElement* lastname = student->FirstChildElement("Lastname");
		if (lastname != nullptr) s[i].lastname = lastname->GetText();
		XMLElement* specialty = student->FirstChildElement("Specialty");
		if (specialty != nullptr) s[i].specialty = std::stoi(specialty->GetText());
		XMLElement* discipline = student->FirstChildElement("Discipline");
		while (discipline != nullptr) {
			XMLElement* dis_name = discipline->FirstChildElement("Dis_name");
			if (dis_name != nullptr) {
				s[i].discipline.push_back(dis_name->GetText());
				XMLElement* estimate = discipline->FirstChildElement("Estimate");
				if (estimate != nullptr) s[i].estimation.push_back(std::stoi(estimate->GetText()));
				XMLElement* date = discipline->FirstChildElement("Date");
				if (date != nullptr) {
					string dates = date->GetText();
					string year = "", month = "", day = "";
					int separator = 0;
					for (int i = 0; i < dates.size(); i++) {
						if (dates[i] == '-') { separator++; continue; }
						if (separator == 0) year += dates[i];
						else if (separator == 1) month += dates[i];
						else day += dates[i];
					}
					s[i].data.push_back(chrono::year(std::stoi(year)) / chrono::month(std::stoi(month)) / chrono::day(std::stoi(day)));
				}
			}
			discipline = discipline->NextSiblingElement("Discipline");
		}
		student = student->NextSiblingElement("Student");
		if (student == nullptr) break;
	}
}

/**
 * @brief Метод відображення повної інформації, щодо студенту
 */
void Student::Show() {

	cout << setw(14) << left << this->name << setw(16) << left << this->surname << setw(16) << this->lastname << setw(6) << " Spec: " << this->specialty << endl;
	for (int i = 0; i < this->discipline.size(); i++) {
		cout << "   " << setw(20) << this->discipline[i] << "- " << left << setw(10) << this->estimation[i] << setw(10) << this->data[i] << endl;
	}
}

/**
 * @brief Метод відображення інформації, щодо сортування
 * @param s Вектор, що містить інформацію про студентів
 */
void Student::SortInfo(vector<Student>& s) {

	for (int i = 0; i < s.size(); i++) {
		if ((i + 1 < s.size() && s[i].GetAmountDebts() == s[i + 1].GetAmountDebts()) || (i - 1 >= 0 && s[i].GetAmountDebts() == s[i - 1].GetAmountDebts())) {
			cout << setw(14) << left << s[i].name << "N-Debts: " << ANSI_COLOR_RED << left << setw(10)  << s[i].GetAmountDebts() << ANSI_COLOR_RESET << "Amount_EstDebts: " << ANSI_COLOR_GREEN << left << setw(10) << s[i].GetArithmeticMean() << ANSI_COLOR_RESET << endl;
		}
		else cout << setw(14) << left << s[i].name << "N-Debts: " << left << setw(10) << s[i].GetAmountDebts() << "Amount_EstDebts: " << left << setw(10) << s[i].GetArithmeticMean() << endl;
	}
}

/**
 * @brief Метод відображення інформації, щодо завдання лаб. роботи
 * @param s Вектор, що містить інформацію про студентів
 */
void Student::TaskSortInfo(vector<Student>& s) {

	for (int i = 0; i < s.size(); i++) {
		if (s[i].GetAmountDebts() >= 2) {
			if ((i + 1 < s.size() && s[i].GetAmountDebts() == s[i + 1].GetAmountDebts()) || (i - 1 >= 0 && s[i].GetAmountDebts() == s[i - 1].GetAmountDebts())) {
				cout << setw(14) << left << s[i].name << "N-Debts: " << ANSI_COLOR_RED << left << setw(10) << s[i].GetAmountDebts() << ANSI_COLOR_RESET << "Amount_EstDebts: " << ANSI_COLOR_GREEN << left << setw(10) << s[i].GetArithmeticMean() << ANSI_COLOR_RESET << endl;
			}
			else cout << setw(14) << left << s[i].name << "N-Debts: " << left << setw(10) << s[i].GetAmountDebts() << "Amount_EstDebts: " << left << setw(10) << s[i].GetArithmeticMean() << endl;
		}		
	}
}

/**
 * @brief Метод отримання середнього балу студент, щодо його заборгованостей у відомості
 * @return Середній бал
 */
int Student::GetArithmeticMean() {

	int mean = 0;
	for (int i : this->estimation) {
		if (i < 60) mean += i;
	}
	if (this->GetAmountDebts() == 0) return 0;
	else return mean / this->GetAmountDebts();
}

/**
 * @brief Метод отримання кількості заборгованостей студента
 * @return Кількість заборгованостей
 */
int Student::GetAmountDebts() {

	int debts = 0;
	for (int i : this->estimation) {
		if (i < 60) debts += 1;
	}
	return debts;
}

class Heap {
private:
	vector<int> data;
	bool max_heap;

	void SiftUp();
	void SiftDown(int);
	void SiftDown(vector<int>&, int, const int&);
	void SiftDown(vector<Student>&, int, const int&);
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
	void ExtractSort(vector<int>&);
	void HeapSort(vector<int>&);
	void HeapSort(vector<Student>&);
};

Heap::Heap(const vector<int>& unsortdata) {

	this->max_heap = true;
	auto start_var1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < unsortdata.size(); i++) {
		this->data.push_back(unsortdata[i]);
		SiftUp();
	}
	auto end_var1 = chrono::high_resolution_clock::now();
	auto dir_var1 = chrono::duration_cast<chrono::milliseconds>(end_var1 - start_var1);
	//this->Show(1);
	this->data.clear();	
	
	auto start_var2 = chrono::high_resolution_clock::now();
	for (int i = 0; i < unsortdata.size(); i++) {
		this->data.push_back(unsortdata[i]);		
	}
	int parent = unsortdata.size();
	if (parent % 2 == 0) parent = parent / 2 - 1;
	else parent / 2;

	for (int i = parent; i >= 0; i--) {
		SiftDown(i);
	}
	auto end_var2 = chrono::high_resolution_clock::now();
	auto dir_var2 = chrono::duration_cast<chrono::milliseconds>(end_var2 - start_var2);
	//this->Show(1);
	cout << "Sift after one element add vs Sift after all element add:" << endl;
	cout << '!' << static_cast<float>(dir_var1.count()) / 1000.0f << " sec " << static_cast<float>(dir_var2.count()) / 1000.0f << " sec " << endl;
}

/**
 * @brief Метод перебудови купи з невпорядкованого масиву
 * @param unsortdata Невпорядкований масив
 * @param max_heap True - побудувати max-heap, false - min-heap
 */
void Heap::RebuiltUnsortedData(const vector<int>& unsortdata, const bool& max_heap) {

	this->data.clear();
	this->max_heap = max_heap;
	for (int i = 0; i < unsortdata.size(); i++) {
		this->data.push_back(unsortdata[i]);
		SiftUp();
	}
}

/**
 * @brief Метод перебудови купи з max-heap в min-heap
 */
void Heap::RebuiltToMinHeap() {

	if (this->max_heap == false) { cout << "Error: <The Heap is current Min-Heap>" << endl; return; }
	vector<int> tmp(this->data);
	this->max_heap = false;
	this->data.clear();

	for (int i = 0; i < tmp.size(); i++) {
		this->data.push_back(tmp[i]);
		SiftUp();
	}
}

/**
 * @brief Метод перебудови купи з min-heap в max-heap
 */
void Heap::RebuiltToMaxHeap() {

	if (this->max_heap == true) { cout << "Error: <The Heap is current Max-Heap>" << endl; return; }
	vector<int> tmp(this->data);
	this->max_heap = true;
	this->data.clear();

	for (int i = 0; i < tmp.size(); i++) {
		this->data.push_back(tmp[i]);
		SiftUp();
	}
}

/**
 * @brief Метод просіювання елементів вгору
 */
void Heap::SiftUp() {

	int i = this->data.size() - 1;

	while (i > 0) {
		int parent;
		if (i % 2 == 0) parent = i / 2 - 1;
		else parent = i / 2;
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

/**
 * @brief Метод просіювання елементів вниз
 * @param parent Індекс батьківського елемента
 */
void Heap::SiftDown(int parent) {
	
	while (2 * parent + 1 < this->data.size()) {
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

/**
 * @brief Метод просіювання елементів вниз (відновлення структури купи для вхідного невпорядкованого масиву)
 * @param unsorteddata Невпорядкований масив
 * @param parent Індекс батьківського елемента
 * @param heapsize Кількість елементів невпорядкованого масиву до розгляду
 */
void Heap::SiftDown(vector<int>& unsorteddata, int parent,const int& heapsize) {

	while (true) {
		int left_child = 2 * parent + 1;
		int right_child = 2 * parent + 2;
		int min_child = parent;

		if (right_child < heapsize && unsorteddata[right_child] < unsorteddata[min_child]) min_child = right_child;
		if (left_child < heapsize && unsorteddata[left_child] < unsorteddata[min_child]) min_child = left_child;
		if (min_child == parent) break;

		std::swap(unsorteddata[parent], unsorteddata[min_child]);
		parent = min_child;
	}
}

/**
 * @brief Метод просіювання елементів вниз (відновлення структури купи для вхідного невпорядкованого масиву)
 * @param unsorteddata Невпорядкований масив типу Student
 * @param parent Індекс батьківського елемента
 * @param heapsize Кількість елементів невпорядкованого масиву до розгляду
 */
void Heap::SiftDown(vector<Student>& unsorteddata, int parent, const int& heapsize) {

	while (true) {
		int left_child = 2 * parent + 1;
		int right_child = 2 * parent + 2;
		int min_child = parent;		
		
		if (right_child < heapsize && unsorteddata[right_child].GetAmountDebts() < unsorteddata[min_child].GetAmountDebts()) min_child = right_child;
		else if (right_child < heapsize && unsorteddata[right_child].GetAmountDebts() == unsorteddata[min_child].GetAmountDebts()) {
			if (unsorteddata[right_child].GetArithmeticMean() > unsorteddata[min_child].GetArithmeticMean()) min_child = right_child;
		}
		if (left_child < heapsize && unsorteddata[left_child].GetAmountDebts() < unsorteddata[min_child].GetAmountDebts()) min_child = left_child;
		else if (left_child < heapsize && unsorteddata[left_child].GetAmountDebts() == unsorteddata[min_child].GetAmountDebts()) {
			if (unsorteddata[left_child].GetArithmeticMean() > unsorteddata[min_child].GetArithmeticMean()) min_child = left_child;
		}		
		if (min_child == parent) break;

		std::swap(unsorteddata[parent], unsorteddata[min_child]);
		parent = min_child;
	}
}

/**
 * @brief Метод реалізація пірамідального сортування
 * @param unsortdata Невпорядкований масив
 */
void Heap::HeapSort(vector<int>& unsortdata) {

	auto sort_s = chrono::high_resolution_clock::now();
	int heapify_node = unsortdata.size();
	if (heapify_node % 2 == 0) heapify_node = heapify_node / 2 - 1;
	else heapify_node / 2;

	for (int i = heapify_node; i >= 0; i--) {
		SiftDown(unsortdata, i, unsortdata.size());
	}
	for (int i = unsortdata.size() - 1; i > 0; i--) {
		std::swap(unsortdata[0], unsortdata[i]);
		SiftDown(unsortdata, 0, i);
	}
	auto sort_e = chrono::high_resolution_clock::now();
	auto sort_dir = chrono::duration_cast<chrono::milliseconds>(sort_e - sort_s);
	cout << "HeapSort (don't save in the heap): " << static_cast<float>(sort_dir.count()) / 1000.0f << " sec" << endl;
	/*for (int i : unsortdata) {
		cout << i << " ";
	}cout << endl;*/
}

/**
 * @brief Метод реалізація пірамідального сортування
 * @param unsortdata Невпорядкований масив типу Student
 */
void Heap::HeapSort(vector<Student>& unsortdata) {

	int heapify_node = unsortdata.size();
	if (heapify_node % 2 == 0) heapify_node = heapify_node / 2 - 1;
	else heapify_node / 2;

	for (int i = heapify_node; i >= 0; i--) {
		SiftDown(unsortdata, i, unsortdata.size());
	}
	for (int i = unsortdata.size() - 1; i > 0; i--) {
		std::swap(unsortdata[0], unsortdata[i]);
		SiftDown(unsortdata, 0, i);
	}
}

/**
 * @brief Метод отримання відсортованого масиву, шляхом багаторазового вилучення корення
 * @param unsortdata Невпорядкований масив
 */
void Heap::ExtractSort(vector<int>& unsortdata) {

	this->data.clear();
	auto sort_s = chrono::high_resolution_clock::now();	
	this->RebuiltUnsortedData(unsortdata, 1);
	while (!this->data.empty()) {
		this->ExtractRoot();
	}
	/*while (!this->data.empty()) {
		cout << this->ExtractRoot() << " ";
	}cout << endl;*/
	auto sort_e = chrono::high_resolution_clock::now();
	auto sort_dir = chrono::duration_cast<chrono::milliseconds>(sort_e - sort_s);
	cout << "Extract Sort (save in the heap): " << static_cast<float>(sort_dir.count()) / 1000.0f << " sec" << endl;
}

/**
 * @brief Метод знаходження індексу мінімального нащадка
 * @param parent Батьківський індекс
 * @return Індекс мінімального нащадка
 */
int Heap::GetMinChild(const int& parent) {

	if (2 * parent + 2 >= this->data.size()) return 2 * parent + 1;
	else {
		if (this->data[2 * parent + 1] < this->data[2 * parent + 2]) return 2 * parent + 1;
		else return 2 * parent + 2;
	}
}

/**
 * @brief Метод знаходження індексу максимального нащадка
 * @param parent Батьківський індекс
 * @return Індекс максимального нащадка
 */
int Heap::GetMaxChild(const int& parent) {

	if (2 * parent + 2 >= this->data.size()) return 2 * parent + 1;
	else {
		if (this->data[2 * parent + 1] > this->data[2 * parent + 2]) return 2 * parent + 1;
		else return 2 * parent + 2;
	}
}

/**
 * @brief Метод перестановки елементів у купі
 * @param first_index Індекс першого елемента
 * @param second_index Індекс другого елемента
 */
void Heap::Swap(const int& first_index, const int& second_index) {

	int tmp = this->data[first_index];
	this->data[first_index] = this->data[second_index];
	this->data[second_index] = tmp;
}

/**
 * @brief Метод вилучення корення купи
 * @return Корень купи
 */
int Heap::ExtractRoot() {

	if (this->data.empty()) { throw "Error: <Heap is Empty>"; }
	int root = this->data[0];
	this->data[0] = this->data[this->data.size() - 1];
	this->data.pop_back();
	SiftDown(0);

	return root;
}

/**
 * @brief Метод додавання елементу до купи
 * @param element Елемент для вставки
 */
void Heap::InsertElem(const int& element) {

	this->data.push_back(element);
	SiftUp();
}

/**
 * @brief Метод видання видалення елемента з купи
 * @param number_elem Індекс елемента
 */
void Heap::DeleteElem(const int& number_elem) {

	if (number_elem > this->data.size() - 1 || number_elem < 0) throw "Error: <Out of the Range>";
	if (number_elem == this->data.size() - 1) { this->data.pop_back(); cout << "The Last Element was Deleted" << endl; }
	else {
		this->data[number_elem] = this->data[this->data.size() - 1];
		this->data.pop_back();
		SiftDown(number_elem);
	}
}

/**
 * @brief Метод відображення купи
 * @param ischild True - надати з відносинами parent-child, false - ні
 */
void Heap::Show(const bool& ischild) {

	if(this->max_heap) cout << "Max-Heap contains: ";
	else cout << "Min-Heap contains: ";
	for (int i = 0; i < this->data.size(); i++) {
		cout << this->data[i] << " ";
	} cout << endl;
	if (ischild && this->data.size() < 100) {
		cout << "Parent-child: \n";
		int n = 0;
		for (int i = 0; i < this->data.size(); i++) {
			if (this->data[i] / 10 == 0) n = 5;
			else if (this->data[i] / 10 < 10) n = 4;
			else n = 3;
			string space(n, ' ');
			cout << space << '(' << this->data[i] << ')';
			if (2 * i + 1 < this->data.size()) {
				cout << endl << space << '/';
				if (2 * i + 2 < this->data.size()) { 
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
				cout << endl << space << '(' << this->data[2 * i + 1] << ')';
			}
			if (2 * i + 2 < this->data.size()) {
				if (this->data[i] / 10 == 0 && this->data[2 * i + 2] / 10 == 0) n = 1;
				else if (this->data[i] / 10 < 10 && (this->data[2 * i + 1] / 10 < 10 && this->data[2 * i + 1] / 10 > 0) && this->data[2 * i + 2] / 10 == 0) n = 2;
				else if (this->data[i] / 10 < 10 && this->data[2 * i + 2] / 10 == 0) n = 4;
				else if (this->data[i] / 10 == 0) n = 6;
				else if (this->data[i] / 10 < 10) n = 2;
				else n = 2;
				space.resize(n, ' ');
				cout << space << '(' << this->data[2 * i + 2] << ')' << endl;
			}
			else cout << endl;
		}
	}	
}

class Sort {

public:
	Sort() {}
	void BubbleSort(vector<Student>&);
	void ChoiceSort(vector<Student>&);
	void InsertSort(vector<Student>&);
	void ShellSort(vector<Student>&);
};

void Sort::BubbleSort(vector<Student>& unsortdata) {
	
	int length = unsortdata.size();

	cout << "Bubble Sorting is in progress...\n";
	while (length != 0) {
		int max_index = 0;
		for (int i = 0; i < length - 1; i++) {
			if (unsortdata[i].GetAmountDebts() < unsortdata[i + 1].GetAmountDebts()) {
				std::swap(unsortdata[i], unsortdata[i + 1]);
				max_index = i + 1;
			}
			else if ((unsortdata[i].GetAmountDebts() == unsortdata[i + 1].GetAmountDebts())) {
				if (unsortdata[i].GetArithmeticMean() > unsortdata[i + 1].GetArithmeticMean()) {
					std::swap(unsortdata[i], unsortdata[i + 1]);
					max_index = i + 1;
				}
			}
		}
		length = max_index;
	}
}

void Sort::ChoiceSort(vector<Student>& unsortdata) {

	cout << "Choice Sorting is in progress..." << endl;
	for (int i = 0; i < unsortdata.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < unsortdata.size(); j++) {
			if (unsortdata[min_index].GetAmountDebts() < unsortdata[j].GetAmountDebts()) {
				min_index = j;
			}
			else if (unsortdata[min_index].GetAmountDebts() == unsortdata[j].GetAmountDebts()) {
				if (unsortdata[min_index].GetArithmeticMean() > unsortdata[j].GetArithmeticMean()) {
					min_index = j;
				}
			}
		}
		if (min_index != i) {
			std::swap(unsortdata[min_index], unsortdata[i]);
		}
	}
}

void Sort::InsertSort(vector<Student>& unsortdata) {

	cout << "Insert Sorting is in progress..." << endl;
	for (int i = 0; i < unsortdata.size() - 1; i++) {
		for (int j = 0; j <= i; j++) {
			if (unsortdata[i + 1 - j].GetAmountDebts() > unsortdata[i - j].GetAmountDebts()) {
				std::swap(unsortdata[i + 1 - j], unsortdata[i - j]);
			}
			else if (unsortdata[i + 1 - j].GetAmountDebts() == unsortdata[i - j].GetAmountDebts()) {
				if (unsortdata[i + 1 - j].GetArithmeticMean() < unsortdata[i - j].GetArithmeticMean()) {
					std::swap(unsortdata[i + 1 - j], unsortdata[i - j]);
				}
			}
		}
	}
}

void Sort::ShellSort(vector<Student>& unsortdata) {
	
	Student buf;

	cout << "Shell Sorting is in progress..." << endl;
	for (int step = unsortdata.size() / 2; step > 0; step /= 2) {
		for (int i = step; i < unsortdata.size(); i++) {
			buf = unsortdata[i];
			int j;
			for (j = i; j >= step; j -= step) {
				if (buf.GetAmountDebts() > unsortdata[j - step].GetAmountDebts()) {
					unsortdata[j] = unsortdata[j - step];
				}
				else if (buf.GetAmountDebts() == unsortdata[j - step].GetAmountDebts()) {
					if (buf.GetArithmeticMean() < unsortdata[j - step].GetArithmeticMean()) unsortdata[j] = unsortdata[j - step];
					else break;
				}
				else break;
						
			}
			unsortdata[j] = buf;
		}
	}
}

int main() {

	srand(time(0));
	int task = 99, ltask = 99, htask = 99, vtask = 99;
	int n = 10;
	int position;
	vector<string> data;
	vector<int> data_int;
	for (int i = 0; i < n; i++) {
		data.push_back("This data #" + to_string(i + 1));
		data_int.push_back(i + 1);
	}

	vector<int> data_heap{ 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	vector<Student> sr(10), s_bubble, s_choice, s_insert, s_shell;

	DoubleLinkedList<string> v(n, data);
	//DoubleLinkedList<int> v(n, data_int);

	Heap h(data_int);
	Student s(1);
	Sort es;

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
					try {
						cout << "The root of Heap : " << h.ExtractRoot() << endl;
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					break;
				case 7:
					cout << "Unsorted Data: ";
					for (int i : data_heap) {
						cout << i << " ";
					}cout << endl;
					h.RebuiltUnsortedData(data_heap, 0);
					h.Show(0);
					h.HeapSort(data_heap);					
					cout << "Sorted Data: ";
					for (int i : data_heap) {
						cout << i << " ";
					}cout << endl;
					break;
				case 8:
					h.ExtractSort(data_int);
					h.HeapSort(data_int);
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
				cout << setw(30) << left << "ExtractSort vs HeapSort " << " / Enter - 8" << endl;
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
		case 3:
			while (vtask != 0) {
				switch (vtask) {
				case 1:
					try {
						cout << "\n!-Enter Amount of Elem to Generate: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						s.GenerateXMLData(position);
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					break;
				case 2:
					try {
						cout << "\n!-Enter Amount of Elem to Read: ";
						cin >> position;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
						sr.resize(position);
						s.GetXMLData(sr);
						if (sr.size() < 500) s.SortInfo(sr);
					}
					catch (const char* err) {
						cerr << endl << err << endl;
					}
					break;
				case 3: {
					sr.resize(30);
					s.GetXMLData(sr);
					if (sr.size() < 31) s.SortInfo(sr);
					s_bubble = sr;
					s_choice = sr;
					s_insert = sr;
					s_shell = sr;

					auto bubble_s = chrono::high_resolution_clock::now();
					es.BubbleSort(s_bubble);
					auto bubble_e = chrono::high_resolution_clock::now();
					auto bubble_dir = chrono::duration_cast<chrono::milliseconds>(bubble_e - bubble_s);
					//s.SortInfo(s_bubble);

					auto choice_s = chrono::high_resolution_clock::now();
					es.ChoiceSort(s_choice);
					auto choice_e = chrono::high_resolution_clock::now();
					auto choice_dir = chrono::duration_cast<chrono::milliseconds>(choice_e - choice_s);
					//s.SortInfo(s_choice);

					auto insert_s = chrono::high_resolution_clock::now();
					es.InsertSort(s_insert);
					auto insert_e = chrono::high_resolution_clock::now();
					auto insert_dir = chrono::duration_cast<chrono::milliseconds>(insert_e - insert_s);
					//s.SortInfo(s_insert);

					auto shell_s = chrono::high_resolution_clock::now();
					es.ShellSort(s_shell);
					auto shell_e = chrono::high_resolution_clock::now();
					auto shell_dir = chrono::duration_cast<chrono::milliseconds>(shell_e - shell_s);
					//s.SortInfo(s_shell);

					auto sort_s = chrono::high_resolution_clock::now();
					h.HeapSort(sr);
					auto sort_e = chrono::high_resolution_clock::now();
					auto sort_dir = chrono::duration_cast<chrono::milliseconds>(sort_e - sort_s);
					cout << endl;
					if (sr.size() < 31) s.TaskSortInfo(sr);
					cout << "\n____________________Sorts vs Sorts____________________\n";
					cout << setw(30) << left << "Bubble sort takes: " << static_cast<float>(bubble_dir.count()) / 1000.0f << " sec" << endl;
					cout << setw(30) << left << "Choice sort takes: " << static_cast<float>(choice_dir.count()) / 1000.0f << " sec" << endl;
					cout << setw(30) << left << "Insert sort takes: " << static_cast<float>(insert_dir.count()) / 1000.0f << " sec" << endl;
					cout << setw(30) << left << "Shell sort takes: " << static_cast<float>(shell_dir.count()) / 1000.0f << " sec" << endl;
					cout << setw(30) << left << "Heap sort takes: " << static_cast<float>(sort_dir.count()) / 1000.0f << " sec" << endl;
					break;
				}
				case 4:
					for (int i = 0; i < sr.size(); i++) {
						sr[i].Show();
					}
					break;
				}
				cout << "\n________Work with Lab Task var 17________" << endl;
				cout << setw(30) << left << "Generate .xml file " << " / Enter - 1" << endl;
				cout << setw(30) << left << "Read .xml file " << " / Enter - 2" << endl;
				cout << setw(30) << left << "Sort Data " << " / Enter - 3" << endl;
				cout << setw(30) << left << "Show info " << " / Enter - 4" << endl;
				cout << setw(30) << left << "Back " << " / Enter - 0" << endl;
				if (vtask != 0) {
					try {
						cout << "\nChoose the Task: ";
						cin >> vtask;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw "Error: <Incorrect Input Data>";
						}
					}
					catch (const char* err) {
						cerr << endl << err << endl;
						vtask = 99;
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