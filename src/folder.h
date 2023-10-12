#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"
#include <iostream>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
private:
    list<Node *> _nodes;
    list<string> _string;

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:
    list<string> findByName(string name) override{
        cout<< "name : " + name << endl;
        return _string;
    }

    void accept(Visitor * visitor) override{
        cout<< "name : " + this->name() << endl;
        Iterator * it = this->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            it->currentItem()->accept(visitor);
        }
        visitor->visitFolder(this);
    }
//-----------------------------------------------------------------------

    Folder(string path): Node(path) {}

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

    void remove(string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }
};