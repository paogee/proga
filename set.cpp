#include <iostream>
using namespace std;
struct Node {
	int info;
	Node* next;	
	Node(int data){ info = data; next = NULL; }
	Node(int data, Node* n){ info = data; next = n; }
};

	Node* Concatenation(Node *list1, Node *list2);
	Node* Intersection(Node *list1, Node *list2);
	Node* Difference(Node *list1, Node *list2);

//};
	
Node* isPresent(Node *n, int data)//check, if set contains data, if yes, return previous element to be used for delete, if needed
{
	
	Node* prev = n;
	while (n != NULL)
	{
		if (n->info == data)
			return prev;
		prev = n;
		n = n->next;
	}
	return NULL;
}

Node* push(Node *n, int data)
{
	Node* newNode = new Node(data, n);
	return newNode;
}

Node* pushBack(Node *n, int data)
{
	Node* newNode = new Node(data);	
	Node* last = n;

	if (n == NULL)
	{
		n = newNode;
		return n;
	}
	while (last->next != NULL)
	{
		if (last->info == data) //check if value already exists
			return n;
		last = last->next;
	}
	last->next = newNode;
	return n;
}

void print(Node *n)
{
	Node* head = n;
	if (head == NULL) cout << "empty";
	while (head != NULL)
	{
		cout << head->info << " ";
		head = head->next;
	}
	cout << endl;
}

Node* Concatenation(Node *list1, Node *list2) //Concatenation
{	
	
	Node *l2 = list2;
	
	while (l2 != NULL)
	{		
		pushBack(list1, l2->info);
		l2 = l2->next;
	}

	return list1;
}

Node* Intersection(Node *list1, Node *list2) //Intersection
{
	
	Node* l1 = list1;
	Node* prev = list1;

	while (l1 != NULL)
	{		
		if (isPresent(list2, l1->info) == NULL)
		{			
			if (l1 == list1)
				list1 = l1->next;
			prev->next = l1->next;
		}
		else
			prev = l1;
		l1 = l1->next;
	}
	return list1;
}

Node* Difference(Node *list1, Node *list2)
{		
	Node* l1 = list1;
	Node* prev = list1;
	//int i;
	while (l1 != NULL)
	{		
		if (isPresent(list2, l1->info) != NULL)
		{
			if (l1 == list1)
				list1 = l1->next;
			prev->next = l1->next;			
		}
		else
			prev = l1;
		l1 = l1->next;
	}
	return list1;
}


int main(int argc, char** argv) {
	Node* list1 = new Node(3);
	Node* list2 = new Node(1);
	
	list1 = push(list1,2);
	list1 = push(list1,1);
	cout << "First: ";
	print(list1);
	
	list2 = push(list2, 4);
	list2 = push(list2, 5);
	cout << "Second: ";
	print(list2);
	
	cout << "Concatenation: ";
	print(Concatenation(list1, list2));
	
	list1 = push(list1, 9);
	cout << "First: ";
	print(list1);
	cout << "Second: ";
	print(list2);
	cout << "Intersection: ";
	print(Intersection(list1, list2));
	
	list1 = pushBack(list1, 8);
	list1 = pushBack(list1, 6);	
	cout << "First: ";
	print(list1);
	cout << "Second: ";
	print(list2);
	cout << "Difference: ";
	print(Difference(list1, list2));
		
	system("pause");

	return 0;
}
