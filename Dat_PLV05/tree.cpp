#include "tree.h"


Tree::Tree()
{
	root = 0;
}


Tree::~Tree()
{
	deleteTree(root);
} 

void Tree::deleteTree(treeNode* n){
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


Tree::treeNode* Tree::generateTree(char* str, int &pos){

	if(str[pos] == ')' && pos>0){  //erzeuge Teilbaum, falls schließende Klammer 
		pos--;
		
		treeNode* n = new treeNode;
	
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
	else if(isOperator(str[pos]) == 0 && pos >= 0){ //falls Zahl oder Buchstabe
		
		//Blattknoten
		
		treeNode* n = new treeNode;
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
	else{
		printf("Fehlerhafte Eingabe!\n");
		pos--;
		return 0;
		
	}
}

void Tree::generateTreeFromCharArray(char* str){
	//erzeugt den Baum aus der übergegeben Zeichenkette
	
	int len = 0;
	
	while(str[len])
		len++;
	
	int pos = len-1;
		
	root = generateTree(str, pos);
	
}

void Tree::traversePostOrder(treeNode* n, List* s){
	if(n){
		traversePostOrder(n->left,s);
		traversePostOrder(n->right,s);
				
		s->append(n->s);
		s->append(' '); //Leerzeichen, um Vorzeichen von Operanden zu unterscheiden
	}
}

void Tree::traversePraeOrder(treeNode* n, List* s){
	if(n){
		s->append(n->s);
		s->append(' '); //Leerzeichen, um Vorzeichen von Operanden zu unterscheiden
		
		traversePraeOrder(n->left,s);
		traversePraeOrder(n->right,s);

	}
}

void Tree::generateExpression(treeNode* n, List* s){
	
	if(n){
		
		if(n->isLeaf){
			s->push(n->s);
			return;
		}
		
		s->push(')');
		generateExpression(n->right, s);
		s->push(n->s);
		generateExpression(n->left, s);
		s->push('(');

	}
	
}


char* Tree::ausgabePostorder(){
	
	List* tmp= new List();

	traversePostOrder(root, tmp);
	
	char* s = tmp->toString();
	
	delete tmp;
	
	return s;
}

char* Tree::ausgabePraeorder(){
	
	List* tmp= new List();

	traversePraeOrder(root, tmp);
	
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

char Tree::intToChar(int i){
	
	if(i>9)
		return '\0';
		
	
	return (char)((int)'0' + i);

}

List* Tree::intToList(int i){
	
	//umwandeln von Integer in Liste
	
	List* li = new List();
	
	int tmp;
	
	if(i == 0){
		li->push('0');
		return li;
	}
	
	//Test auf Vorzeichen
	bool neg = false;
	
	if(i<0){
		neg = true;
		i *= -1;
	}
	
	//Werte von rechts nach links Umwandeln
	while(i > 0){
		
		tmp = i % 10;
		
		li->push( intToChar(tmp) );
		
		i=i/10;	
	}
	
	//Vorzeichen hinzufügen
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
	

	char* str1 = v1->toString();
	char* str2 = v2->toString();
	char* str3 = op->toString();
	
	char oper = str3[0];
		
	//Testen, ob die Übergeben Operanden Zahlen sind 
	//(in val1 und val2 stehend diese dann drin)
	
	int val1,val2,erg;
	bool v1Number = isNumber(str1,val1);
	bool v2Number = isNumber(str2,val2);
	
	delete[] str1;
	delete[] str2;
	delete[] str3;
	
	//beide Operanten sind Zahlen
	if(v1Number && v2Number){
		
		switch(oper){
			case '+': erg = val1 + val2; break;
			case '-': erg = val1 - val2; break;
			case '*': erg = val1 * val2; break;
			default : ; //Fehler
		}
		
		//Ergebnis in Liste Umwandeln
		return intToList(erg);	
	}
	
	//Vereinfachung bei Multiplikation
	if(oper == '*'){
		
		//falls einer der Operanden 0
		if((v1Number && val1 == 0) || (v2Number && val2 == 0)){
						
			List* result = new List();
			result->push('0');
			
			return 	result;		
		}
		
		//falls einer der Operanden 1
		if(v1Number && val1 == 1){
			List* result = new List();
			result->push(v2);
			
			return 	result;	
		}
		
		if(v2Number && val2 == 1){
			List* result = new List();
			result->push(v1);
			
			return 	result;	
		}
		
		//falls einer der Operanden -1 -> Vorzeichenwechsel 
		//-1 * a = -a
		if(v1Number && val1 == -1){
			
			List* result = new List();
			
			char vz = v2->pop();  //entferne das erste Zeichen
			
			if(vz == '-'){		//Falls minus	
				result->push(v2);								
			}
			else{
				v2->push(vz);
				result->push(v2);
				result->push('-');
			}
						
			return 	result;	
		}
		
		if(v2Number && val2 == -1){ //-> a * -1 = -a
			
			List* result = new List();
			
			char vz = v1->pop();  //entferne das erste Zeichen
			
			if(vz == '-'){		//Falls minus	
				result->push(v1);								
			}
			else{
				v1->push(vz);
				result->push(v1);
				result->push('-');
			}
						
			return 	result;	
		}
	}
	
	//Vereinfachung bei Addition 
	if(oper == '+'){
		
		//falls einer der Operanden 0
		if(v1Number && val1 == 0){
			List* result = new List();
			result->push(v2);
			
			return 	result;	
		}
		
		if(v2Number && val2 == 0){
			List* result = new List();
			result->push(v1);
			
			return 	result;	
		}
		
		//-a + a = 0 
		if(!v1Number && !v2Number){
			
			char vz = v1->pop();  //entferne das erste Zeichen
			
			if(vz == '-'){
								
				if(v1->isEqual(v2)){  //falls beide Operanden gleich 
					List* result = new List();
					result->push('0');
				
					return 	result;	
				}
			}
				
			v1->push(vz);
			return 0;	
		}
	}
		
	//Vereinfachung bei Addition 
	if(oper == '-'){
		
		// 0 - Operand = -Opeand -> Vorzeichenwechsel
		if(v1Number && val1 == 0){  
			List* result = new List();
			
			char vz = v2->pop();  //entferne das erste Zeichen
			
			if(vz == '-'){		//Falls minus	
				result->push(v2);								
			}
			else{
				v2->push(vz);
				result->push(v2);
				result->push('-');
			}
						
			return 	result;	
		}
		
		//Operand - 0 = Operand
		if(v2Number && val2 == 0){
			List* result = new List();
			result->push(v2);
			
			return 	result;	
		}
		
		//a - a = 0 
		if(!v1Number && !v2Number){
			
			if(v1->isEqual(v2)){
				List* result = new List();
				result->push('0');
			
				return 	result;	
			}
		}
		
	}
	
	return 0;
	
}



void Tree::optimizeTree(treeNode* n){
	
	if(!n)
		return;
	
	//zu erst linken und rechten Teilbaum optimieren
	if(n->left && !(n->left->isLeaf))  //nur innere Knoten können optimiert werden
		optimizeTree(n->left);
	
	if(n->right && !(n->right->isLeaf))
		optimizeTree(n->right);
	
	//falls beide Teilbäume Blattknoten sind
	if(n->left && n->left->isLeaf && n->right && n->right->isLeaf){
		
				
		//Vereinfachen des Ausdrucks 
		List* result = simplify(n->left->s, n->right->s, n->s);
		
		//falls erfolgreich (Zusammenfassen zu einem Knoten möglich)
		if(result){		
				
			//linkes und rechtes Blatt löschen
			
			deleteTree(n->left);  
			deleteTree(n->right);
			
			n->left = 0;
			n->right = 0;
			
			//der Knoten ist jetzt selbst ein Blatt
			n->isLeaf = true;
			
			//alten Wert löschen und das Ergebnis zuweisen
			delete n->s;
			n->s=result;
		}
		else{
			
			char* val1 = n->left->s->toString();
			char* val2 = n->right->s->toString();
			
			char* op = n->s->toString();
			
			if(op[0]=='*'){ //-a * -b = a * b
				
				if(val1[0]=='-' && val2[0]=='-'){ 
					n->left->s->pop(); //vorzeichen entfernen
					n->right->s->pop();
				}
				
			}
			else if(op[0]=='-'){ //a--b = a + b
				if(val2[0]=='-'){
					n->right->s->pop();
					n->s->pop();
					n->s->push('+');
				}
			}
			
			delete[] val1;
			delete[] val2;
			delete[] op;
		}
			
	}
	return;
}


void Tree::optimieren(){
	optimizeTree(root);
}

char* Tree::ausgabeAusdruck(){
	
	List* tmp= new List();

	generateExpression(root, tmp);
	
	char* s = tmp->toString();
	
	delete tmp;
	
	return s;
}




