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
	T*  search(BNode* current, int key, int& counter);
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
	parent = nullptr;
	numOfRecords = 0;
	numOfSons = 0;
}

template<class T>
BTree<T>::BNode::~BNode()
{
	if(records)
		delete[] records;
	records = nullptr;

	if(sons)
		delete[] sons; // Delete the sons array
	sons = nullptr;
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
	int i;
	for (i = 0; i < numOfRecords; i++)
	{
		if (records[i] > record)//found the right place to get this record in 
		{
			for (int j = numOfRecords; j > i; j--)//get all the continue of the array one place earlier and crush the record we want to delete
			{
				records[j] = records[j-1];
			}
			break;
		}
	}
	records[i] = record;
	numOfRecords++;
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	for (int i = 0; i < numOfRecords; i++)
	{
		if (records[i] == record)
		{
			for (int j = i; j < numOfRecords - 1; j++)//get all the continue of the array one place earlier and crush the record we want to delete
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
	if (root == nullptr)
		root = new BNode(m);

	BNode* x = findAddNode(root, record);
	x->insertKey(record);
	if (x->numOfRecords == m)
		split(x);
}


//private recursive help fuctions
template<class T>
void BTree<T>::clear(BNode* current)
{
		if (current)
	{
		//delete[] current->records;//deleting all records-directly
		for (int i = 0; i < current->numOfSons; i++)//delete sons
		{
			clear(current->sons[i]);
		}
		
		delete current;
		current = nullptr;
	}
}
template<class T>
void BTree<T>::inorder(BNode* current)
{
	int i;
	if (current != nullptr && !current->isLeaf())
	{
		for (i = 0; i < current->numOfRecords; i++)
		{
			if (!current->isLeaf())
				inorder(current->sons[i]); //ran over the left node of of the current record 

			current->printKeys();// visit the node itself
		}
		if (!current->isLeaf())
			inorder(current->sons[i]); //if isnt leaf: numOfSons = numOfRecord + 1 so we need to ran over this Node too.
	}
	//if it doesn't have sons - print it only once
	else if (current->isLeaf())
		current->printKeys();
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	int i;
	if (root == nullptr)//empty tree
		return nullptr;

	if (current->isLeaf())//our current isn't full => add to him
		return current;

	else if (record < current->records[0]) //if the current node has atleast one record, and the new record is smaller the left record
		return findAddNode(current->sons[0], record);

	for (i = 1; i < current->numOfRecords; i++)
	{
		if (record > current->records[i - 1] && record < current->records[i])
			return findAddNode(current->sons[i], record);

	}

	//if we finished the loop and didn't find the right node return the right node.
	return findAddNode(current->sons[i], record);
}

template <class T>
void BTree<T>::split(BNode* fullNode)
{
	int i;

	//WAY OF WORK:
	//A. first m/2 => stays in the fullNode
	//B. middle => goes to the parent
	//C. last m/2 => creates new node and send them to him. this new node always will be one place after the son fullNode. 

	//B. get the middle value in full node to the parent:
	if (fullNode->parent == nullptr)
	{
		fullNode->parent = new BNode(m);
		fullNode->parent->sons[0] = fullNode;
		fullNode->parent->numOfSons++;

		root = fullNode->parent;
	}

	fullNode->parent->insertKey((fullNode->records)[m / 2]);//get him into the father 
	fullNode->numOfRecords--;

	//C. fill the new node with appropriate values:
	BNode* newNode = new BNode(m);	
	newNode->parent = fullNode->parent;
	for (i = (m / 2) + 1; i < m; i++)
	{
		newNode->insertKey((fullNode->records)[i]);
		fullNode->numOfRecords--;
	}
	//get newNode in his correct place in the sons array-> always the newNode will be one place after the fullNode:
	int numberOfSonsParent = fullNode->parent->numOfSons;
	int placeOfFullNode = 0;
	for (i = 0; i < numberOfSonsParent; i++)
	{
		if (fullNode->parent->sons[i] == fullNode)
		{
			placeOfFullNode = i;
		}
	}
	for (i = numberOfSonsParent; i > placeOfFullNode + 1; i--)//move all BNodes after fullNode one place forward.
	{
		fullNode->parent->sons[i] = fullNode->parent->sons[i-1];
	}
	fullNode->parent->sons[placeOfFullNode +1] = newNode;
	fullNode->parent->numOfSons++;

	if (!fullNode->isLeaf())
	{
		for (int i = (m / 2) + 1; i <= m; i++)
			newNode->sons[i -((m/2)+1)] = fullNode->sons[i];

		fullNode->numOfSons = (m / 2) + 1;
		newNode->numOfSons = (m / 2) + 1;
	}


	//reqursive check for the father send.
	if (fullNode->parent->numOfSons > m)
		split(fullNode->parent);
}



template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	int i;
	counter++;
	if (current != nullptr)
	{
		for (i = 0; i < current->numOfRecords; i++)
		{
			if (key < (current->records[i]).getKey())
			{
				return search(current->sons[i], key, counter);
			}
			if (key == (current->records[i]).getKey())
			{
				return &(current->records[i]); ///// maybe need to be current->records
			}
		}
	}
	else
		return nullptr;
	//if key is bigger from all the current record =>go to the right son
	if (current->numOfSons != 0)
	{
		return search(current->sons[i], key, counter);
	}
	return nullptr;
}

template<class T>
T* BTree<T>::search(int key) 
{
	int counter = 0;
	T* found = search(root, key, counter);
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return found;
}
