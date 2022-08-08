/*
  menu.cpp
  MISIS:M00734221
  File Created:3/04/2021
  File Updated:15/04/2021
*/

#include <iostream>
#include <string>
#include <iomanip>
#include "rbtree.h"
#include "menu.h"


RBTree b;
std::string filename;
/*User interface for search which takes title
calls the search function of red-black tree*/ 
void search_menu(){
  
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n     SEARCH MENU     \n";
    std::cout<<"\n-------------------------------------\n"; 
    std::cout<<"Enter title of book to be searched: \n";
    std::string title;
    std::cin.ignore();
    getline(std::cin,title);
          
    b.search(title);
    if(b.found==0)
      std::cout<<"Book not found\n";
    std::cout<<"\n----------------------------------------\n";
    
}
/*User interface for inserting books into the file and red-black tree if book is not found in the tree */
void Insert_menu(){
  
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n     INSERT MENU     \n";
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n\nEnter new title of the book:\n ";
    std::string title;
    std::cin.ignore();
    getline(std::cin,title);
    //searching if book is found in the file      
    b.search(title);
    //if book is found the rest of the details are entered 
    if(b.found==0)
    {
      //Each input checks if the entered string is empty or not
      std::cout<<"\n\nEnter author of the book ("<<title<<"):\n";
      std::string author;
      while(getline(std::cin,author)){
        if(author.empty())
          std::cout<<"Author not valid\nEnter a proper name\n";
        else  
          break;
      }
      //converts inital alphabets to caps
      author = Caps_name(author);

      std::cout<<"\n\nEnter ISBN of the book ("<<title<<"):\n";
      std::string ISBN;
      while(getline(std::cin,ISBN)){
        if(ISBN.empty())
          std::cout<<"ISBN not valid\nEnter a proper value\n";
        //checks if input entered is a number  
        else if (check_number(ISBN) == false)
            std::cout<<"Enter an integer value"<<std::endl;
        else
          break;
      }

      std::cout<<"\n\nEnter quantity of the book ("<<title<<"):\n ";
      std::string quantity;
      while(getline(std::cin,quantity)){
        //checks if input entered is a number 
        if (check_number(quantity))
            break;
        else
            std::cout<<"Enter an integer value"<<std::endl;
        }
            
      b.insertToFile(title,author,ISBN,quantity,filename);
    }else if(b.found==1){
      std::cout<<"Book already in the file\n";
    }
    else
        std::cout<<"\n";
    std::cout<<"\n----------------------------------------\n";
}
/*Provides a user interface to delete a book from the file and data structure*/
void delete_menu(){
  
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n     DELETE MENU     \n";
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"Enter title of the book to be deleted:\n";
    std::string title;
    std::cin.ignore();
    //checks if user entered a black value
    while(getline(std::cin,title)){
      if(title.empty())
        std::cout<<"Title not valid\nEnter a proper title\n";
      else
        break;
    }
    std::cout<<"Are you sure (y/n): ";
    std::string choice;
    getline(std::cin,choice);
    if(choice=="y" ||choice=="Y"||choice=="yes"||choice=="YES")
    {  //deletes node from the red-black tree
      b.deleteNode(title);
      //delete the line of information from the file
      b.deleteFromFile(title,filename);
    }     
    std::cout<<"\n----------------------------------------\n";
}

/*Provides the first user interface to choose which option they want and calls functions accordingly*/
void initial_page(){
  
  char choice;
  do{
  std::cout<<"\n------------------------------------------\n\n";
  std::cout<<"WELCOME TO LIBRARY MANAGEMENT SYSTEM\n";
  std::cout<<"\n------------------------------------------\n\n";
  
  std::cout<<"Operations On The File\n\n";
  std::cout<<"1. Search book (By Title)\n";
  std::cout<<"2. Insert book\n";
  std::cout<<"3. Remove book\n";
  std::cout<<"4. Exit\n";
  std::cout<<"Choose an option: ";
  std::cin>>choice;
  // Using switch case statements to handle functions calls depending on user input
  switch(choice){
      case '1': search_menu();
              break; 

      case '2':Insert_menu();
              break;
              
      
      case '3':delete_menu();
              break;

      case '4':std::cout<<"Exiting...\n";
               std::cout<<"\n\n THANK YOU \n\n";
               exit(0);
              break;

      default: std::cout<<"Invalid Choice\n";
                break;
  }
  }while(choice!=4);
}
//Checks if the entered string is a number
bool check_number(std::string quantity) {
  for (unsigned int i = 0; i < quantity.length(); i++)
  if (isdigit(quantity[i]) == false)
    return false;
  return true;
}
//Converts initial letter of a word to caps
std::string Caps_name(std::string name) {

  for (unsigned int x = 0; x < name.length(); x++)
  { //first letter of the string
    if (x == 0)
      name[x] = toupper(name[x]);
    //letter after space  
    else if (name[x - 1] == ' ')
      name[x] = toupper(name[x]);
  }

return name;
}
// main function where name of file is taken from command line
int main(int argc, char *argv[]){
  if (argc < 2) {
  //in case user forgets to enter file name  
  std::cout << "Enter filename alongside " << argv[0]
            << " <filename>\n";
  exit(1);
  }
  filename = argv[1];
  b.fileRead(filename);
  initial_page();
  
  return 0;
}
