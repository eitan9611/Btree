#include<iostream>
#include"Book.h"
#include"BTree.h"
#include"AVL.h"
#include"Library.h"

int main()
{
    string path, command;
    int degree, catalogNumber;
    cout << "Enter the path to the books database:\n";
    cin >> path;
    cout << "Enter the degree of the BTree:\n";
    cin >> degree;

    BTree<Book> bt(degree);
    AVL<Book> avl;
    Library newLibrary(path, bt);
    Library oldLibrary(path, avl);
    while (true) {
        cout << "Enter 'b' to borrow, 'r' to return, 'v' to validate structure or 'e' to quit:\n";
        cin >> command;

        if (command == "e") {
            break;
        }
        if (command == "b") {
            cout << "Enter catalog number:" << endl;
            cin >> catalogNumber;
            cout << "Trying to borrow book using the old data structure" << endl;
            oldLibrary.borrowBook(catalogNumber);
            cout << "Trying to borrow book using the new data structure" << endl;
            newLibrary.borrowBook(catalogNumber);
        }
        if (command == "r") {
            cout << "Enter catalog number:\n" << endl;
            cin >> catalogNumber;
            cout << "Trying to return book using the old data structure" << endl;
            oldLibrary.returnBook(catalogNumber);
            cout << "Trying to return book using the new data structure" << endl;
            newLibrary.returnBook(catalogNumber);
        }
        if (command == "v") {

            cout << "validating the old data structure" << endl;
            oldLibrary.validateDataStructure();
            cout << "validating the new data structure" << endl;
            newLibrary.validateDataStructure();
        }
    }

    return 0;
}