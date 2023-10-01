#if !defined(FILE_H)
#define FILE_H
#pragma once
#include "./node.h"

class File: public Node {
public:
    File(const std::string & path = "", const std::string & name = "")
    :Node(path, name)
    {}

    void add(Node * node) override{};

    void remove(string path) const override{};

private:
};

#endif // FILE_H
