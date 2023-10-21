#pragma once

#include "./visitor.h"
#include "./iterator.h"
#include "./folder.h"
#include "./file.h"

class FindByNameVisitor : public Visitor{
private:
    string _name;
    list<string> _paths;
public:
    FindByNameVisitor(string name)
    : _name(name)
    {}

    void visitFolder(Folder * folder){
        if (folder->name() == _name) {
            _paths.push_back(folder->path());
        }
    }

    void visitFile(File * file){
        if (file->name() == _name) {
            _paths.push_back(file->path());
        }
    }

    list<string> getPaths(){
        return _paths;
    }
};