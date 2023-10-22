#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

class StreamOutVisitor : public Visitor{
private:
    std::string _result = "";
    std::list<std::string> _resultlist;
public:
    StreamOutVisitor(){}

    void visitFile(File * file){
        std::ifstream ifs(file->path(), std::ios::in);
        if (!ifs.is_open()) {
            throw std::string("Failed to open file.");
        }

        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string contnet = ss.str();
        if(_resultlist.empty()){
            _resultlist.push_back("_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
            _result += ("_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
        }
        else{
            _resultlist.push_back("\n_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
            _result += ("\n_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
        }
        ifs.close();
    }

    void visitFolder(Folder * folder){}

    std::string getResult() const{
        if(_resultlist.size() != 1){
            return _result + "\n";
        }
        else{
            return _result;
        }
    }
};