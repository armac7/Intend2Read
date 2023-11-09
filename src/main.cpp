#include <iostream>
#include "../headers/Book.h"
#include "../headers/Stack.h"
using namespace std;

int menu(string);

int main() 
{
    int userChoice = 0;
    string name = "None Selected";
    while (userChoice != -1) 
    {
        userChoice = menu(name);
        switch(userChoice) 
        {
            case 1:
                // create stack
                break;
            case 2:
                // delete stack
                break;
            case 3:
                // print stack names
                break;
            case 4:
                // update active stack
                break;
            case 5:
                // load books from file
                break;
            case 6:
                // add book to stack
                break;
            case 7:
                // print stack titles
                break;
            case 8:
                // print stack top
                break;
            case 9:
                // remove book
                break;
            case -1:
                // quit
                break;
            default:
                cout << "Invalid Input." << endl << endl;
                userChoice = 0; 
                continue;
                break;
        }
    }
    return 0;
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

// Test Main
// int main() 
// {
//     Stack<Book*> test;
//     test.push();
//     cout << test.getName() << endl;
//     test.push();
//     test.push();
//     cout << test << endl;
//     test.pop();
//     cout << test << endl;
//     cout << *test.getTop() << endl; // does not work.

//     return 0;
// }