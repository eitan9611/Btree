#include "Book.h"

Book::Book(int catalog, int _shelf)
{
	catalogNumber = catalog;
	shelf = _shelf;
	available = true;
}

bool Book::borrowBook(int wantedCatalogNumber)
{
	if (!available)
	{
		cout << "Error! The book " << catalogNumber << " is already borrowed!" << endl;
		return false;
	}
	else
	{
		cout << "Successfully found the book " << catalogNumber << " on shelf " << shelf << " and borrowed it" << endl;
		return true;
	}
}

bool Book::returnBook()
{
	if (!available)
	{
		cout << "Error! The book " << catalogNumber << " is not borrowed!" << endl;
		return false;
	}
	else
	{
		cout << "Successfully returned the book " << catalogNumber << " to shelf " << shelf << endl;
		return true;
	}
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
