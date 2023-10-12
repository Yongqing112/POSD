#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"

class FindByNameVisitor : public Visitor{
private:
    string _name;
public:
    FindByNameVisitor(string name)
    : _name(name)
    {}

    void visitFolder(Folder * folder){
        
    }

    void visitFile(File * file){}
};