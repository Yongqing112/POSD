#pragma once

#include <list>
#include<string>
#include <iostream>
#include <sys/stat.h>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder: public Node {
private:
    std::list<Node *> _nodes;
    std::list<std::string> _string;

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:

    static Folder * create(std::string path){
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;//S_ISREG
        if(S_ISDIR(mode)){
            return new Folder(path);
        }
        else{
            throw std::string("this is not a folder");
        }
    }


    void accept(Visitor * visitor) override{
        Iterator * it = this->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            it->currentItem()->accept(visitor);
        }
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder * composite)
        :_host(composite) {
            _origin = _host->_nodes;
        }

        void first() {
            if(_origin != _host->_nodes){
                throw std::string("structure of golder is changed");
            }
            else{
                _current = _host->_nodes.begin();
            }
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            if(_origin != _host->_nodes){
                throw std::string("structure of golder is changed");
            }
            else{
            _current++;
            }
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }
        
        ~FolderIterator() {}

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        std::list<Node *> _origin;
    };
//-----------------------------------------------------------------------

    Folder(std::string path): Node(path) {
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;//S_ISREG
        if(!S_ISDIR(mode)){
            throw std::string("this is not a folder");
        }
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw std::string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
    }

    Node * getChildByName(const char * name) const {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() {
        return new FolderIterator(this);
    }

    Iterator * dfsIterator() {
        return new DfsIterator(this);
    }

    Node * find(std::string path) {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (std::string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<std::string> findByName(std::string name) override {
        std::list<std::string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<std::string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }


    void remove(std::string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }
};