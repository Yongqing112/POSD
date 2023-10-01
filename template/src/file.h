#if !defined(FILE_H)
#define FILE_H
#pragma once
#include "./node.h"

class File : public Node {
public:
    File(const std::string & path, const std::string & name = "")
    :Node(path, name)
    {}

private:
};

#endif // FILE_H
