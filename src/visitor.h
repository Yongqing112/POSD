#pragma once

class Folder;
class File;

class Visitor{
public:
    virtual void visitFolder(Folder * folder){}
    virtual void visitFile(File * file){}
};