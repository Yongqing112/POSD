#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#pragma once
#include <vector>
#include <stack>

class Node;
class Folder;

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite);

    void first();

    Node * currentItem() const;

    void next();
    
    bool isDone() const;

    ~DfsIterator(){}

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
    std::vector<Node *>::iterator _parent;
    std::vector<Node *> allNodes;
    int folderCount = 0;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first(){}
    Node * currentItem() const{return nullptr;}
    void next(){}
    bool isDone() const{return false;}
    ~BfsIterator(){}

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
};

#endif // DFS_ITERATOR_H
