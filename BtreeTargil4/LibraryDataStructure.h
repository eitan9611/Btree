#pragma once
template<class T>
class LibraryDataStructure
{
public:
    virtual void inorder() = 0;
    virtual void insert(T t) = 0;
    virtual T* search(int key) = 0;
    virtual ~LibraryDataStructure() {} // Virtual destructor
};
