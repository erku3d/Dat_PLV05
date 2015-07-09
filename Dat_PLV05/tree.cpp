#include "tree.h"


Tree::Tree()
{
	root = 0;
}


Tree::~Tree()
{
	
} 

int Tree::isOperator(char c){
	
	switch(c){
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case ')': return 3;
		case '(': return 3;
		default : return 0;
	}
		
}


Tree::node* Tree::generateTree(char* str, int &pos){
	
	if(pos<0)
		return 0;
	
	node* n = 0;
		
	if(str[pos] == ')' && pos>0){  //erzeuge Teilbaum, falls Klammer auf
		pos--;
		
		n = new node;
	
		n->s     = 0;
		n->left  = 0;
		n->right = 0;
		
		n->right = generateTree(str, pos); //rechter Teilbaum
		
		//Operator
		n->s = new String();
		n->s->push(' ');		
		n->s->push(str[pos]);
		
		pos--;
		
		n->left = generateTree(str, pos); //Linker Teilbaum
		
		if(pos >= 0 && str[pos] == '('){ // schließende Klammer entfernen
			pos--;
		}
		
		return n;
			
	}
	/*
	if(str[pos] == '(' && pos>0){  //falls nach dem Operator '(' -> Vorzeichen
		
		if(str[pos+1] == '-'){  //bspw wird -2 zu 0-2
			n = new node;
			n->left  = 0;
			n->right = 0;
		
			n->s = new String();
			
			n->s->push('0');   
			
			return n;
		}
		pos--;
	}
	*/
	
	if(isOperator(str[pos]) == 0 && pos >= 0){ //falls Zahl oder Buchstabe
		
		//Blattknoten
		
		n = new node;
		n->left  = 0;
		n->right = 0;
		
		n->s = new String();
		n->s->push(' ');
			
		while(isOperator(str[pos]) == 0 && pos >=0 ){ 
			
			n->s->push(str[pos]);			
			pos--;
		}
		
		//Test auf Vorzeichen
		if(pos > 0 && str[pos] == '-'){
			if(isOperator(str[pos-1]) != 0){
				n->s->push(str[pos]);			
				pos--;
			}
		}
		
		if(pos == 0 && str[pos] == '-'){ //falls nur eine negative Zahl eingegeben wurde
			n->s->push(str[pos]);			
			pos--;
		}
		
		
	
		return n;
	}
		
	pos--;		
	return n;
	
}

void Tree::generateTreeFromCharArray(char* str){
	//erzeugt den Baum aus der übergegeben Zeichenkette
	
	int len = 0;
	
	while(str[len])
		len++;
	
	int pos = len-1;
		
	root = generateTree(str, pos);
	
}

void Tree::traversePostOrder(node* n, String* s){
	if(n){
		traversePostOrder(n->left,s);
		traversePostOrder(n->right,s);
				
		s->addString(n->s);
	}
}

char* Tree::ausgabePostorder(){
	
	String* tmp= new String();

	traversePostOrder(root, tmp);
	
	char* s = tmp->toString();
	
	delete tmp;
	
	return s;
}


