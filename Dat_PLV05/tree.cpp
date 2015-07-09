#include "tree.h"


Tree::Tree()
{
	root = 0;
}


Tree::~Tree()
{
	deleteTree(root);
} 

void Tree::deleteTree(node* n){
	//löschen von n und aller Kinder von n
	
	if(n){
		
		if(n->left)
			deleteTree(n->left);
	
		if(n->right)	
			deleteTree(n->right);
		
		if(n->s)
			delete n->s;
			
		delete n;		
	}
	
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
	
	node* n = 0;
		
	if(pos<0)
		return n;
		
	if(str[pos] == ')' && pos>0){  //erzeuge Teilbaum, falls schließende Klammer 
		pos--;
		
		n = new node;
	
		n->s     = 0;
		n->left  = 0;
		n->right = 0;
		n->isLeaf = false; // Operatoren sind keine Blattknoten
		
		n->right = generateTree(str, pos); //rechter Teilbaum
		
		//Operator
		n->s = new List();
		n->s->push(str[pos]);
		
		pos--;
		
		n->left = generateTree(str, pos); //Linker Teilbaum
		
		if(pos >= 0 && str[pos] == '(') // öffnende Klammer überspringen
			pos--;
		
		
		return n;
			
	}
		
	if(isOperator(str[pos]) == 0 && pos >= 0){ //falls Zahl oder Buchstabe
		
		//Blattknoten
		
		n = new node;
		n->left  = 0;
		n->right = 0;
		n->isLeaf = true;
		
		n->s = new List();
			
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

void Tree::traversePostOrder(node* n, List* s){
	if(n){
		traversePostOrder(n->left,s);
		traversePostOrder(n->right,s);
				
		s->append(n->s);
		s->append(' '); //Leerzeichen, um Vorzeichen von Operanden zu unterscheiden
	}
}

char* Tree::ausgabePostorder(){
	
	List* tmp= new List();

	traversePostOrder(root, tmp);
	
	char* s = tmp->toString();
	
	delete tmp;
	
	return s;
}

int Tree::charToInt(char c){
	
	if( (int)c >= (int)'0' && (int)c <= (int)'9' )
		return (int)c - (int)'0';
	else
		return -1;
}

char c Tree::intToChar(int i){
	
	if(i>9)
		return '\0'
		
	
	return (char)((int)'0' + i);

}

List* intToList(int i){
	
	List* li = new List();
	
	int tmp;
	
	if(i == 0){
		li->push('0');
		return li;
	}
	
	bool neg = false;
	if(i<0){
		neg = true;
		i *= -1;
	}
	
	while(i > 0){
		
		tmp = i % 10;
		
		li->push(intToChar(tmp));
		
		i=i/10;	
	}
	
	if(neg)
		li->push('-');
	
	return li;	
}


bool Tree::isNumber(char* str, int& value){
	
	//übergebene Zeichenkette enthält nur Operaden (ggf. mit Vorzeichen)
	
	int len = 0;
	value = 0;
	
	//länge der Zeichenkette ohne '\0'
	while(str[len])
		len++;
		
	len--; 
	
	//prüfen auf Vorzeichen
	int pos = 0;
	
	bool neg = false;
	
	if(str[pos] == '-'){
		neg = true;
		pos++;

	}
	
	//Prüfen, ob erstes Element (nach dem Vorzeichen) eine Zahl ist		
	if(charToInt(str[pos]) == -1 ) //keine Zahl 
		return false; 
	
	//Erzeugung der Zahl
	
	int mul = 1; 
	int tmp;
	
	while(len >= pos){
		tmp = charToInt(str[len]);
		
		if(tmp == -1) //Kombinationen aus Zahlen und Buchstaben dürfen nicht vorkommen, bspw. a9 oder 9a
				return false;
		
		value += tmp*mul;
		mul *= 10;	
		
		len--;	
	}
	
	if(neg)
		value = value * -1;
	
	return true;
	
}


List* Tree::simplify(List* v1, List* v2, List* op){	
	
	
	List* result = 0;

	char* str1 = v1->toString();
	char* str2 = v2->toString();
	char* str3 = op->toString();
	
	char oper = str3[0];
	
	printf("simpl: |%s| |%s| \n",str1,str2);
	
	//Testen, ob die Übergeben Operanden Zahlen sind 
	//(in val1 und val2 stehend diese dann drin)
	
	int val1,val2,erg;
	bool v1Number = isNumber(str1,val1);
	bool v2Number = isNumber(str2,val2);
	
	if(v1Number && v2Number){
		
		switch(oper){
			case '+': erg = val1 + val2; break;
			case '-': erg = val1 - val2; break;
			case '*': erg = val1 - val2; break;
			default : ; //Fehler
		}
		
		//ergebniss in zeichenkette Umwandeln
		
		
	}
	
	
	delete str1,str2,str3;
	
	return result;
	
}



void Tree::optimizeTree(node* n){
	
	if(!n)
		return;
	
	//zu erst linken und rechten Teilbaum optimieren
	if(n->left && !(n->left->isLeaf))  //nur innere Knoten können optimiert werden
		optimizeTree(n->left);
	
	if(n->right && !(n->right->isLeaf))
		optimizeTree(n->right);
	
	//falls beide Teilbäume Blattknoten sind
	if(n->left && n->left->isLeaf && n->right && n->right->isLeaf){
		
		char* op = n->s->toString();
		char* val1 = n->left->s->toString();
		char* val2 = n->right->s->toString();
		
		printf("leaf: %s%s%s\n",val1,op,val2);
		
		delete op,val1,val2;
		
		//Vereinfachen des Ausdrucks
		List* result = simplify(n->left->s, n->right->s, n->s);
		
		//falls erfolgreich
		if(result){
			
			char* str = result->toString();
			printf("result: |%s|\n",str);
			delete str;
				
			//linker und rechte Blätter löschen
			
			deleteTree(n->left);  
			deleteTree(n->right);
			
			//der Knoten ist jetzt selbst ein Blatt
			n->isLeaf = true;
			
			//alten Wert löschen und das Ergebnis zuweisen
			delete n->s;
			n->s=result;
		}
	}
	return;
}


void Tree::optimieren(){
	optimizeTree(root);
}




