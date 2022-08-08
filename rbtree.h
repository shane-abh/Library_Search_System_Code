/*
  rbtree.h
  MISIS:M00734221
  File Created:3/04/2021
  File Updated:15/04/2021
*/
#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "book.h"

// title structure that represents a node in the tree
struct Node {
	std::string title; // holds the key
	std::string name;
	std::string ISBN;
	std::string quantity;
	Node *parent; 
	Node *left; 
	Node *right;
	int color; // 1 -> Red, 0 -> Black
};
//Pointer of struct Node
typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
  NodePtr root;
	NodePtr TNULL;
  //function declarations
  void initializeDetails(NodePtr node, NodePtr parent);
  
  NodePtr searchTreeHelper(NodePtr node, std::string key);
  void fixAfterDelete(NodePtr x);
  void deleteNodeHelper(NodePtr node, std::string key);
  void insert(Book *b);
  void fixAfterInsert(NodePtr k);
  void TransplantTree(NodePtr u, NodePtr v);
  
public:
  //constructor
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

  int found; //variable to check if book is present in the file 

  NodePtr search(std::string k);
  NodePtr minimum(NodePtr node);
  NodePtr maximum(NodePtr node);
  void leftRotate(NodePtr x);
  void rightRotate(NodePtr x);
  NodePtr getRoot();
  void deleteNode(std::string title); 
  //file handling functions  
  void fileRead(std::string filename);
  void insertToFile(std::string b_title,std::string b_author,std::string b_isbn,std::string b_qty,std::string filename);
  void deleteFromFile(std::string name,std::string filename);
}; 

#endif