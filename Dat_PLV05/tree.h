
#ifndef TREE_H
#define TREE_H

#include"string.h"
#include<cstdio>

class Tree
{
	private:
		
		struct node{
			String* s;
			bool isLeaf;
			
			node* left;
			node* right;			
		};
		
		node* root;
		
		node* generateTree(char* str, int &pos);
		int isOperator(char c);
		
		void traversePostOrder(node* n, String* s);
		
	public:
		Tree();
		 ~Tree();
		 
		void generateTreeFromCharArray(char* str);
		char* ausgabePostorder();
	
	
	
};

#endif /* TREE_H */ 
