#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;



class List {
public:
	List() { head = NULL; };
	~List();
	struct node {//our pair of values
		char* key;	 //key
		char* value; //value
		node *ptrNext;  //ptrNext ptr
	};
	node* getHead() const;  //returns head
	int empty() const;	//check if empty
	void addHead(char* key, char* value);	//add head
	node* addElem(node* n, const char* key, const char* value); // add elem to listf
	void print(); 
private:
	node* head; 
};




class Parser {
public:
	Parser(); //Parser
	void printTable(); //table output
private:
	char *query();
	char *get();
	char *post();
	List list; //list
};



char* Parser::post() { //func returning our url if using POST method
	char* str = getenv("CONTENT_LENGTH");
	int size = atoi(str);
	char* url = new char[size + 1];
	fread(url, size, 1, stdin);
	url[size] = '\0';
	return url;
}


char* Parser::get() { //func returning our url if using GET method
	char* str = getenv("QUERY_STRING");
	int size = strlen(str);
	char* url = new char[size + 1];
	strcpy(url, str);
	return url;
}


char* Parser::query() { //method checking query
	char * method = getenv("REQUEST_METHOD");
	if (strcmp(method, "GET") == 0) //calls post func if value GET
		return get();
	if (strcmp(method, "POST") == 0) //calls post func if value POST
		return post();
}



char decode(const char* str) {	//decoder
	char a = *str;	//1st sym after %
	char b = *(str + 1);	//2nd sym after%
	char c; 
	if (isalpha(a)) {  //if 1st symbol NOT num
		c = (a - 'A' + 10) << 4;
	}
	else { //if 1st symbol num
		c = (a - '0') << 4;
	}
	if (isalpha(b)) {	//if 2nd symbol NOT num
		c += (b - 'A' + 10);
	}
	else {
		c += (b - '0');	//if 2nd symbol num
	}
	return c;
}




int main() {
	cout << "Content-type:text/html \n\n";
	Parser p;
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<title> Profile info</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	p.printTable();
	cout << "</body>\n";
	cout << "</html>\n";
	return 0;
}


Parser::Parser() {
	int i = 0;
	char value[100]; //value buffer
	char key[100];  //key buffer
	char* temp = key; //temporary variable
	char * str = query();
	
	while (str[i] != '\0' && list.empty()) {
		switch (str[i]) {
		case '=':
			*temp = '\0';
			temp = value;
			break;
		case '&':
			*temp = '\0';
			temp = key;
			list.addHead(key, value);
			break;
		case '+':
			*temp = ' ';
			temp++;
			break;
		case '%':
		{
			char c = decode(str + i + 1);
			*temp = c;
			temp++;
			i += 2;
			break;
		}
		default:
			*temp = str[i];
			temp++;
			break;
		}
		i++;

	}

	List::node* pointer =list.getHead();

	while (str[i] != '\0') {
		switch (str[i]) {
		case '=':
			*temp = '\0';
			temp = value;
			break;
		case '&':
			*temp = '\0';
			temp = key;
			pointer=list.addElem(pointer,key, value);
			break;
		case '+':
			*temp = ' ';
			temp++;
			break;
		case '%':
		{
			char c = decode(str + i + 1);
			*temp = c;
			temp++;
			i += 2;
			break;
		}
		default:
			
			*temp = str[i];
			temp++;
			break;
		}
		i++;
	}
	*temp = '\0';
	pointer = list.addElem(pointer, key, value);
	delete str;
}


List::~List()
{
	node* prev = head;
	node* current = prev->ptrNext;
	while (current != NULL) {
		delete prev;
		prev = current;
		current=current->ptrNext;
	}
}


List::node * List::getHead() const
{
	return head;
}


int List::empty() const
{
	return head==NULL;
}


void List::addHead(char * key, char * value)
{
	head = new node;
	head->key = new char(strlen(head->key) + 1);
	head->value = new char(strlen(head->value) + 1);
	head->key = strcpy(head->key, key);
	head->value = strcpy(head->value, value);
}



List::node* List::addElem(node* n, const char* key, const char* value) {//elem add to list ,returns ptrNext to know the inserting index
	n->ptrNext = new node;
	n = n->ptrNext;
	n->key = new char[strlen(key) + 1];
	n->value = new char[strlen(value) + 1];
	strcpy(n->key, key);
	strcpy(n->value, value);
	return n;
}



void List::print() {
	if (head == NULL)
		cout << "Is empty" << endl;
	else {
		node* current = head;
		while (current != NULL) {
			cout << current->key << "  " << current->value << endl;
			current = current->ptrNext;
		}
	}
}



void Parser::printTable()
{
	List::node* current=list.getHead();
	cout << "<table border=\"1\">\n";
	while(current!=NULL){
		cout << "<tr>\n";
		cout << "<td>\n";
		cout << current->key;
		cout << "</td>\n";
		cout << "<td>\n";
		cout << current->value;
		cout << "</td>\n";
		cout << "</tr\n";
		current=current->ptrNext;
	}
	cout << "</table>\n";
}
