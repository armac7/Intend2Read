#include <iostream>
#include <assert.h>
using namespace std;

#ifndef STACK_H
#define STACK_H
template <typename Type>
class Stack
{
private:
    Node<Type> *top;
    Node<Type> *bottom;
    string name;
    int size;
    void copy(const Stack &stack)
    {
        // Node<Type> *copy = nullptr;
        // Node<Type> *current = stack.top;
        // name = stack.name;
        // size = stack.size;
        // while (current != nullptr)
        // {
        //     copy = new Node<Type>; // creates new node
        //     copy->data = current->data; // sets new node data equal to data of current node in the stack we are copying from.
        //     copy->link = nullptr; // since we want a new node, and not a shallow copy, do not copy current->link
        //     if (top == nullptr) top = copy; // if top is null, list is empty so set top to current copy
        //     if (copy->link = nullptr) bottom = copy; // if copy->link is null, copy is the last in the stack.
        //     copy = copy->link; // move to next in the copy stack.
        //     current = current->link; // move to the next in the current stack.
        // }
        // copy = nullptr; // not deleting copy or current because we don't want to delete from either stack.
        // current = nullptr;
    }

public:
    Stack()
    {
        top = nullptr;
        bottom = nullptr;
        cout << "Enter a name for your stack: ";
        getline(cin, this->name);
        cout << endl;
        size = 0;
    }
    Stack(const Stack &stack) { copy(stack); }
    ~Stack()
    {
        Node<Type> *temp = nullptr;
        while (top != nullptr)
        {
            temp = top->link;
            delete top;
            top = temp;
        }
        top = nullptr;
        bottom = nullptr;
        temp = nullptr;
    }
    void destroyStack()
    {
        Node<Type> *temp = top;
        while (top != nullptr)
        {
            temp = top->link;
            delete top;
            top = temp;
        }
        name = "null";
        size = 0;
        top = nullptr;
        bottom = nullptr;
        temp = nullptr;
    }
    void push() // specific for Book class
    {
        Node<Type> *newNode = new Node<Type>; // creates a new node of type.
        newNode->data = new Book;             // Book specific. Creates a book.
        newNode->link = top;                  // Sets the link to the current top.
        top = newNode;                        // Sets the new top to the new node.
        newNode = nullptr;                    // Prevents dangling pointer.
        size++;
    }
    void push(string title, string author, string ISBN) // specific for Book class
    {
        Node<Type> *newNode = new Node<Type>;          // creates a new node of type.
        newNode->data = new Book(title, author, ISBN); // Book specific. Creates a book.
        newNode->link = top;                           // Sets the link to the current top.
        top = newNode;                                 // Sets the new top to the new node.
        newNode = nullptr;                             // Prevents dangling pointer.
        size++;
    }
    void pop()
    {
        Node<Type> *temp = top->link;
        delete top;
        top = temp;
        temp = nullptr;
        size--;
    }
    Node<Type> *getTop() // does not work.
    {
        assert(top != nullptr);
        return top;
    }
    int getSize() { return this->size; }
    string getName() { return this->name; }
    void operator=(const Stack &stack) { copy(stack); }
    friend ostream &operator<<(ostream &os, const Stack &stack) // Book class specific.
    {
        os << "Titles for Stack: " << stack.name << endl;
        Node<Type> *current = stack.top;
        while (current != nullptr)
        {
            os << current->data->getTitle() << endl;
            current = current->link;
        }
        current = nullptr;
        return os;
    }
};
#endif