#pragma once

#include "node.h"

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

    list<string> findByName(string name){
        return _string;
    }
};