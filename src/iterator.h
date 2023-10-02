#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<vector>

class Node;
class Folder;

class Iterator {
public:
    ~Iterator();
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem();
    void next();
    bool isDone();
private:
    Folder * _composite;
    std::vector<Node *>::iterator _it;
};


#endif // ITERATOR_H
