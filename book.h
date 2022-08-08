/*
  book.h
  MISIS:M00734221
  File Created:3/04/2021
  File Updated:15/04/2021
*/
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>

//Book class to insert book objects into the data structure
class Book{
  std::string title;
  std::string author;
  std::string ISBN;
  std::string quantity;
  
  public:
  std::string getTitle();
  std::string getAuthor();
  std::string getISBN();
  std::string getQuantity();
  void setDetails(std::string title,std::string author,std::string ISBN,std::string quantity);
};

#endif