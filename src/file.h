#pragma once

#include "node.h"
#include "./visitor.h"
#include <iostream>

class File: public Node {
private:
    list<string> _string;
public:
    File(string path): Node(path) {}

    int numberOfFiles() const {
        return 1;
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    list<string> findByName(string name) override{
        cout<< "name : " + name << endl;
        return _string;
    }

    void accept(Visitor * visitor) override{
        cout<< "name : " + this->name() << endl;
        visitor->visitFile(this);
    }
};