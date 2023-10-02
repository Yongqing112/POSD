#if !defined(NODE_H)
#define NODE_H

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

    virtual void remove(string path) const = 0;
    
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    int numberOfFiles() const;

    virtual Iterator * createIterator();
private:
    const std::string _path;
    const std::string _name;
};


#endif // NODE_H
