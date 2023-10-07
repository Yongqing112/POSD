#if !defined(NODE_H)
#define NODE_H
#pragma once
#include "./iterator.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Node {
    friend class FolderIterator;
    friend class DfsIterator;
public:
    Node(std::string path)
    :_path(path)
    {
        std::vector<std::string *> tokens = customSplit(_path);
        _name = *(tokens.at(tokens.size()-1));
    }

    std::string name() const{
        return _name;
    }

    std::string getName(){
        return _name;
    }
    
    std::string path() const{
        return _path;
    }

    std::string getPath(){
        return _path;
    }
    
    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator(){
        return nullptr;
    }

    void setParent(Node * parent){
        _parent = parent;
    };

    Node * getParent(){
        return _parent;
    }
    
    std::vector<std::string *> customSplit(std::string path){
        std::stringstream ss(path);
        std::vector<std::string *> tokens;
        std::string token;
        while(getline(ss, token, '/')){
            tokens.push_back(&token);
        }
        return tokens;
    }

    virtual ~Node(){}
    vector<Node *> subNodes;
private:
    std::string _path;
    std::string _name;
    Node * _parent = nullptr;
};


#endif // NODE_H
