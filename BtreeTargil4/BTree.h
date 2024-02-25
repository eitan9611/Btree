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
	// TODO: fix
}

template<class T>
BTree<T>::BNode::~BNode()
{
	// TODO: fix
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	// TODO: fix
}

template<class T>
void BTree<T>::BNode::insert(T record)
{
	// TODO: fix
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	// TODO: fix
}

template<class T>
void BTree<T>::BNode::printKeys()
{
	cout << '(';
	for (int i = 0; i < numOfRecords - 1; i++)
		cout << records[i].getKey() << ",";
	cout << records[numOfRecords - 1].getKey() << ')' << endl;
}


template<class T>
BTree<T>::BTree(int degree) :m(degree), root(nullptr)
{}

template<class T>
BTree<T>::~BTree()
{
	// TODO: fix
}
template<class T>
void BTree<T>::inorder()
{
	// TODO: fix
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
	// TODO: fix
}
template<class T>
void BTree<T>::inorder(BNode* current)
{
	// TODO: fix
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
