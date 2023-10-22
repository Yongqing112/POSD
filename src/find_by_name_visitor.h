#pragma once

#include "./visitor.h"
#include "./iterator.h"
#include "./folder.h"
#include "./file.h"
#include<string>

class FindByNameVisitor : public Visitor{
private:
    std::string _name;
    std::list<std::string> _paths;
public:
    FindByNameVisitor(std::string name)
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

    std::list<std::string> getPaths() const {
        return _paths;
    }
};