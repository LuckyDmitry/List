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
		T data; //���� ������
		Node* p_next; //��������� �� ����. �������
	};

	Node<T>* p_first; // ��������� �� ������ �������
	Node<T>* p_last; // ��������� �� ��������� �������
	int size_list;		//������ ������

	void show(Node<T>* current_element) {
		std::cout << current_element->data << ' ';
	}
public:
	List();
	~List();
	void push_back(T data);		//�������� ������� � �����
	void push_front(T data);		//�������� � ������ ������
	void print_all();	//����������� ��� ��������
	void pop_back();	//������� ��������� ������
	void pop_front();	//�������� ������� ��������
	void insert(const T data, int index);	//�������� ������� �� �������
	void remove(int index); //������� ������� �� ������
	void clear(); //������� ������
	bool check_empty() { if (p_first == NULL) return true; else return false; }//�������� ,���� �� �������� � ������
	bool find_item(T data);		//����� ������ � ������
	int get_length() { return size_list; }		//�������� ����� ������
	T& operator[](const int);		//���������� ��������� 
	void operator=(const List<T>& original);
	List<T>& get_poinet_head() { return p_first; }	//�������� ������ ���������

};

template<typename T>
List<T>::List()		//�����������
{
	p_first = NULL;
	p_last = NULL;
	size_list = 0;
}

template<typename T>
void List<T>::push_back(T data) {

	Node<T>* current_element = new Node<T>;		//������� ����� ���������
	current_element->data = data;			//�������� ���� ������
	size_list++;								//������� ���-�� ���������
	if (p_first == NULL) {					//��������� ���� �� �������� � ������
		p_first = current_element;			//��������� �� ������ ������� - �������
		p_last = current_element;			//��������� �� ��������� ������� - �������
		p_last->p_next = NULL;				//��������� ���������� ��������� �� �������� ��������� � �������

	}
	else {									//���� ���� ��������
		p_last->p_next = current_element;	//��������� ����������� �������� �� �������� = �������� ��������
		p_last = current_element;			//��������� ������ ����� ��������
		p_last->p_next = NULL;				//��������� ���������� �� �������� = �������
	}
}

template<typename T>
void List<T>::push_front(T data) {		//�������� ������� � ������ ������

	Node<T>* current_element = new Node<T>;		//������� ���������
	current_element->data = data;		//������� ������� = ������ ��������
	size_list++;		//������� �����������
	if (p_first == NULL) {		//���� ��������� ��� ,�� ������� �������
		p_first = current_element;
		p_last = current_element;
		p_last->p_next = NULL;
	}
	else {		//���� �������� ����
		current_element->p_next = p_first;		//��������� �� ����.������ �������� �������� = ������� ��������
		p_first = current_element;		//������ ������ ����� ��������
	}
}

template<typename T>
void List<T>::print_all() {
	Node<T>* temp = new Node<T>;		//������� ����� ��������� ��������
	temp = p_first;			//������������ ��������� �� ������ ������� ������
	while (temp != NULL) {		//���� ���� ������� �� ��������� �� �������
		show(temp);		//�������� ����� �������� ������ �������
		temp = temp->p_next;		//������������ ��������� �� �������� �������

	}
}

template<typename T>
void List<T>::pop_back() {
	Node<T>* current_element = p_first;		//������� ����� ���������
	Node<T>* p_previous = NULL;		//��������� �� ���������� ������� = �������
	size_list--;

	while (current_element != NULL) {		//���� ������� ������ �� �������
		if (current_element->p_next == NULL) {		//���� �������� ��������� = �������
			p_last = p_previous;		//���������� ��������� = ���������� ���������
			delete current_element;
			p_last->p_next = NULL;		//��������� ��������� �� �������� ������� = �������
			break;
		}
		p_previous = current_element;	//���������� ������� = �������
		current_element = current_element->p_next;	//������� = ���������
	}
}

template<typename T>
void List<T>::pop_front() {	//������� � ������

	Node<T>* current_element = p_first;
	p_first = current_element->p_next;//������ ������� ����� ����������

	delete current_element;//������� �������	
	size_list--;//������� ����� 1

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
void List<T>::clear() {//������� ������ ���������
	while (size_list) {
		pop_front();
	}
}

template<typename T>
List<T>::~List()//����������
{
	clear();
}

template<typename T>
T& List<T>::operator[](const int index) { //���������� ��������� ����������

	Node<T>* current_element = p_first;//��������� �� ������ �������
	int count = 0;	
	while (current_element != NULL)
	{
		if (count == index) {
			return current_element->data;	//������� ��� ������ � ���������� ������ �� ����
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

	// TODO: �������� ����� �������� return
}

template<typename T>
void List<T>::remove(int index) {		//������� ������� �� �������
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
bool List<T>::find_item(const T data) {//����� ������� 

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