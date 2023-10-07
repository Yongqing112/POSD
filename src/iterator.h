#pragma once 

#include<vector>

class Node;
class Folder;

class Iterator {
public:
    virtual void first(){}
    virtual Node * currentItem() const{return nullptr;}
    virtual void next(){}
    virtual bool isDone() const{return false;}
    virtual ~Iterator(){}
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
    ~FolderIterator(){}
private:
    Folder * _composite;
    std::vector<Node *>::iterator _it;
};