#pragma once

#include "./visitor.h"
#include "./folder.h"
#include "./file.h"
#include <fstream>
#include <sstream>
#include <iostream>

class StreamOutVisitor : public Visitor{
private:
    string _result = "";
    list<string> _resultlist;
public:
    StreamOutVisitor(){}

    void visitFolder(Folder * folder){}

    void visitFile(File * file){
        // cout << "StreamOutFile path : " + file->path() << endl;
        std::ifstream ifs(file->path(), std::ios::in);
        if (!ifs.is_open()) {
            cout << "Failed to open file.\n";
        }

        std::stringstream ss;
        ss << ifs.rdbuf();
        string contnet = ss.str();
        if(_resultlist.empty()){
            _resultlist.push_back("_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
        }
        else{
            _resultlist.push_back("\n_____________________________________________\n" + file->path() + "\n---------------------------------------------\n" + contnet + "\n_____________________________________________\n");
        }
        ifs.close();
    }

        string getResult(){
            // cout << "getResult : " + _result << endl;
            for (auto it=_resultlist.begin(); it != _resultlist.end(); ++it){
                _result += *it;
            }
            if(_resultlist.size() != 1){
                _result += "\n";
            }
            
            return _result;
        }
};