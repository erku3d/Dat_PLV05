
#ifndef TREE_H
#define TREE_H

#include"list.h"
#include<cstdio>

class Tree
{
	private:
		
		struct node{
			List* s;
			bool isLeaf;
			
			node* left;
			node* right;			
		};
		
		node* root;
		
		node* generateTree(char* str, int &pos);
		int isOperator(char c);
		
		void traversePostOrder(node* n, List* s);
		
		void deleteTree(node* n);
		
		void optimizeTree(node* n);
		
		List* simplify(List* v1, List* v2, List* op);
		
		int charToInt(char c);
		char intToChar(int i);
		bool isNumber(char* str, int& value);
		
		List* intToList(int i);
		
	public:
		Tree();
		 ~Tree();
		 
		void generateTreeFromCharArray(char* str);
		char* ausgabePostorder();
		
		void optimieren();
	
	
	
};

#endif /* TREE_H */ 
