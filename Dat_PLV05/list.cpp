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

	
	while(!li->isEmpty()){
		push(li->pull());
	}
	
	
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




