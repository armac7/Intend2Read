#include <iostream>
using namespace std;

#ifndef BOOK_H
#define BOOK_H

class Book
{
private:
    string title;
    string author;
    string ISBN;
    void copy(const Book &book);

public:
    Book();
    Book(string, string, string);
    Book(const Book &book);
    void setTitle(string title);
    void setAuthor(string author);
    void setISBN(string ISBN);
    string getTitle();
    string getAuthor();
    string getISBN();
    void operator=(const Book &book);
    friend ostream &operator<<(ostream &os, const Book &book);
};

#endif