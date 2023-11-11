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
                first->data->destroyStack();
                delete first;
                first = temp;
            }
            first = nullptr;
            last = nullptr;
            temp = nullptr;
        }
        int getLength() {return length;}
        void insert(Type data)
        {
            // if no first item, insert at first.
            if (first == nullptr) 
            {
                first = new Node<Type>;
                first->data = data;
                first->link = nullptr;
                last = first;
            } 
            else // else insert where necessary
            {
                Node<Type> *current = first;
                while (current->link != nullptr) 
                    current = current->link;
                current->link = new Node<Type>;
                current = current->link;
                current->data = data;
                current->link = nullptr;
                last = current;
            }
            length++;
        }
        void remove(string name) // doesnt properly work. Gets rid of everything in the stack but not the stack itself.
        {
            Node<Type> *toRemove = search(name);
            // cout << "\tTo Remove: " << toRemove->data->getName() << endl; // debug
            if (toRemove == nullptr) // Case: not found
                cout << "Stack by the name \"" << name << "\" not found." << endl;
            else 
            {
                Node<Type> *current = first;
                if (current == toRemove) // Case: removing head node
                {
                    first = first->link;
                    toRemove->data->destroyStack(); // gets rid of every item in the stack
                    delete toRemove; // deletes the node
                    toRemove = nullptr; // sets pointer of node to null.
                }
                else // Case: everything else
                {
                    while (current->link != toRemove) // will get the item before the item needed removed.
                        current = current->link;
                    current->link = toRemove->link; // sets the link to the link of the item to be removed. (skips the item to be removed.)
                    toRemove->data->destroyStack(); // gets rid of every item in the stack
                    delete toRemove; // deletes the node
                    toRemove = nullptr; // sets pointer of node to null.
                    if (length == 1) first = current; // likewise for first.
                }
                length--;
                if (current->link == nullptr) last = current; // makes sure if the current is last, to set last to it.
            } 
        } // specific to Stack.
        Node<Type> *search(string name) 
        {
            Node<Type> *current = first;
            while (current != nullptr) 
            {
                if (current->data->getName() == name) return current;
                current = current->link;
            }
            return nullptr;
        }
        Node<Type> *front() 
        {
            assert(first != nullptr);
            return first;
        }
        Node<Type> *rear() 
        {
            assert(last != nullptr);
            return last;
        }
        friend ostream &operator<<(ostream &os, const LinkedList &ll) 
        {
            Node<Type> *current = ll.first;
            os << "Stacks:" << endl;
            while (current != nullptr) 
            {
                os << "\t" << current->data->getName() << endl;
                current = current->link;
            }
            current = nullptr;
            return os;
        }
};

#endif