#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"

class StreamOutVisitor : public Visitor{
private:
    list<string> _result;
public:
    StreamOutVisitor(){}

    void visitFolder(Folder * folder){}

    void visitFile(File * file){}

    list<string> getResult(){
        return _result:
    }
};