#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"
#include <fstream>
#include <sstream>
#include <iostream>

class StreamOutVisitor : public Visitor{
private:
    string _result;
public:
    StreamOutVisitor(){}

    void visitFolder(Folder * folder){}

    void visitFile(File * file){
        cout << "StreamOutFile path : " + file->path() << endl;
        std::ifstream ifs(file->path(), std::ios::in);
        if (!ifs.is_open()) {
            cout << "Failed to open file.\n";
        }

        std::stringstream ss;
        ss << ifs.rdbuf();
        _result = ss.str();
        ifs.close();
    }

        string getResult(){
            cout << "getResult : " + _result << endl;
            return _result;
        }
};