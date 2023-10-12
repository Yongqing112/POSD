#pragma once

class Folder;
class File;

class Visitor{
public:
    virtual void visitFolder(Folder * folder) = 0;
    virtual void visitFile(File * file) = 0;
};