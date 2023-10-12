#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"

class FindByNameVisitor : public Visitor{
    FindByNameVisitor(string name){}

    void visitFolder(Folder * folder){}

    void visitFile(File * file){}
};