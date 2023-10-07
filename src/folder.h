#pragma once
#include "./node.h"
#include "./iterator.h"
#include "./dfs_iterator.h"
#include <vector>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
    friend class DfsIterator;
public:
    Folder(std::string path)
    :Node(path)
    {}

    void add(Node * node) override{
        Folder * folder = dynamic_cast<Folder *>(this);
        if(folder){
            vector<string > nodePath = customSplit(node->getPath());
            nodePath.pop_back();
            vector<string > thisPath = customSplit(this->getPath());
            if(nodePath == thisPath){
                node->setParent(this);
                this->_subNodes.push_back(node);
                subNodes = _subNodes;
            }
            else{
                throw string("incorret path");
            }
        }
    }
    
    void remove(string path) override {
        Folder * folder;
        for(auto it = this->_subNodes.begin(); it != this->_subNodes.end(); it++){
            folder = dynamic_cast<Folder *>(*it);
            if((*it)->path() == path){
                (*it)->setParent(nullptr);
                this->_subNodes.erase(it--);
            }
            else if(folder){
                folder->remove(path);
            }
        }
    }

    Node * getChildByName(const char * name) const override{
        Node * target = nullptr;
        for(auto it = this->_subNodes.begin(); it != this->_subNodes.end(); it++){
            if((*it)->name() == name){
                target = *it;
            }
        }
        return target;
    }

    Node * find(string path){
        Node * target = nullptr;
        Folder * folder;
        for(auto it = this->_subNodes.begin(); it != this->_subNodes.end(); it++){
            folder = dynamic_cast<Folder *>(*it);
            if((*it)->path() == path){
                target = *it;
            }
            else if(target == nullptr && folder){
                target = folder->find(path);
            }
        }
        return target;
    }

    int numberOfFiles() const override{
        int count = this->_subNodes.size();
        Folder * folder;
        for(auto it = this->_subNodes.begin(); it != this->_subNodes.end(); it++){
            folder = dynamic_cast<Folder *>(*it);
            if(folder){
                count += folder->numberOfFiles();
                count -= 1;
            }
        }
        return count;
    };

    FolderIterator * createIterator(){
        return new FolderIterator(this);
    }

    ~Folder(){}
private:
    vector<Node *> _subNodes;
};