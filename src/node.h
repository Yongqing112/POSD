#pragma once 

#include <string>
#include <list>
#include "iterator.h"
#include "null_iterator.h"
#include "visitor.h"

using namespace std;

class Node {
private:
    std::string _path;
    Node * _parent;
protected:

    Node(std::string path): _path(path) {}

public:

    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw std::string("This node does not support removing sub node");
    }

    std::string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    std::string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw std::string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {
        return new NullIterator();
    }

    virtual Iterator * dfsIterator() {
        return new NullIterator();
    }

    virtual Node * find(std::string path) = 0;

    virtual std::list<std::string> findByName(std::string name) = 0;

    virtual void remove(std::string path) {
        throw std::string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor * visitor) = 0;
};