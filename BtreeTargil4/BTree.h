#pragma once
#include<iostream>
#include "LibraryDataStructure.h"
using namespace std;

template<class T>
class BTree : public LibraryDataStructure<T>
{
private:
	class BNode
	{
	public:
		int m;		//max num of records in node +1
		T* records;
		BNode** sons;
		BNode* parent;
		int numOfRecords;
		int numOfSons;
		BNode(int _m);
		~BNode();
		bool isLeaf();
		void insert(T record);
		void remove(T record);
		void printKeys();
	};
	int m;
	BNode* root;

	void clear(BNode* current);
	void inorder(BNode* current);
	BNode* findAddNode(BNode* current, T record);
	void split(BNode* current);
	T* search(BNode* current, int key, int& counter);
public:
	BTree(int degree);
	~BTree();
	void inorder();
	void insert(T record);
	T* search(int key);


};
////////////////////////////////////////////////////////////////

template<class T>
BTree<T>::BNode::BNode(int _m)
{
	m = _m;
	records = new T[_m];
	sons = new BNode * [_m + 1];
	parent = new BNode;
	numOfRecords = 0;
	numOfSons = 0;
}

template<class T>
BTree<T>::BNode::~BNode()
{
	delete[] records;
	for (int i = 0; i < m; ++i) {
		delete sons[i]; // Assuming each element of sons was dynamically allocated
	}
	delete[] sons; // Delete the sons array
	delete parent;
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	if (numOfSons == 0)
		return true;
	return false;
}

template<class T>
void BTree<T>::BNode::insert(T record)
{
	records[numOfRecords + 1] = record;
	numOfRecords++;
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	for (int i = 0; i < numOfRecords; i++)
	{
		if (records[i] == record)
		{
			for (int j = i; j < numOfRecords-1; j++)//get all the continue of the array one place earlier and crush the record we want to delete
			{
				records[j] = records[j + 1];
			}
		}
	}
}

template<class T>
void BTree<T>::BNode::printKeys()
{
	cout << '(';
	for (int i = 0; i < numOfRecords - 1; i++)
		cout << records[i].getKey() << ",";
	cout << records[numOfRecords - 1].getKey() << ')' << endl;
}
//-----------------------------------------------------------------------------------------------------
//start of BTree:

template<class T>
BTree<T>::BTree(int degree) :m(degree), root(nullptr)
{}

template<class T>
BTree<T>::~BTree()
{
	for (int i = 0; i < m; i++)
	{
		
	}
}
template<class T>
void BTree<T>::inorder()
{
	inorder(root);
}

template<class T>
void BTree<T>::insert(T record)
{
	// TODO: fix
}

//private recursive help fuctions
template<class T>
void BTree<T>::clear(BNode* current)
{
	if (current)
	{
		for (int i = 0; i < m; i++)
		{

		}
	}
}
template<class T>
void BTree<T>::inorder(BNode* current)
{
	int i;
	if (current != nullptr)
	{
		for (i = 0; i < current->numOfRecords; i++)
		{
			if( !current->isLeaf())
				inorder(current->sons[i]); //ran over the left node of of the current record 

			current->printKeys();// visit the node itself
		}
		if (!current->isLeaf())
			inorder(current->sons[i]); //if isnt leaf: numOfSons = numOfRecord + 1 so we need to ran over this Node too.
	}
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	// TODO: fix
	return nullptr;
}

template <class T>
void BTree<T>::split(BNode* current)
{
	// TODO: fix
}



template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	// TODO: fix
	return nullptr;
}

template<class T>
T* BTree<T>::search(int key) {
	int counter = 0;
	// TODO: fix
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return nullptr;
}
