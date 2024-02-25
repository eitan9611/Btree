#pragma once
#include <iostream>
using namespace std;

template <class T>
class AVL : public LibraryDataStructure<T>
{
protected:
    class Node
    {
    public:
        T record;
        Node* left;
        Node* right;
        Node(T val, Node* l = nullptr, Node* r = nullptr)
            : record(val), left(l), right(r) {}
    };

    // Data member of tree
    Node* root;

    // Helper functions
    int height(Node* current);
    void clear(Node* current);
    void inorder(Node* current);
    void insert(Node*& current, T record);
    T* search(Node* current, int record, int& counter);
    void process(T& r);

public:
    AVL();
    AVL(const AVL<T>& other);
    ~AVL();
    bool isEmpty() const;
    void clear();
    void inorder();
    int height();
    void insert(T record);
    T* search(int record);

private:
    void balanceTree(Node*& current);
    Node* LL(Node* x);
    Node* LR(Node* x);
    Node* RR(Node* x);
    Node* RL(Node* x);
};

template<class T>
AVL<T>::AVL() : root(nullptr) {}

template<class T>
AVL<T>::AVL(const AVL<T>& other)
{
    if (other.isEmpty())
        root = nullptr;
    else
        root = copyTree(other.root);
}

template<class T>
AVL<T>::~AVL()
{
    clear();
}

template<class T>
bool AVL<T>::isEmpty() const
{
    return root == nullptr;
}

template<class T>
void AVL<T>::clear(Node* current)
{
    if (current)
    {
        clear(current->left);
        clear(current->right);
        delete current;
    }
}

template<class T>
void AVL<T>::clear()
{
    clear(root);
    root = nullptr;
}


template<class T>
void AVL<T>::inorder(Node* current)
{
    if (current)
    {
        inorder(current->left);
        process(current->record);
        inorder(current->right);
    }
}

template<class T>
void AVL<T>::inorder()
{
    inorder(root);
}


template<class T>
int AVL<T>::height(Node* current)
{
    if (!current)
        return -1;
    return max(height(current->left), height(current->right)) + 1;
}

template<class T>
int AVL<T>::height()
{
    return height(root);
}

template<class T>
void AVL<T>::insert(Node*& current, T record)
{
    if (!current)
        current = new Node(record);
    else if (record < current->record)
        insert(current->left, record);
    else if (record > current->record)
        insert(current->right, record);

    balanceTree(current);
}

template<class T>
void AVL<T>::insert(T record)
{
    insert(root, record);
}

template<class T>
T* AVL<T>::search(Node* current, int record, int& counter)
{
    if (!current)
        return nullptr;

    counter++;

    if (current->record.getKey() == record)
        return &(current->record);

    if (record < current->record.getKey())
        return search(current->left, record, counter);
    else
        return search(current->right, record, counter);
}

template<class T>
T* AVL<T>::search(int record)
{
    int counter = 0;
    T* result = search(root, record, counter);
    cout << "The search involved scanning " << counter << " nodes" << endl;
    return result;
}

template<class T>
void AVL<T>::balanceTree(Node*& current)
{
    int balance = height(current->left) - height(current->right);

    if (balance > 1)
    {
        if (height(current->left->left) >= height(current->left->right))
            current = LL(current);
        else
            current = LR(current);
    }
    else if (balance < -1)
    {
        if (height(current->right->right) >= height(current->right->left))
            current = RR(current);
        else
            current = RL(current);
    }
}

template<class T>
typename AVL<T>::Node* AVL<T>::LL(typename AVL<T>::Node* x)
{
    typename AVL<T>::Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

template<class T>
typename AVL<T>::Node* AVL<T>::LR(typename AVL<T>::Node* x)
{
    typename AVL<T>::Node* y = x->left;
    typename AVL<T>::Node* z = y->right;
    x->left = z;
    y->right = z->left;
    z->left = y;
    x->left = z->right;
    z->right = x;
    return z;
}

template<class T>
typename AVL<T>::Node* AVL<T>::RR(typename AVL<T>::Node* x)
{
    typename AVL<T>::Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

template<class T>
typename AVL<T>::Node* AVL<T>::RL(typename AVL<T>::Node* x)
{
    typename AVL<T>::Node* y = x->right;
    typename AVL<T>::Node* z = y->left;
    x->right = z;
    y->left = z->right;
    z->right = y;
    x->right = z->left;
    z->left = x;
    return z;
}

template<class T>
inline void AVL<T>::process(T& r)
{
    cout << "(" << r.getKey() << ")" << endl;
}