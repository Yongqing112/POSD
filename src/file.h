#if !defined(FILE_H)
#define FILE_H
#pragma once
#include "./node.h"
#include "./iterator.h"
#include "./null_iterator.h"

class File: public Node {
public:
    File(std::string path)
    :Node(path)
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

    int numberOfFiles() const override{
        throw string("this is a file.");
    }

    NullIterator * createIterator(){
        return new NullIterator();
    }

    ~File(){}

private:
};

#endif // FILE_H
