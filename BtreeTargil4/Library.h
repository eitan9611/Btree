#pragma once
#include "BTree.h"
#include "Book.h"
#include "LibraryDataStructure.h"
#include <fstream>
#include <iostream>

using namespace std;

class Library
{
private:
    LibraryDataStructure<Book>& ds;

public:
    Library(string path, LibraryDataStructure<Book>& _ds);
    bool borrowBook(int catalogNumber);
    bool returnBook(int catalogNumber);
    void validateDataStructure();
};
