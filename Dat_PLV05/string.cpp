#include "string.h"



String::String() : List()
{
		count=0;
}

String::~String()
{
}


int String::charToInt(char c){
	
	return (int)c - (int)'0';
	
}

int String::toInt(){
	
	if(isEmpty())    //besser wäre Exception
		return 1000; //laut Aufgabenstellung Operanden im Intervall [–999, 999]
				     //sollte bei korrekter Eingabe nicht auftretten
	
	
	node* tmp = tail;
	
	int multi = 1;
	
	int result = 0;
	
	int x;
	
	while(tmp){
		
		if(tmp->c == '-'){
			result *= -1;
			break;
		}
			
		if(tmp->c == '+'){
			break;
		}		
		x = charToInt(tmp->c);
		
		result += x*multi;
		
		multi *= 10;
		
		tmp = tmp->pred;
				
		
	}
	
	return result;
	
}

void String::addString(String* s){
	char* tmp = s->toString();
	
	int pos = 0;
	
	while(tmp[pos]){
		addChar(tmp[pos]);
		pos++;
	}
	
	delete[] tmp;
}

