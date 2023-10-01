#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>

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
    FolderIterator(Folder* composite)
    : _composite(composite)
    {}
    void first(){
        _it = _composite->_nodes.begin();
    }
    Node * currentItem() const;
    void next();
    bool isDone() const{
        return _it == _composite->_nodes.end();
    }
private:
    Folder * _composite;
    std::list<Node *>::iterator _it;
};


#endif // ITERATOR_H
