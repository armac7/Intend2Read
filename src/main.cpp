#include <iostream>
#include <fstream>
#include "../headers/Book.h"
#include "../headers/Node.h"
#include "../headers/Stack.h"
#include "../headers/LinkedList.h"
using namespace std;

int menu(string);
Node<Stack<Book *> *> *createStack(LinkedList<Stack<Book *> *> &);
void printStacks(LinkedList<Stack<Book *> *> &ll);
void deleteStack(LinkedList<Stack<Book *> *> &, Node<Stack<Book *> *> *&);
Node<Stack<Book *> *> *updateActiveStack(LinkedList<Stack<Book *> *> &, Node<Stack<Book *> *> *); // inefficient
Node<Stack<Book *> *> *updateActiveStack(LinkedList<Stack<Book *> *> &, string);
void printStackTitles(Node<Stack<Book *> *> *);
void printStackTop(Node<Stack<Book *> *> *);
void removeBook(Node<Stack<Book *> *> *);
void addBookFile(Node<Stack<Book *> *> *);
void addBook(Node<Stack<Book *> *> *);

int main()
{
    int userChoice = 0;
    LinkedList<Stack<Book *> *> stacks;
    Node<Stack<Book *> *> *activeStack = nullptr;
    string name = "None Selected";
    while (userChoice != -1)
    {
        if (activeStack == nullptr)
            name = "None Selected";
        else
            name = activeStack->data->getName();
        userChoice = menu(name);
        cin.ignore();
        switch (userChoice)
        {
        case 1:
            // create stack
            activeStack = createStack(stacks);
            break;
        case 2:
            // delete stack
            if (stacks.getLength() == 0)
            {
                cout << "No Intend2Read Stacks available." << endl
                     << endl;
                continue;
            }
            deleteStack(stacks, activeStack);
            cout << endl;
            break;
        case 3:
            // print stack names
            if (stacks.getLength() == 0)
            {
                cout << "No Intend2Read Stacks available." << endl
                     << endl;
                continue;
            }
            printStacks(stacks);
            cout << endl;
            break;
        case 4:
            // update active stack
            if (stacks.getLength() == 0)
            {
                cout << "***Select a Stack by Number:***" << endl
                     << "No Intend2Read Stacks available." << endl
                     << endl;
                continue;
            }
            activeStack = updateActiveStack(stacks, activeStack);
            break;
        case 5:
            // load books from file
            addBookFile(activeStack);
            cout << endl;
            break;
        case 6:
            // add book to stack
            addBook(activeStack);
            break;
        case 7:
            // print stack titles
            printStackTitles(activeStack);
            break;
        case 8:
            // print stack top
            printStackTop(activeStack);
            break;
        case 9:
            // remove book
            removeBook(activeStack);
            cout << endl;
            break;
        case -1:
            // quit
            break;
        default:
            cout << "Invalid Input." << endl
                 << endl;
            userChoice = 0;
            continue;
            break;
        }
    }
    return 0;
}

