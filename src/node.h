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
    Node(string path)
    :_path(path)
    {
        vector<string> tokens = customSplit(_path);
        _name = tokens.back();
    }

    string name() const{
        return _name;
    }
    
    string path() const{
        return _path;
    }
    
    void setParent(Node * parent){
        _parent = parent;
    };

    Node * getParent() const{
        return _parent;
    }
    
    std::vector<std::string> customSplit(string path){
        stringstream ss(path);
        vector<string > tokens;
        string token;
        while(getline(ss, token, '/')){
            tokens.push_back(token);
        }
        return tokens;
    }

    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;

    virtual ~Node(){}

    vector<Node *> subNodes;
private:
    std::string _path;
    std::string _name;
    Node * _parent = nullptr;
};