#include <iostream>
#include <string>
#include <list>

using namespace std;
template<typename T>
class List
{
	
private:

	template<typename T>
	struct Node {
		T data; //наши данные
		Node* p_next; //указатель на след. элемент
	};

	Node<T>* p_first; // указатель на первый элемент
	Node<T>* p_last; // указатель на последний элемент
	int size_list;		//размер списка

	void show(Node<T>* current_element) {
		std::cout << current_element->data << ' ';
	}
public:
	List();
	~List();
	void push_back(T data);		//добавить элемент в конец
	void push_front(T data);		//вставить в начало элемет
	void print_all();	//распечатать все элементы
	void pop_back();	//удалить последний элемет
	void pop_front();	//удаление первого элемента
	void insert(const T data, int index);	//вставить элемент по индексу
	void remove(int index); //удалить элемент по индксу
	void clear(); //очистка списка
	bool check_empty() { if (p_first == NULL) return true; else return false; }//проверка ,есть ли элементы в списке
	bool find_item(T data);		//найти элемет в списке
	int get_length() { return size_list; }		//получить длину списка
	T& operator[](const int);		//перегрузка оператора 
	void operator=(const List<T>& original);
	List<T>& get_poinet_head() { return p_first; }	//получить первый указатель

};

template<typename T>
List<T>::List()		//конструктор
{
	p_first = NULL;
	p_last = NULL;
	size_list = 0;
}

template<typename T>
void List<T>::push_back(T data) {

	Node<T>* current_element = new Node<T>;		//создаем новую структуру
	current_element->data = data;			//помещаем наши данные
	size_list++;								//счетчик кол-во элементов
	if (p_first == NULL) {					//проверяем есть ли элементы в списке
		p_first = current_element;			//указателю на первый элемент - текущий
		p_last = current_element;			//указателю на последний элемент - текущий
		p_last->p_next = NULL;				//указатель последнего эелемента на следущий указывает в пустоту

	}
	else {									//если есть элементы
		p_last->p_next = current_element;	//указателю предыдущего элемента на следущий = текущему элементу
		p_last = current_element;			//последний элемет равен текущему
		p_last->p_next = NULL;				//указатель последнего на следущий = пустота
	}
}

template<typename T>
void List<T>::push_front(T data) {		//добавить элемент в начало списка

	Node<T>* current_element = new Node<T>;		//создаем структуру
	current_element->data = data;		//текущей элемент = нашему значению
	size_list++;		//счетчик увеличиваем
	if (p_first == NULL) {		//если элементов нет ,то создаем сначала
		p_first = current_element;
		p_last = current_element;
		p_last->p_next = NULL;
	}
	else {		//если элементы есть
		current_element->p_next = p_first;		//указатель на след.элемет текущего элемента = первому элементу
		p_first = current_element;		//первый элемет равен текущему
	}
}

template<typename T>
void List<T>::print_all() {
	Node<T>* temp = new Node<T>;		//создаем новую структуру итератор
	temp = p_first;			//приравниваем указатель на первый элемент списка
	while (temp != NULL) {		//пока этот элемент не указывает на пустоту
		show(temp);		//вызываем метод показать данный элемент
		temp = temp->p_next;		//приравниваем указатель на следущий элемент

	}
}

template<typename T>
void List<T>::pop_back() {
	Node<T>* current_element = p_first;		//создаем новую структуру
	Node<T>* p_previous = NULL;		//указатель на предыдущий элемнет = пустота
	size_list--;

	while (current_element != NULL) {		//пока текущий элемет не пустота
		if (current_element->p_next == NULL) {		//если следущий указатель = пустота
			p_last = p_previous;		//последнему указателю = предыдущий указатель
			delete current_element;
			p_last->p_next = NULL;		//последний указатель на следущий элемент = пустота
			break;
		}
		p_previous = current_element;	//предыдущий элемент = текущий
		current_element = current_element->p_next;	//текущий = следующий
	}
}

template<typename T>
void List<T>::pop_front() {	//удалить в начале

	Node<T>* current_element = p_first;
	p_first = current_element->p_next;//первый элемент равен следующему

	delete current_element;//удаляем текущий	
	size_list--;//счетчик минус 1

}

template<typename T>
void List<T>::insert(const T data, int index) {
	Node<T>* current_element = new Node<T>;
	current_element->data = data;
	if (p_first == NULL) {
		push_front(data);
	}
	else {
		Node<T>* previous = p_first;
		for (int i = 1; i < index - 1 && previous->p_next!= NULL; ++i){
			previous = previous->p_next;
		}
		if (index == 0) {
			push_front(data);
		}
		else if (previous->p_next == NULL) {
			push_back(data);
		}
		else {
			current_element->p_next = previous->p_next;		
			previous->p_next = current_element;
			
		}
	}

}

template<typename T>
void List<T>::clear() {//очистка списка полностью
	while (size_list) {
		pop_front();
	}
}

template<typename T>
List<T>::~List()//деструктор
{
	clear();
}

template<typename T>
T& List<T>::operator[](const int index) { //перегрузка оператора индексации

	Node<T>* current_element = p_first;//указатель на первый элемент
	int count = 0;	
	while (current_element != NULL)
	{
		if (count == index) {
			return current_element->data;	//находим наш индекс и возвращаем ссылку на него
		}
		current_element = current_element->p_next;
		count++;
	}
}

template<typename T>
void List<T>::operator=(const List<T> &original)
{
	Node<T>* current = original.p_first;
	while (current!= NULL ){
		this->push_back(current->data);
		current = current->p_next;
	}

	// TODO: вставьте здесь оператор return
}

template<typename T>
void List<T>::remove(int index) {		//удалить элемент по индексу
	Node<T>* current_element = p_first;
	Node<T>* previous = p_first;
	size_list--;
	for (int i = 0; i < index&& current_element->p_next!=NULL; ++i) {
		current_element = current_element->p_next;
	}
	if (index == 0) {
		pop_front();
	}
	else if(current_element == NULL) {
		pop_back();
	}
	else {
		while (previous->p_next!= current_element){
			previous = previous->p_next;
		}
		previous->p_next = current_element->p_next;
		delete current_element;
		current_element = previous;
	}
}

template<typename T>
bool List<T>::find_item(const T data) {//поиск элемета 

	Node<T>* current_element = p_first;
	while (current_element != NULL) {
		if (current_element->data == data) {
			return true;
		}
		current_element = current_element->p_next;
	}
	return false;
}

int main() {

	List<int> a;
	a.push_back(4);
	a.push_back(2);
	a.push_back(1);
	List<int> b;
	b = a;
	b.print_all();
	b.pop_back();
	b.print_all();
	a.print_all();



	return 0;
}