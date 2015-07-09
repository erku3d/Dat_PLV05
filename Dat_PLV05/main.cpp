#include<cstdio>
#include"list.h"
#include"tree.h"

int isOperator(char c){
	
	switch(c){
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		default : return 0;
	}
		
}

List* getNextOperand(const char* str, int &pos){
	//Liest eine Operanden von str
	//Klammert, falls Vorzeichen)
	
	List *tmp = new List();
	
	while(isOperator(str[pos]) == 0 && pos >=0 ){ //falls Zahl oder Buchstabe
		tmp->push(str[pos]);			
		pos--;
	}
	
	
	//pos Steht auf einenm Operator
	
	//Vorezeichen -> zwei aufeinanderfolgende Operatoren
	if(pos>0){
		if(isOperator(str[pos-1]) != 0){
			tmp->push(str[pos]);
			//tmp->append(')');
			//tmp->push('(');
			pos--;
		}
	}
	else if(pos == 0){ //bzw. Operator am Anfang der Zeichenkette
		if(isOperator(str[pos]) == 1){
			tmp->push(str[pos]);
			//tmp->append(')');
			//tmp->push('(');
			pos--;
		}
	}
	
	return tmp;
}


char* generateDyadicExpression(const char* str){
	
	List* expr = new List();  //liste für den geklammerten Ausdruck
							  //(jedes Zeichen ist ein Element)
							  
	//bestimme länge der Zeichenkette
	int len = 0;
	
	while(str[len])
		len++;
	
	
	int pos = len-1; //Zeichenkette wird von rechts nach links analysiert
	
	List* tmp,*tmp2;	
	
	while(pos >= 0 ){
		
		if(isOperator(str[pos]) == 0){
		
			tmp = getNextOperand(str,pos); //lies den nächsten Operanden (mit evtl. Vorzeichen)
			
			//pos steht jetzt vor dem Operanden -> auf einem Operator
			
			expr->push(tmp); //in Liste Einfügen
			
			delete tmp;
		}
				
		if(isOperator(str[pos]) == 1){ //Addition oder Subtraktion
			
			expr->append(')');
			expr->push(str[pos]);	
			
			pos--;
						
			tmp = getNextOperand(str,pos);		
												
			while(isOperator(str[pos]) == 2){ //Multiplikation
				
				//Multiplikation bindet stärker 
				//wird als eigenener Ausdruck in einer Liste (tmp) zusammengefasst 
				 
												
				tmp->append(')');
				tmp->push(str[pos]);
				
				pos--;
				
				tmp2 = getNextOperand(str,pos);
				
				tmp->push(tmp2);
				
				delete tmp2;
				
				tmp->push('(');
				
			}
						
			expr->push(tmp);
			
			delete tmp;
			
			expr->push('(');
			
		}
		
		while(isOperator(str[pos]) == 2 && pos >=0){ //Multiplikation
								
			expr->append(')');
			expr->push(str[pos]); //operator *
			
			pos--;
			
			tmp = getNextOperand(str,pos);
			
			expr->push(tmp);
		
			delete tmp;
			
			expr->push('(');
			
		}
		
	}
	
	char* result =  expr->toString(); 
	
	delete expr;
	
	return result;
}



int main(int argc, const char* argv[]){
	//2*3-a+6-b*0
	if(argc != 2){
		printf("Bitte geben sie genau einen ungeklammerten mathematischen Ausdruck (ohne Leerzeichen) ein!");
		return 0;
	}
	
	
	
	printf("\nEingabe:\n%s\n\n",argv[1]);
	
	char* s = generateDyadicExpression(argv[1]);
	
	printf("geklammerter dyadischer Ausdruck:\n%s\n\n",s);
	 
	
	Tree* t = new Tree();
	
	t->generateTreeFromCharArray(s);
	
	delete[] s;	
	
	s = t->ausgabePostorder();
		
	printf("Postorder:\n%s\n\n",s);
	
	delete[] s;
	
	t->optimieren();
	
	s = t->ausgabePraeorder();
		
	printf("optimierter Ausdrucksbaum in Präorder:\n%s\n\n",s);
	
	delete[] s;
		
	s = t->ausgabeAusdruck();
	
	printf("optimierter Ausdrucksbaums geklammert:\n%s\n\n",s);
	
	
	delete[] s;
	
		
	delete t;
	
	return 1;
}

