#include "Book.h"

Book::Book(int catalog, int _shelf)
{
	// TODO: fix
}

bool Book::borrowBook()
{
	// TODO: fix. Use the following lines to print the output according to the relevant case
	// cout << "Error! The book " << catalogNumber << " is already borrowed!" << endl;
	// cout << "Successfully found the book " << catalogNumber << " on shelf " << shelf << " and borrowed it" << endl;
	return true;
}

bool Book::returnBook()
{
	// TODO: fix. Use the following lines to print the output according to the relevant case
	// cout << "Error! The book " << catalogNumber << " is not borrowed!" << endl;
	// cout << "Successfully returned the book " << catalogNumber << " to shelf " << shelf << endl;
	return true;
}

ostream& operator<<(ostream& os, Book b)
{
	os << "{" << b.catalogNumber << ", " << b.shelf << ", ";
	os << (b.available ? "available" : "borrowed") << "}";
	return os;
}

istream& operator>>(istream& is, Book& b)
{
	is >> b.catalogNumber >> b.shelf;
	return is;
}
