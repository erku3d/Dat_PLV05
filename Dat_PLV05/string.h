
#ifndef STRING_H
#define STRING_H

#include "list.h"


class String : List
{	
	
	private:
		int count;
		
		int charToInt(char c);	
			
		
	public:
		String();
		~String();
		
		void addChar(char c){List::append(c);}
		void push(char c){List::push(c);}
		char* toString(){return List::toString();}
		
		int getLength(){return List::elementCount;}
		
		int toInt();
		
		void addString(String* s);
	
		
};

#endif /* STRING_H */ 
