#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    list<string> _string;

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:

    static Folder create(string path){
        // cout << "path : " + path << endl;
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;//S_ISREG
        if(S_ISDIR(mode)){
            // cout << "this is a folder : " + path << endl;
            return Folder(path);
        }
        else{
            // cout << "this is not a folder : " + path << endl;
            throw std::string("this is not a folder");
        }
    }


    void accept(Visitor * visitor) override{
        // cout<< "accept name : " + this->name() << endl;
        Iterator * it = this->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            it->currentItem()->accept(visitor);
        }
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder * composite)
        :_host(composite) {}

        void first() {
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }
        ~FolderIterator() {}

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
    };
//-----------------------------------------------------------------------

    Folder(string path): Node(path) {
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;//S_ISREG
        if(!S_ISDIR(mode)){
            // cout << "this is a folder : " + path << endl;
            throw std::string("this is not a folder");
        }
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
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

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
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

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }


    void remove(string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }
};