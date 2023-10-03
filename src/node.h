#if !defined(NODE_H)
#define NODE_H
#pragma once
#include "./iterator.h"
#include<string>

using namespace std;

class Node {
public:
    Node(const std::string path = "", const std::string & name = "")
    :_path(path), _name(name)
    {}

    std::string name() const{
        return _name;
    }
    
    std::string path() const{
        return _path + _name;
    }
    
    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(string path) = 0;

    int numberOfFiles() const;

    Iterator * createIterator();

private:
    const std::string _path;
    const std::string _name;
};


#endif // NODE_H
