#include <iostream>
#include "../headers/Book.h"
using namespace std;

void Book::copy(const Book &book)
{
    this->title = book.title;
    this->author = book.author;
    this->ISBN = book.ISBN;
}
Book::Book()
{
    cout << endl;
    cout << "************************************" << endl;
    cout << "Enter the book title." << endl;
    getline(cin, this->title);
    cout << "Enter the author." << endl;
    getline(cin, this->author);
    cout << "Enter the ISBN." << endl;
    getline(cin, this->ISBN);
    cout << endl;
    cout << "************************************" << endl
         << endl;
}
Book::Book(string title, string author, string isbn)
{
    this->title = title;
    this->author = author;
    this->ISBN = isbn;
}
Book::Book(const Book &book) { copy(book); }
void Book::setTitle(string title) { this->title = title; }
void Book::setAuthor(string author) { this->author = author; }
void Book::setISBN(string ISBN) { this->ISBN = ISBN; }
string Book::getTitle() { return this->title; }
string Book::getAuthor() { return this->author; }
string Book::getISBN() { return this->ISBN; }
void Book::operator=(const Book &book) { copy(book); }
ostream &operator<<(ostream &os, const Book &book)
{
    os << "\tTitle: " << book.title << endl
       << "\tAuthor: " << book.author << endl
       << "\tISBN: " << book.ISBN << endl;
    return os;
}