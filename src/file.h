#pragma once

#include "node.h"
#include "./visitor.h"

class File: public Node {
private:
    std::list<std::string> _string;
public:
    static File * create(std::string path){
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;
        if(S_ISREG(mode)){
            return new File(path);
        }
        else{
            throw std::string("this is not a file");
        }
    }

    File(std::string path)
    : Node(path) 
    {
        struct stat st;
        const char *cstr = path.c_str();
        lstat(cstr, &st);
        int mode = st.st_mode;
        if(!S_ISREG(mode)){
            throw std::string("this is not a file");
        }
    }

    int numberOfFiles() const {
        return 1;
    }

    Node * find(std::string path) {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<std::string> findByName(std::string name) override {
        std::list<std::string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * visitor) override{
        visitor->visitFile(this);
    }
};