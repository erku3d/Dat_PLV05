#include "list.h"
#include<cstdio>

List::List()
{
	head = 0;
	tail = 0;
	
	elementCount = 0;
	
	empty = true;
	
}


List::~List()
{
	
	while(head){
		
		node* tmp = head;
		head = head->next;
		
		delete tmp;	
	}
	
}



char List::pop(){
		
	char c = (char) 0;
	
	if(head){
		
		node* tmp = head;
		
		head = head->next;
		
		if(head){
			
			head->pred = 0;
		}
		else{
			
			tail = 0;
			empty = true;
		}
		
		c = tmp->c;
		
		delete tmp;
			
		elementCount--;	
	}	
	
	return c;
	
}

char List::pull(){
	
	char c = (char) 0;
	
	if(tail){
		
		node* tmp = tail;
		
		tail = tail->pred;
		
		if(!tail){
			empty = true;
			head = 0;
		}
		
		c = tmp->c;
		
		delete tmp;
		
		elementCount--;
	}
	
	return c;
	
}

void List::push(char c){
	
	node* n = new node;

	n->c = c;
	n->next = head;
	n->pred = 0;
		
	if(!head){
		tail = n;
		empty = false;
	}
	else
		head->pred = n;
	
	head = n;
	
	elementCount++;
	
}



void List::push(List* li){	
	
	int len;
	char *str = li->toString(len);
		
	len-=2; //->letztes Zeichen vor'\0' 
	
	while(len>=0){
		push(str[len]);
		len--;
	}
	
	delete[] str;
	
	/*
	//li ist danach leer!
	while(!li->isEmpty()){
		push(li->pull());
	}
	*/	
}


void List::append(List* li){
	
	char *str = li->toString();

	int len=0;
	
	while(str[len]){
		append(str[len]);
		len++;
	}
	
	delete[] str;
	
		
	/*
	//li ist danach leer!
	while(!li->isEmpty()){
		append(li->pop());
	}
	*/
}

void List::append(char c){
	
	if(!head){		
		push(c);		
	}
	else{
	
		node* n = new node;
		n->c = c;
		n->next = 0;		
		
		n->pred = tail;
		tail->next = n;
		tail = n;
		
		elementCount++;
	}
	
}

char* List::toString(){
	
	char* str = new char[elementCount+1];
		
	node* tmp = head;
	
	for(int i=0; i<elementCount && tmp; i++){
				
		str[i] = tmp->c;
		tmp = tmp->next;
	}
	
	str[elementCount] = '\0';
	
	return str;
}

char* List::toString(int &len){
	
	len = elementCount+1;
	
	return toString();
	
}

bool List::isEqual(List* li){
	
	if(li->getElementCount() != elementCount)
		return false;
	
	char* str1 = toString();
	char* str2 = li->toString();
	
	bool result = true;
	
	for(int i=0; i<elementCount; i++){
		
		if(str1[i] != str2[i]){
			result = false;
			break;
		}
	}

	delete str1;
	delete str2;
	
	return result;
	
}



