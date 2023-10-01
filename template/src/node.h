#if !defined(NODE_H)
#define NODE_H

#include<string>

using namespace std;

class Node {
public:
    Node(const std::string path, const std::string & name = "")
    :_path(path), _name(name)
    {}

    string name() const{
        return _name;
    }
    
    string path() const{
        return _path + _name;
    }
    
    void add(Node * node);

    void remove(string path);
    
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    int numberOfFiles() const;

    // Iterator * createIterator();
private:
    const std::string _path;
    const std::string _name;
};


#endif // NODE_H
