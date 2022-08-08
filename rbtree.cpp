/*
  rbtree.cpp
  MISIS:M00734221
  File Created:3/04/2021
  File Updated:15/04/2021
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "menu.h"
#include "rbtree.h"


  
//initializes the node with empty string values and pointers to null
void RBTree::initializeDetails(NodePtr node, NodePtr parent) {
  node->title = " ";
  node->name = " ";
  node->ISBN = " ";
  node->quantity = " ";
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = 0;
}


//Main search funtion which takes in the pointer and the key to be searched and returns the deatils if found
NodePtr RBTree::searchTreeHelper(NodePtr node, std::string key) {
    //if blank input is entered by user
    if(key.empty()){
      std::cout<<"Empty string entered\nNot valid\n";
      found=2;
      return nullptr;
    }
    //if the key is not found
    if(node==nullptr)
    {   found=0;
        return nullptr;
    }
    //travesing and searching through the tree
    while(node){
      //if key is found show details
      if (key == node->title){
          found=1;
          std::cout<<"\n"<<node->title<<" is found\n";
          std::cout<<"\nDetails:\n\n ";
          std::cout<<"\t Book Title: "<<node->title;
          std::cout<<"\n\t Author: "<<node->name;
          std::cout<<"\n\t ISBN: "<<node->ISBN;
          std::cout<<"\n\t Quantity: "<<node->quantity<<"\n";
        return node;
       //if key is less than the pointer position 
      }else if (key < node->title) {
          return searchTreeHelper(node->left, key);
      }
      //if key is greater than the pointer position
      else if(key > node->title){
          return searchTreeHelper(node->right, key);
      }
    }
  return node;
}

//deletes the node present in the tree
void RBTree::deleteNodeHelper(NodePtr node, std::string key) {
  // find the node having the key
  NodePtr z = TNULL; //temp variable
  NodePtr x, y;
  while (node != TNULL) {
    if (node->title == key) {
      z = node;
    }

    if (node->title <= key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  if (z == TNULL) {
    std::cout << "Key not found in the tree" << std::endl;
    return;
  }

  y = z;
  int y_original_color = y->color;
  //if left child of the node is NULL
  if (z->left == TNULL) {
    x = z->right;
    //transplant the node with x
    TransplantTree(z, z->right);
    //if left child of the node is NULL
  } else if (z->right == TNULL) {
    x = z->left;
    //transplant the node with x
    TransplantTree(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      TransplantTree(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    TransplantTree(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0) {
    fixAfterDelete(x);
  }
  std::cout<<"Book deleted\n";
}

//Rotates the red-black tree after deletion to make sure the tree is balanced
void RBTree::fixAfterDelete(NodePtr x) {
  NodePtr s;
  while (x != root && x->color == 0) {
    //if x is the left child of its parent
    if (x == x->parent->left) {
      //assigning s to the right child of the parent x
      s = x->parent->right;
      //case 1
      // if s is red colored
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        leftRotate(x->parent);
        s = x->parent->right;
      }

      //case 2
      //if right and left child s is black
      if (s->left->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
      //case 3  
      //if right child is black
        if (s->right->color == 0) {
          s->left->color = 0;
          s->color = 1;
          rightRotate(s);
          s = x->parent->right;
        }
      //case 4
      //if none of these cases happen
        s->color = x->parent->color;
        x->parent->color = 0;
        s->right->color = 0;
        leftRotate(x->parent);
        x = root;
      }
    } else {
       //assigning s to the left child of the parent x
      s = x->parent->left;
      //case 1
      // if s is red colored      
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        rightRotate(x->parent);
        s = x->parent->left;
      }

      //case 2
      //if right and left child s is black
      if (s->right->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
        //case 3  
        //if right child is black
        if (s->left->color == 0) {
          s->right->color = 0;
          s->color = 1;
          leftRotate(s);
          s = x->parent->left;
        }
        //case 4
      //if none of these cases happen
        s->color = x->parent->color;
        x->parent->color = 0;
        s->left->color = 0;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  //changes color to black
  x->color = 0;
}

void RBTree::insert(Book *b) {
  //initializing node and pointers
  NodePtr node = new Node;
  node->parent = nullptr;
  node->title = b->getTitle();
  node->name = b->getAuthor();
  node->ISBN = b->getISBN();
  node->quantity = b->getQuantity();
  node->left = TNULL;
  node->right = TNULL;
  node->color = 1; // new node must be red

  
  NodePtr q = nullptr;
  NodePtr p = this->root;

  //Binary Search Insertion
  while (p != TNULL) {
   q =p;
    if (node->title <p->title) {
     p =p->left;
    } else {
     p =p->right;
    }
  }

  //q is parent of p
  node->parent = q;
  if (q == nullptr) {
    root = node;
  } else if (node->title <q->title) {
   q->left = node;
  } else {
   q->right = node;
  }

  //Return null if the current node is a root node.
  if (node->parent == nullptr){
    node->color = 0;
    return;
  }

  // Simply return if the grandparent is null
  if (node->parent->parent == nullptr) {
    return;
  }

  // Balance the tree
  fixAfterInsert(node);
}

// fix the red-black tree
void RBTree::fixAfterInsert(NodePtr k){
  NodePtr u;
  while (k->parent->color == 1) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left; // uncle
      if (u->color == 1) {
        // Case 1:
	//If the color of the grandparent of y is red

        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
         // Case 2:
	 //if the new node is the left child of the parent

          k = k->parent;
          rightRotate(k);
        }
        // Case 3:
	//If the new node is the right child of the parent

        k->parent->color = 0;
        k->parent->parent->color = 1;
        leftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right; // uncle

      if (u->color == 1) {
        // mirror case 1
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;	
      } else {
        if (k == k->parent->right) {
          // mirror case 2
          k = k->parent;
          leftRotate(k);
        }
        // mirror case 3
        k->parent->color = 0;
        k->parent->parent->color = 1;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root) {
      break;
    }
  }
  root->color = 0;
}

//This function replaces one pointer with another which 
//helps to transplant nodes in balancing the tree after deletion
void RBTree::TransplantTree(NodePtr u, NodePtr v){
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left){
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}


// search the tree for the key k
// and return the corresponding node
NodePtr RBTree::search(std::string k) {
  return searchTreeHelper(this->root, k);
}

// find the node with the minimum key
NodePtr RBTree::minimum(NodePtr node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

// find the node with the maximum key
NodePtr RBTree::maximum(NodePtr node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}


// rotate left at node x
void RBTree::leftRotate(NodePtr x) {
  NodePtr y = x->right;
  x->right = y->left;
  if (y->left != TNULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  //if parent of x is NULL then make y as the root
  if (x->parent == nullptr) {
    this->root = y;
  //if x is the left child of the node then made y as the left child of the node  
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
  //assigning y as the right child of the node  
    x->parent->right = y;
  }
  y->left = x;
  //making y as parent of x
  x->parent = y;
}

// rotate right at node x
void RBTree::rightRotate(NodePtr x) {
  NodePtr y = x->left;
  x->left = y->right;
  if (y->right != TNULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  //if parent of x is NULL then make y as the root
  if (x->parent == nullptr) {
    this->root = y;
  //if x is the right child of the node then made y as the right child of the node
  } else if (x == x->parent->right) {
    x->parent->right = y;
  //assigning y as the left child of the node  
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

// insert the key to the tree in its appropriate position
// and fix the tree

//function to get root of the red-black tree
NodePtr RBTree::getRoot(){
  return this->root;
}

// call function to deleteNodeHelper
void RBTree::deleteNode(std::string title) {
  deleteNodeHelper(this->root, title);
}

/*This function stores each string which is seaprated by a tab
and stores it in a vector for each line in the file*/
std::vector<std::string> StringDivider(std::string book_vb, 
      char separator){

  std::vector<std::string> words;
  std::stringstream ss(book_vb);
  // temp variable to hold each word in the std::string
  std::string str;
  while(getline(ss, str, separator)){
    // Put the std::string sentences into a vector
      words.push_back(str);
  }
  return words;
}
//Reads initial contents of the file and inserts to
// the data structre 
void RBTree::fileRead(std::string filename){
//Declaring book object and referencing it as a pointer  
Book b;
Book* book = &b;
std::ifstream f;
std::string sentences = " ";
f.open(filename, std::ios_base::in);
if(f.is_open()){
  while(f.good()){
    getline(f, sentences);
    std::vector<std::string> v = StringDivider(sentences,'\t');
    //sets as book object and insert the file contents to the data structure
    if(f.good()){  
      b.setDetails(v[0], v[1], v[2], v[3]);
      insert(book);
    }
  }  
f.close();
}
std::cout<<"\nFile inserted to the data structure\n"; 
}
//insert contents to the file and calls the insert function
// of red-black tree
void RBTree::insertToFile(std::string b_title,std::string b_author,std::string b_ph,std::string b_qty,std::string filename) {
    std::fstream f;
    Book b;
    // assigns book object
    b.setDetails(b_title,b_author,b_ph,b_qty);
    //inserts book object to red-black tree
    insert(&b);
    
    f.open(filename,std::ios_base::out|std::ios::app);
    
    f<<b_title<<'\t'<<b_author<<'\t'<<b_ph<<'\t'<<b_qty<<'\n';
    f.close();
}
//deletes book from file copying contents to a temporary 
// file and renaming to original file name
void RBTree::deleteFromFile(std::string name,std::string filename){
  std::string line;
  std::ifstream myfile;
  myfile.open(filename);
  std::ofstream temp;
  temp.open("temp.txt");
  //reads the line to be deleted
  while (getline(myfile, line))
  {
      if (line.substr(0, name.size()) != name)
          temp << line << std::endl;
  }
  
  myfile.close();
  temp.close();
  remove(filename.c_str());
  rename("temp.txt", filename.c_str());

}
