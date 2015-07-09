
#ifndef TREE_H
#define TREE_H

#include"list.h"
#include<cstdio>

class Tree
{
	private:
		
		struct treeNode{
			List* s;
			bool isLeaf;
			
			treeNode* left;
			treeNode* right;			
		};
		
		treeNode* root;
		
		treeNode* generateTree(char* str, int &pos);
		
		int isOperator(char c);
		
		void traversePostOrder(treeNode* n, List* s);
		void traversePraeOrder(treeNode* n, List* s);
		void generateExpression(treeNode* n, List* s);
		
		void deleteTree(treeNode* n);
		
		void optimizeTree(treeNode* n);
		
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
		char* ausgabePraeorder();
		char* ausgabeAusdruck();
		
		void optimieren();
	
};

#endif /* TREE_H */ 
