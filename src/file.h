#if !defined(FILE_H)
#define FILE_H
#pragma once
#include "./node.h"
#include "./iterator.h"

class File: public Node {
public:
    File(const std::string & path = "", const std::string & name = "")
    :Node(path, name)
    {}

    void add(Node * node) override{
        throw string("this is a file.");
    }

    void remove(string path) override{
        throw string("this is a file.");
    }

    Node * getChildByName(const char * name) const override{
        Node * target = nullptr;
        return target;
    }

    Node * find(string path){
        Node * target = nullptr;
        return target;
    }

private:
};

#endif // FILE_H
