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

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }


    void accept(Visitor * visitor) override{
        cout<< "accept name : " + this->name() << endl;
        visitor->visitFile(this);
    }
};