#include "./folder.h"
#include "./node.h"
#include "./iterator.h"
#include "./dfs_iterator.h"
#include <stack>

FolderIterator::FolderIterator(Folder * composite)
    : _composite(composite)
    {}
void FolderIterator::first(){
    _it = _composite->_subNodes.begin();
}

bool FolderIterator::isDone() const{
    return _it == _composite->_subNodes.end();
}

Node * FolderIterator::currentItem() const{
    return *_it;
}

void FolderIterator::next(){
    _it++;
}

DfsIterator::DfsIterator(Node * composite)
    : _composite(composite)
    {}

void DfsIterator::first(){
    // for(auto it = _composite->subNodes.begin(); it != _composite->subNodes.end(); it++){
    //     cout << "just :" + (*it)->path() << endl;
    // }
    
    _it = _composite->subNodes.begin();
}

bool DfsIterator::isDone() const{
    return _it == _composite->subNodes.end();
}

Node * DfsIterator::currentItem() const{
    return *_it;
}

void DfsIterator::next(){
    Folder * folder;
    folder = dynamic_cast<Folder *>(*_it);
    _parent = _it;
    if(folder){
        if(this->currentItem()->numberOfFiles() != 0){
            folderCount = this->currentItem()->numberOfFiles();
            cout<< folderCount << endl;
            cout<< "now folder : " + (*_it)->path() << endl;
            mystack.push(_it);
            _it = this->currentItem()->subNodes.begin();
            cout<< "next folder : " + (*_it)->path() << endl;
        }
        else{
            cout<< "now folder : " + (*_it)->path() << endl;
            if(!mystack.empty()){
                _it = mystack.top();
                mystack.pop();
                cout<< "go back folder : " + (*_it)->path() << endl;
                mystack.push(_it);
                _it = this->currentItem()->subNodes.begin();
                if(folder = dynamic_cast<Folder *>(*_it)){
                    folderCount -= 1;
                }
            }
            _it++;
            cout<< "next folder : " + (*_it)->path() << endl;
        }
    }
    else{
        //cout<< folderCount << endl;
        cout<< "now folder : " + (*_it)->path() << endl;
        if(folderCount != 0){
            _it++;
            folderCount -= 1;
            cout<< folderCount << endl;
            cout<< "next folder : " + (*_it)->path() << endl;
        }
        else{
            cout<< "go back folder : " + (*_it)->path() << endl;
            _it = mystack.top();
            mystack.pop();
            cout<< "next folder : " + (*_it)->path() << endl;
        }
    }

    // if(folder){
    //     cout<< "folder : " + folder->path() << endl;
    //     if(this->currentItem()->numberOfFiles() != 0){
    //         if(){
    //             _parent = _it;
    //         }
    //         _it = this->currentItem()->subNodes.begin();
    //         cout<< "next folder : " + (*_it)->path() << endl << endl;
    //     }
    //     else{
    //         _it = _parent;
    //         _it = this->currentItem()->subNodes.begin();
    //         _it++;
    //         cout<< "next folder : " + (*_it)->path() << endl << endl;
    //     }
    // }
    // else{
    //     cout<< "file : " + (*_it)->path() << endl;
    //     if(this->currentItem()->subNodes.begin() != this->currentItem()->subNodes.end()){
    //         _it++;
    //         cout<< "next file : " + (*_it)->path() << endl << endl;
    //     }
    //     else{
    //         _it = _parent;
    //         cout<< "next file : " + (*_it)->path() << endl << endl;
    //     }
        
    // }
}

BfsIterator::BfsIterator(Node * composite)
    : _composite(composite)
    {}