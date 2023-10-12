#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"

class StreamOutVisitor : public Visitor{
public:
    StreamOutVisitor(Node * node){}

    void visitFolder(Folder * folder){}

    void visitFile(File * file){}
};