#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <iomanip>
#include <process.h>
#include "rbtree.h"
//#include "menu.h"
#include "catch.hpp"

RBTree rb;

bool check_number(std::string quantity) {
   for (int i = 0; i < quantity.length(); i++)
   if (isdigit(quantity[i]) == false)
      return false;
      return true;
}

std::string Caps_name(std::string name) {

	for (int x = 0; x < name.length(); x++)
	{
		if (x == 0)
		{
			name[x] = toupper(name[x]);
		}
		else if (name[x - 1] == ' ')
		{
			name[x] = toupper(name[x]);
		}
	}

	return name;
}
int searchTree(std::string s){
	rb.fileRead("test.txt");
	rb.search(s);
	if(rb.found==1)
	{   return 1;}
	else 
	{   std::cout<<"Book not found\n";
		return 0;
	}	
}
int insert(std::string title){
   	RBTree b;
      std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n     INSERT MENU     \n";
    std::cout<<"\n-------------------------------------\n";
   
    //searching if book is found in the file      
    b.search(title);
    //if book is found the rest of the details are entered 
    if(searchTree(title)==0)
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
            
      b.insertToFile(title,author,ISBN,quantity,"test.txt");
    }else if(b.found==1){
      std::cout<<"Book already in the file\n";
    }
    else
        std::cout<<"\n";
    std::cout<<"\n----------------------------------------\n";
  return 0;

}
int delete_test(std::string title){
  
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"\n     DELETE MENU     \n";
    std::cout<<"\n-------------------------------------\n";
    std::cout<<"Enter title of the book to be deleted:\n";
    //std::string title;
    //std::cin.ignore();
    //checks if user entered a black value
    /*while(getline(std::cin,title)){
      if(title.empty())
        std::cout<<"Title not valid\nEnter a proper title\n";
      else
        break;
    }*/
    if(searchTree(title)==1){	
    	std::cout<<"Are you sure you want to delete (y/n): ";
    	std::string choice;
    	getline(std::cin,choice);
    	if(choice=="y" ||choice=="Y"||choice=="yes"||choice=="YES")
    		{  //deletes node from the red-black tree
      		   rb.deleteNode(title);
      		   ///delete the line of information from the file
      		   rb.deleteFromFile(title,"test.txt");
   		 }
	}else{
     		std::cout<<"Book not found\n";
	}
    std::cout<<"\n----------------------------------------\n";
return 0;
}


TEST_CASE("SearchTree_testing" , "[testing]")
{
	REQUIRE(searchTree("Unix System Management")==1);
	REQUIRE(searchTree("Graph Databases")==1);
	REQUIRE(searchTree("Basic Fundamentals")==0);
}
TEST_CASE("Insert_testing" , "[test1]")
{
	REQUIRE(insert("SQL Injection Attacks and Defense")==0);
	REQUIRE(insert("Graph Databases")==0);
	REQUIRE(insert("Basic Fundamentals")==0);
}
TEST_CASE("Delete_testing" , "[test2]")
{
	REQUIRE(delete_test("Basic Fundamentals")==0);
	REQUIRE(delete_test("Life Lessons")==0);
	
}
TEST_CASE("Check_number" , "[test3]")
{
	REQUIRE(check_number("s")==false);
	REQUIRE(check_number("1")==true);
}
TEST_CASE("Check_Caps" , "[test4]")
{
	REQUIRE(Caps_name("alexander pachev")=="Alexander Pachev");
	REQUIRE(Caps_name("maxim lapan")=="Maxim Lapan");
	REQUIRE(Caps_name("matthew taylor")=="Matthew Taylor");
}