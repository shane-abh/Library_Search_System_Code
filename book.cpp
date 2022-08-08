/*
  book.cpp
  MISIS:M00734221
  File Created:3/04/2021
  File Updated:15/04/2021
*/
#include <iostream>
#include <string>
#include "book.h"
//defines getter functions for the class variables
std::string Book::getTitle(){
     return title;
}

std::string Book::getAuthor(){
    return author;
}

std::string Book::getISBN(){
    return ISBN;
}

std::string Book::getQuantity(){
    return quantity;
}

//Assigns values to the class variables
void Book::setDetails(std::string title,std::string author,std::string ISBN,std::string quantity){
    this->title=title;
    this->author=author;
    this->ISBN=ISBN;
    this->quantity=quantity;
}