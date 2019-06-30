#include <iostream>
using namespace std;
struct Node {
	int info;
	Node* next;
	Node(int data){ info = data; next = NULL; }
	Node(int data, Node* n){ info = data; next = n; }
};
class List{
public:
	List() { head = NULL; }
	~List() {};
	void push(int val);
	void pushBack(int i);
	bool isPresent(int i)const;		
	void print();
		
	List& operator+= (const List &list2); //as concatenation
	List& operator-= (const List &list2); //as difference
	List& operator&= (const List &list2); //as intersaction
//
	//List* Concatenation(const List *list1, const List *list2);
	//List* Intersection(const List  *list2);
	//List* Difference(const List *list2);
private:
	Node* head;
};

void List::push(int info)
{
	/* allocate node */
	Node* newNode = new Node(info, head );

	/* put in the data */
	//newNode->info = info;

	/* link the old list off the new node */
	//newNode->next = head;

	/* move the head to point to the new node */
	head = newNode;
}
void List::pushBack(int i)
{
	Node* newNode = new Node(i);
	Node* last = head;
	
	/* If  List is empty,
	then make the new node as head */
	if (head == NULL)
	{
		head = newNode;
		return;
	}

	/* Else traverse till the last node */
	while (last->next != NULL)
	{
		if (last->info == i) //check if value already exists
			return;
		last = last->next;
	}
	/* Change the next of last node */
	last->next = newNode;
	return;
}
bool List::isPresent(int info)const
{
	Node* l = head;
	while (l != NULL)
	{
		if (l->info == info)
			return 1;
		l = l->next;
	}
	return 0;
}

void List::print()
{
	Node* head = this->head;
	if (head == NULL) cout << "empty";
	while (head != NULL)
	{
		cout << head->info << " ";
		head = head->next;
	}
	cout << endl;
}
//List* List::Concatenation(const List *list1, const List *list2)
//{
//	List *result = NULL;
//	Node *l1 = list1->head, *l2 = list2->head;
//
//	// Insert all elements of list1 to the result list 
//	while (l1 != NULL)
//	{
//		pushBack(l1->info);
//		l1 = l1->next;
//	}
//
//	// Insert those elements of list2 which are not 
//	// present in result list 
//	while (l2 != NULL)
//	{
//		if (!isPresent(l2->info))
//			pushBack(l2->info);
//		l2 = l2->next;
//	}
//
//	return this;
//}
List& List::operator += (const List &list2) //Concatenation
{	
	Node *l2 = list2.head;

	while (l2 != NULL)
	{		
		pushBack(l2->info);
		l2 = l2->next;
	}

	return *this;
}
//List* List::Intersection(const List *list2)
//{	
//	Node* l1 = this->head;	
//	int i;	
//	while (l1 != NULL)
//	{
//		i = l1->info;
//		l1 = l1->next;
//		if (!list2->isPresent(i))	
//		erase(i);	
//	}
//	return this;
//}
List& List::operator&= (const List &list2) //Intersection
{
	Node* l1 = head;
	Node* prev = NULL;
	int i;
	while (l1 != NULL)
	{
		i = l1->info;
		if (list2.isPresent(i))
			prev = l1;
		else
			prev->next = l1->next;
		l1 = l1->next;
	}
	return *this;
}
//List* List::Difference(const List *list2)
//{	
//	Node* l1 = this->head;
//	int i;
//	while (l1 != NULL)
//	{
//		i = l1->info;
//		l1 = l1->next;
//		if (list2->isPresent(i))
//		erase(i);
//	}
//	return this;
//}
List& List::operator-= (const List &list2)//Difference
{	
	/*Node* l1 = head;
	int i;
	while (l1 != NULL)
	{
		i = l1->info;
		l1 = l1->next;
		if (list2.isPresent(i))
		erase(i);
	}
	return *this;*/
	Node* l1 = head;
	Node* prev = NULL;
	int i;
	while (l1 != NULL)
	{
		i = l1->info;
		if (list2.isPresent(i))
			prev->next = l1->next; 
		else
			prev = l1;
		l1 = l1->next;
	}
	return *this;
}


int main(int argc, char** argv) {
	List* list1 = new List();
	List* list2 = new List();

	list1->push(3);
	list1->push(2);
	list1->push(1);
	cout << "First: ";
	list1->print();


	list2->push(1);
	list2->push(4);
	list2->push(5);
	cout << "Second: ";
	list2->print();

	cout << "Concatenation: ";
	*list1+=*list2;
	list1->print();
	cout << "First: ";
	list1->print();
	cout << "Second: ";
	list2->print();
	cout << "Intersection: ";
	*list1&=*list2;
	list1->print();

	list1->push(7);
	cout << "First: ";
	list1->print();
	cout << "Second: ";
	list2->print();
	cout << "Difference: ";
	*list1-=*list2;
	list1->print();
	
	system("pause");

	return 0;
}
//работать с указателями посредством чего экономить время
