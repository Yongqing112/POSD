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
        return nullptr;
    }

    Node * find(string path){
        return nullptr;
    }

    int numberOfFiles() const override{
        throw string("this is a file.");
    }

    NullIterator * createIterator(){
        return new NullIterator();
    }

    ~File(){}
};