#ifndef LIST_H
#define LIST_H

class List
{
	public: struct node{
			char c;
			node *next;
			node *pred;
		};
		
	protected:
				
		node* head;  //Anfang und
		node* tail;	 //Ende der Liste
		
		int elementCount;  //Anzahl der Elemente
		
		bool empty;  // Ist die Liste leer?
	
	public: 
		
		List();
		~List();	
				
		bool isEmpty(){return empty;} 
		
		char* toString(); //Ausgabe der Liste als Zeichenkette
		
		char pop(); 			//entferen Element vom Anfang Ende der Liste
		char pull();			//entferen Element vom Ende der Liste
		void push(char c);  	//am Anfang anfügen
		void push(List* li);	//Liste am Anfang anfügen
		void append(char c);	//am Ende anfügen
		
	
	};

#endif /* LIST_H */ 
