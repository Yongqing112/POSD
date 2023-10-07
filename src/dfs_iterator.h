#pragma once
#include <vector>

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
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first();

    Node * currentItem() const;

    void next();
    
    bool isDone() const;

    ~BfsIterator(){}

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
    std::vector<std::vector<Node *>::iterator> _queue;
};