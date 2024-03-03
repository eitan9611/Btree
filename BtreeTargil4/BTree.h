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
		void insertKey(T record);
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
	records = nullptr;
	for (int i = 0; i < m; ++i) {
		delete sons[i]; // Assuming each element of sons was dynamically allocated
	}
	delete[] sons; // Delete the sons array
	sons = nullptr;
	delete parent;
	parent = null;
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	if (numOfSons == 0)
		return true;
	return false;
}

template<class T>
void BTree<T>::BNode::insertKey(T record)
{

	bool stop = false;
	int rightPlace = 0;
	for (int i = 0; i < numOfRecords && stop = false; i++)
	{
		if (records[i] > record)//found the right place to get this record in 
		{
			stop = true;
			rightPlace = i;
			for (int j = i; j < numOfRecords; j++)//get all the continue of the array one place earlier and crush the record we want to delete
			{
				records[j+1] = records[j];
			}	
		}
	}
	records[rightPlace] = record;
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
	clear(root);
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
		delete[]records;//deleting all records-directly
		for (int i = 0; i < current->numOfSons; i++)//delete sons
		{
			clear(sons[i]);
		}
		delete[]sons;
		delete current;
		current = null;
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
	if (root == nullptr)//empty tree
		return nullptr;
	if ((current->numOfSons) == 0 && (current->numOfRecords) < m)//our current isn't full => add to him
		return current;
	for (size_t i = 0; i < length; i++)
	{
		for (int i = 0; i < current->numOfRecords; i++)
		{
			//if you meet a deleted place-keep go
			//else  if you meet place with record and his record isn't a sign for deleted place [0] => see if you need to go left or right according to his value
			if (current->records[i] < record && current->records[i] != 0)

		}

	}
	

}

template <class T>
void BTree<T>::split(BNode* fullNode)
{
	//WAY OF WORK:
	//A. first m/2 => stays in the fullNode
	//B. middle => goes to the parent
	//C. last m/2 => creates new node and send them to him. this new node always will be one place after the son fullNode. 

	//B. get the middle value in full node to the parent:
	fullNode->parent->insertKey((fullNode->records)[m / 2]);//get him into the father 
	fullNode->parent->numOfRecords++;
	fullNode->numOfRecords--;

	//C. fill the new node with appropriate values:
	BNode* newNode(m);	
	newNode->parent = fullNode->parent;
	for (int i = ((fullNode->numOfRecords) / 2) + 1; i < fullNode->numOfRecords; i++)
	{
		newNode->records->insertKey((fullNode->records)[i]);
		(fullNode->records)[i] = 0;
		newNode->numOfRecords++;
		fullNode->numOfRecords--;
	}
	//get newNode in his correct place in the sons array-> always the newNode will be one place after the fullNode:
	int numberOfSonsParent = fullNode->parent->numOfSons;
	int placeOfFullNode = 0;
	for (int  i = 0; i < numberOfSonsParent; i++)
	{
		if (fullNode->parent->sons[i] == fullNode)
		{
			placeOfFullNode = i;
		}
	}
	for (int i = placeOfFullNode+1; i < numberOfSonsParent-1; i++)//move all BNodes after fullNode one place forward.
	{
		fullNode->parent->sons[i + 1] = fullNode->parent->sons[i];
	}
	fullNode->parent->sons[i + 1] = newNode;
	fullNode->parent->numOfSons++;


	//reqursive check for the father send.
	if (fullNode->parent->numOfSons == m)
		split(fullNode->parent);
}



template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	counter++;
	for(int i = 0;  i< current->numOfRecords; i++)
	{
		if (key < (current->records)[i])
		{
			return search(current->records)[i],key,counter);
		}
		if (key == (current->records)[i])
		{
			return current->records)[i];
		}
	}
	//if key is bigger from all the current record =>go to the right son
	return search(current->records)[current->numOfSons],key,counter);
}

template<class T>
T* BTree<T>::search(int key) {
	int counter = 0;
	// TODO: fix
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return nullptr;
}
