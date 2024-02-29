#pragma once
#include<iostream>
using namespace std;
class Book
{
private:
	int catalogNumber;
	int shelf;
	bool available;
public:
	int getKey() { return catalogNumber; }
	Book(int catalog = 0, int _self = 0);
	bool borrowBook(int wantedCatalogNumber);///////
	bool returnBook();////////////
	bool operator<(Book b) { if (catalogNumber < b.catalogNumber)return true; else return false; } 
	bool operator>(Book b) { if (catalogNumber > b.catalogNumber)return true; else return false; } 
	bool operator<=(Book b) { if (catalogNumber <= b.catalogNumber)return true; else return false; } 
	bool operator==(Book b) { if (catalogNumber == b.catalogNumber)return true; else return false; } 
	bool operator!=(Book b) { if (catalogNumber != b.catalogNumber)return true; else return false; } 
	friend ostream& operator<<(ostream& os, Book b);
	friend istream& operator>>(istream& is, Book& b);
};

