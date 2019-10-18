#include <iostream>
#include <map>

#ifndef __GETPOST_H__
#define __GETPOST_H__

#include <string.h> 
#include <string> 
#include <stdlib.h>
#include <map>
#include <new>

using namespace std;


std::string urlDecode(std::string str)
{
	std::string temp;
	register int i;
	char tmp[5], tmpchar;
	strcpy(tmp,"0x");
	int size = str.size();
	for (i=0; i<size; i++) {
		if (str[i]=='%') {
			if (i+2<size) {
				tmp[2]=str[i+1];
				tmp[3] = str[i+2];
				tmp[4] = '\0';
				tmpchar = (char)strtol(tmp,NULL,0);
				temp+=tmpchar;
				i += 2;
				continue;
			} else {
				break;
			}
		} else if (str[i]=='+') {
			temp+=' ';
		} else {
			temp+=str[i];
		}
	}
	return temp;
}

void initializeGet(std::map <std::string, std::string> &Get)
{
	std::string tmpkey, tmpvalue;
	std::string *tmpstr = &tmpkey;
	register char* raw_get = getenv("QUERY_STRING");
	if (raw_get==NULL) {
		Get.clear();
		return;
	}
	while (*raw_get != '\0') {
		if (*raw_get=='&') {
			if (tmpkey!="") {
				Get[urlDecode(tmpkey)] = urlDecode(tmpvalue);
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*raw_get=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*raw_get);
		}
		raw_get++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		Get[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		tmpkey.clear();
		tmpvalue.clear();
	}
}

void initializePost(std::map <std::string, std::string> &Post)
{
	std::string tmpkey, tmpvalue;
	std::string *tmpstr = &tmpkey;
	int content_length;
	register char *ibuffer;
	char *buffer = NULL;
	char *strlength = getenv("CONTENT_LENGTH");
	if (strlength == NULL) {
		Post.clear();
		return;
	}
	content_length = atoi(strlength);
	if (content_length == 0) {
		Post.clear();
		return;
	}
	
	try {
		buffer = new char[content_length*sizeof(char)];
	} catch (std::bad_alloc xa) {
		Post.clear();
		return;
	}
	if(fread(buffer, sizeof(char), content_length, stdin) != (unsigned int)content_length) {
		Post.clear();
		return;
	}
	*(buffer+content_length) = '\0';
	ibuffer = buffer;
	while (*ibuffer != '\0') {
		if (*ibuffer=='&') {
			if (tmpkey!="") {
				Post[urlDecode(tmpkey)] = urlDecode(tmpvalue);
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*ibuffer=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*ibuffer);
		}
		ibuffer++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		Post[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		tmpkey.clear();
		tmpvalue.clear();
	}
}

#endif /*__GETPOST_H__*/

int main()
{
	map<string,string> Get;
	initializeGet(Get); //notice that the variable is passed by reference!
	cout<<"Content-type: text/html"<<endl<<endl;
	cout<<"<html><body>"<<endl;
	cout<<"<h1>Processing forms</h1>"<<endl;
	cout<<"<form method=\"get\">"<<endl;
	cout<<" <label for=\"fname\">First name: </label>"<<endl;
	cout<<" <input type=\"text\" name=\"fname\" id=\"fname\"><br>"<<endl;
	cout<<" <label for=\"lname\">Last name: </label>"<<endl;
	cout<<" <input type=\"text\" name=\"lname\" id=\"lname\"><br>"<<endl;
	cout<<" <input type=\"submit\" />"<<endl;
	cout<<"</form><br /><br />"<<endl;

	if (Get.find("fname")!=Get.end() && Get.find("lname")!=Get.end()) {
		cout<<"Hello "<<Get["fname"]<<" "<<Get["lname"]<<" "
			"Would you like a glass of wine?"<<endl;
	} else {
		cout<<"Fill up the above from and then press submit"<<endl;
	}
	cout<<"</body></html>"<<endl;

	return 0;
}