string getName(Node<Stack<Book *> *> *node) { return node->data->getName(); } // passes a copy, but passing reference causes error. Look into this.
Node<Stack<Book *> *> *createStack(LinkedList<Stack<Book *> *> &ll)           // creates a new stack and inserts it into the list.
{
    /**
     * @brief [Creates a new stack and inserts it to ll]
     * @param ll [A LinkedList of pointers to stack containing pointers to books.]
     */
    Stack<Book *> *newStack = new Stack<Book *>;

    if (ll.getLength() == 0) // if no stacks, just add a new one,
    {
        ll.insert(newStack);
    }
    else // if at least one book, make sure the stack name is unique.
    {
        Node<Stack<Book *> *> *current = ll.front();
        bool unique = true;
        while (current != nullptr)
        {
            if (current->data->getName() == newStack->getName()) // if another stack has the same name...
            {
                cout << endl;
                cout << "Cannot create a stack with the same name as another stack." << endl;
                unique = false;
                break;
            }
            else
                current = current->link;
        }
        if (unique)
        {
            ll.insert(newStack);
        }
    }
    return updateActiveStack(ll, newStack->getName());
}
void printStacks(LinkedList<Stack<Book *> *> &ll) { cout << ll; } // prints the name of each stack.
void deleteStack(LinkedList<Stack<Book *> *> &ll, Node<Stack<Book *> *> *&node)
{
    /**
     * @brief [Deletes stack by name specified by user.]
     * @param ll [A LinkedList of pointers to stack containing pointers to books.]
     * @param node [A node containing a pointer to a stack which contains pointers to books. Used to update the active node if it is deleted.]
     */
    // prints stacks and gets user input for which one to remove.
    int userChoice;
    cout << endl;
    cout << "***Select A Stack by Number to Delete:***" << endl;
    printStacks(ll);
    cin >> userChoice;

    // checks if user choice is in list, if so delete it from list.
    Node<Stack<Book *> *> *current = ll.search(userChoice);
    if (current == nullptr) // Case: Stack not found in search
        cout << endl
             << "Cannot remove list by name of \"" << userChoice << "\". List does not exist." << endl
             << endl;
    else // Case: Stack is found in search.
    {
        if (current == node)
            node = nullptr;
        ll.remove(userChoice);
        // if (getName(current) == getName(node)) node = nullptr;
        cout << "Stack " << userChoice << " has been deleted." << endl;
    }
    // return node;
}
Node<Stack<Book *> *> *updateActiveStack(LinkedList<Stack<Book *> *> &ll, string name) // updates the current active stack.
{
    /**
     * @brief [Updates the currently active stack with whatever choice the user wants, as long as it exists.]
     * @param ll [A LinkedList of pointers to stack containing pointers to books.]
     * @return [Returns a pointer to a node containing a pointer to a stack which contains pointers to books.]
     */
    bool valid = false;
    Node<Stack<Book *> *> *stack = nullptr;
    // gets user input for new stack.
    while (!valid)
    {
        // checks if user choice is found in list. If not, reset loop. If so, return the address of the node.
        stack = ll.search(name);
        if (stack == nullptr)
        {
            cout << "Invalid selection. No stack found named " << name << "." << endl;
            cout << endl;
            continue;
        }
        else
            valid = true;
    }
    return stack;
}
Node<Stack<Book *> *> *updateActiveStack(LinkedList<Stack<Book *> *> &ll, Node<Stack<Book *> *> *activeStack) // updates the current active stack.
{
    /**
     * @brief [Updates the currently active stack with whatever choice the user wants, as long as it exists.]
     * @param ll [A LinkedList of pointers to stack containing pointers to books.]
     * @return [Returns a pointer to a node containing a pointer to a stack which contains pointers to books.]
     */
    bool valid = false;
    Node<Stack<Book *> *> *stack = nullptr;
    // gets user input for new stack.
    while (!valid)
    {
        int userChoice = 0;
        cout << "***Select A Stack by Number:***" << endl;
        printStacks(ll);
        cout << "-1 to CANCEL." << endl;
        cin >> userChoice;

        // checks if user choice is found in list. If not, reset loop. If so, return the address of the node.
        if (userChoice == -1)
        {
            cout << "Active Stack NOT Updated." << endl;
            stack = activeStack;
            valid = true;
            break;
        }

        if (userChoice < 1 && userChoice > ll.getLength())
            continue;

        ll.search(userChoice);
        // checks if user choice is found in list. If not, reset loop. If so, return the address of the node.
        stack = ll.search(userChoice);
        if (stack == nullptr)
        {
            cout << "Invalid selection. No stack at position " << userChoice << "." << endl;
            cout << endl;
            continue;
        }
        else
            valid = true;
    }
    cout << endl;
    return stack;
}
void addBook(Node<Stack<Book *> *> *node)
{
    /**
     * @brief [Adds a book to the active node (node) as long as it exists.]
     * @param node [A pointer to a node pointing to a stack pointing to books.]
     */
    if (node == nullptr)
    {
        cout << endl;
        cout << "************************************" << endl;
        cout << "No stack selected to add to." << endl;
        cout << "************************************" << endl
             << endl;
    }
    else
        node->data->push();
}
void addBookFile(Node<Stack<Book *> *> *activeStack)
{
    if (activeStack == nullptr)
    {
        cout << endl;
        cout << "************************************" << endl;
        cout << "No stack selected to add to." << endl;
        cout << "************************************" << endl
             << endl;
    }
    else
    {
        string filename;
        string line;
        int index = 0;

        cout << "Which file do you want to read? ";
        getline(cin, filename);
        ifstream file(filename);
        if (!file.is_open())
            cout << "Failed to open file \"" << filename << "\"." << endl
                 << endl;
        else
        {
            string title;
            string author;
            string ISBN;
            while (getline(file, line))
            {
                if (index % 3 == 0)
                    title = line;
                else if (index % 3 == 1)
                    author = line;
                else if (index % 3 == 2)
                    ISBN = line;

                if (index % 3 == 2)
                    activeStack->data->push(title, author, ISBN);

                index++;
            }
        }
    }
}
void printStackTitles(Node<Stack<Book *> *> *node)
{
    /**
     * @brief [Prints the titles of all the books in the passed by node.]
     * @param node [A node containing a pointer to a stack containing pointers to books.]
     */
    if (node == nullptr)
        cout << "Stack is empty." << endl
             << endl;
    else if (node->data->getSize() == 0)
    {
        cout << "Titles for Stack: " << node->data->getName() << endl;
        cout << "Stack is empty." << endl
             << endl;
    }
    else
        cout << *node->data << endl;
}
void printStackTop(Node<Stack<Book *> *> *node)
{
    /**
     * @brief [Prints the top of the passed by node.]
     * @param node [A node containing a pointer to a stack containing pointers to books.]
     */
    if (node == nullptr)
    {
        cout << "Cannot print top book of an empty stack." << endl;
        cout << endl;
    }
    else if (node->data->getSize() == 0)
    {
        cout << "Cannot print top book of an empty stack." << endl;
        cout << endl;
    }
    else
    {
        cout << "Book on Top of " << node->data->getName() << " stack:" << endl;
        cout << *node->data->getTop()->data;
        cout << endl;
    }
}
void removeBook(Node<Stack<Book *> *> *node)
{
    /**
     * @brief [Removes a book so long as the node, passed as parameter, is not null.]
     * @param node [A node pointing to a stack pointing to books.]
     */
    if (node == nullptr)
    {
        cout << endl;
        cout << "************************************" << endl;
        cout << "Cannot remove from an empty stack." << endl;
        cout << "************************************" << endl
             << endl;
    }
    else if (node->data->getSize() == 0)
    {
        cout << endl;
        cout << "************************************" << endl;
        cout << "Cannot remove from an empty stack." << endl;
        cout << "************************************" << endl
             << endl;
    }
    else
        node->data->pop();
}

int menu(string name)
{
    cout << "Active Stack: " << name << endl;
    cout << "Make a Selection:" << endl;
    cout << "\t1. Create a Stack." << endl
         << "\t2. Delete a Stack." << endl
         << "\t3. Print Stack Names." << endl
         << "\t4. Update Active Stack" << endl;
    cout << "***Select for Active Stack: " << name << "***" << endl;
    cout << "\t5. Load Books From File" << endl
         << "\t6. Add Book to Stack" << endl
         << "\t7. Print Stack Titles" << endl
         << "\t8. Print Stack Top" << endl
         << "\t9. Remove Book" << endl
         << "\t-1. Quit" << endl;
    int userChoice;
    cin >> userChoice;
    return userChoice;
}