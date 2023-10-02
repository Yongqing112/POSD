#if !defined(FOLDER)
#define FOLDER
#pragma once
#include "./node.h"
#include "./iterator.h"
#include <list>

using namespace std;

class Folder: public Node {
public:
    Folder(const std::string & path = "", const std::string & name = "", std::list<Node *> nodes = {})
    :Node(path, name), _nodes(nodes)
    {}

    void add(Node * node) override{
        _nodes.push_back(node);
    }
    
    void remove(string path) const override{};

    FolderIterator * createIterator(){
        return new FolderIterator(this);
    }
private:
    std::list<Node *> _nodes;
};


#endif // FOLDER
