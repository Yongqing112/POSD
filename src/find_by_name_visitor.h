#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"

class FindByNameVisitor : public Visitor{
private:
    string _name;
    list<string> paths;
public:
    FindByNameVisitor(string name)
    : _name(name)
    {}

    void visitFolder(Folder * folder){

    }

    void visitFile(File * file){}

    list<string> getPaths(){
        for(auto it = this->_nodes.begin(); it != this->_nodes.end(); it++){
            paths.push_back(*it);
        }
    }
};