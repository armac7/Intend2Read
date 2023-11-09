#include <iostream>
#include <assert.h>
#include "../headers/Node.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename Type>
class LinkedList 
{
    private:
        Node<Type> *first;
        Node<Type> *last;
        int length;
    public:
        LinkedList() 
        {
            first = nullptr;
            last = nullptr;
            length = 0;
        }
        ~LinkedList() 
        {
            Node<Type> *temp = nullptr;
            while (first != nullptr) 
            {
                temp = first->link;
                delete first;
                first = temp;
            }
            first = nullptr;
            last = nullptr;
            temp = nullptr;
        }
        void insert(Type data)
        {
            if (first == nullptr) 
            {
                first = new Node<Type>;
                first->data = data;
                first->link = nullptr;
                last = first;
            } 
            else 
            {
                Node<Type> *current = first;
                while (current->link != nullptr) 
                {
                    current = current->link;
                }
                current->link = new Node<Type>;
                current = current->link;
                current->data = data;
                current->link = nullptr;
                last = current;
            }
            length++;
        }
        void remove(string name); // specific to Stack.
        Node<Type> *search();
        Node<Type> *front();
        Node<Type> *last();
        friend ostream &operator<<(ostream &os, const LinkedList &ll) 
        {
            Node<Type> *current = ll.first;
            while (current != nullptr) 
            {
                os << current->getName() << endl;
            }
            current = nullptr;
            return os;
        }
};

#endif