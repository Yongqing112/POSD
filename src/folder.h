#if !defined(FOLDER)
#define FOLDER
#pragma once
#include "./node.h"
#include "./iterator.h"
#include <vector>
#include <iostream>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
public:
    Folder(const std::string & path = "", const std::string & name = "", std::vector<Node *> nodes = {})
    :Node(path, name), _nodes(nodes)
    {}

    void add(Node * node) override{
        this->_nodes.push_back(node);
    }
    
    void remove(string path) override {
        for(auto it = this->_nodes.begin(); it != this->_nodes.end(); it++){
            if((*it)->path() == path){
                this->_nodes.erase(it--);
            }
        }
    }

    Node * getChildByName(const char * name) const override{
        Node * target = nullptr;
        for(auto it = this->_nodes.begin(); it != this->_nodes.end(); it++){
            if((*it)->name() == name){
                target = *it;
            }
        }
        return target;
    }

    Node * find(string path){
        Node * target = nullptr;
        for(auto it = this->_nodes.begin(); it != this->_nodes.end(); it++){
            if((*it)->path() == path){
                target = *it;
            }
        }
        return target;
    }

    FolderIterator * createIterator(){
        return new FolderIterator(this);
    }
private:
    std::vector<Node *> _nodes;
};


#endif // FOLDER
