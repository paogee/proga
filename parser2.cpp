#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Parser {
public:
	Parser();
	string params;
private:
	int formGet(string &tmpStr);
	int formPost(string &tmpStr);
};
Parser::Parser()
{
	char *method = getenv("REQUEST_METHOD");
	if (strcmp("POST", method) == 0)
		formGet(params);
	else
		formPost(params);
}
int Parser::formGet(string &tmpStr)
{
	//char* data = "firstname=hrju&lastname=gav%20gav"; 
	char* data = getenv("QUERY_STRING");
	if (data == NULL) {
		return -1;
	}
	tmpStr = string(data);
	return 0;
}

int Parser::formPost(string &tmpStr)
{
	char* contentLength;
	int strLength;
	contentLength = getenv("CONTENT_LENGTH");
	if (contentLength == NULL)
		return -1;
	strLength = atoi(contentLength);
	if (strLength == 0)
		return -1;

	char* data = (char*)malloc(strLength + 1);
	if (data == NULL)
		return -1;
	if (fread(data, 1, strLength, stdin) == 0)
		return -1;
	*(data + strLength) = '\0';
	tmpStr = string(data);
	return 0;
}
class Data {
public:
	Data();
	struct Params {
		string key;
		string value;
		Params* next;
	};
	void push(string k, string v);
	void const print(); 
	Params* head;
};
void Data::push(string k, string v)
{
	Params* d = new Params();
	d->key = k;
	d->value = v;
	if (head == NULL)
		d->next = d;
	else
	{
		head->next = d;
		d->next = head;
	}
	head = d;
}
Data::Data(){
	head = NULL;
}
void const Data::print()
	{
		if (head != NULL)
		{
			Params* temp = head->next;
			while (temp != head)
			{
				cout << temp->key << " = " << temp->value << endl; 
				temp=temp->next;
			}
			cout << head->key << " = " << head->value << endl;			
		}
		else
			cout << "EMPTY" << endl;
	}
class Processor {
public:
	Processor(string &params);
	Data* data;
private:
	static string decode(string str);
};
string Processor::decode(string str)
{
	string temp;
	int i;
	char tmp[5], tmpchar;
	strcpy(tmp, "0x");
	int size = str.size();
	for (i = 0; i<size; i++) {
		if (str[i] == '%') {
			if (i + 2<size) {
				tmp[2] = str[i + 1];
				tmp[3] = str[i + 2];
				tmp[4] = '\0';
				tmpchar = (char)strtol(tmp, NULL, 0);
				temp += tmpchar;
				i += 2;
				continue;
			}
			else {
				break;
			}
		}
		else if (str[i] == '+') {
			temp += ' ';
		}
		else {
			temp += str[i];
		}
	}
	return temp;
}
Processor::Processor(string &params){
	string tmpkey, tmpvalue;
	string *tmpstr = &tmpkey;

	if (params == "") return;
	char* paramStr = &params[0];
	data = new Data();

	if (paramStr == NULL) {
		return;
	}
	while (*paramStr != '\0') {
		if (*paramStr == '&') {
			if (tmpkey != "") {
				data->push(decode(tmpkey), decode(tmpvalue));					
			}
			tmpkey = ""; 
			tmpvalue = ""; 
			tmpstr = &tmpkey;
		}
		else if (*paramStr == '=') {
			tmpstr = &tmpvalue;
		}
		else {
			(*tmpstr) += (*paramStr);
		}
		paramStr++;
	}
	
	if (tmpkey != "") { //last pair processing
		data->push(decode(tmpkey), decode(tmpvalue));		
		tmpkey = "";
		tmpvalue = "";
	}
}
int main()
{
	Parser parser = Parser();
	Processor proc = Processor(parser.params);
	
	cout << "Content-type: text/html" << endl << endl;;
	cout << "<html>" << endl;
	cout << "<head>" << endl;;
	cout << "<title> CGI Program - Form processing</title>" << endl;;
	cout << "</head>";
	cout << "<body> \n";
	cout << "<form method=\"get\" action=\"parser.cgi\">" << endl;
	cout << " <label for=\"fname\">First name: <input type=\"text\" name=\"fname\" id=\"fname\"></label><br>" << endl;
	cout << " <label for=\"lname\">Last name: <input type=\"text\" name=\"lname\" id=\"lname\"></label><br>" << endl;
	cout << " <input type=\"submit\" />" << endl;
	cout << "</form><br /><br />" << endl;

	cout << "Param string: " << parser.params << endl;
	cout << "Form data:" << endl;
	if (proc.data == NULL)
		cout << "No data specified" << endl;
	else
		proc.data->print();
	cout << "</body></html>" << endl;
	system("pause");
	return 0;

}
