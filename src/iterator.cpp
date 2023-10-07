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
    int location = 0;
    Folder * folder;
    folder = dynamic_cast<Folder *>(*_it);
    Node * grandfather;
    Node * father;
    if(folder){
        father = (*_it)->getParent();
        cout<< "now folder : " + folder->path() << endl<< endl;
        if(!this->currentItem()->subNodes.empty()){ // have sub nodes;
            _parent = _it;
            cout<< "parent folder : " + (* _parent)->path() << endl;
            _it = this->currentItem()->subNodes.begin();
            cout<< "next folder : " + (*_it)->path() << endl ;
            cout<< "next name : " + (*_it)->name() << endl << endl;
        }
        else{// don't have sub nodes, so go to next file or folder
            location = std::distance(father->subNodes.begin(), _it);
            cout<< "parent folder : " + father->path() <<endl;
            cout<< "location in parent : ";
            cout<< location << endl<< endl;

            if((father->subNodes.begin() + location + 1) != father->subNodes.end()){
                _it = father->subNodes.begin() + location + 1;
                cout<< "next file : " + (*_it)->path() << endl ;
            cout<< "next name : " + (*_it)->name() << endl << endl;
            }
            else{
                cout<< "end file : " + (*_it)->path() << endl << endl;
                _it++;
            }
        }
    }
    else{
        cout<< "now file : " + (*_it)->path() << endl<< endl;
        if(this->currentItem()->subNodes.begin() != this->currentItem()->subNodes.end()){
            _it++;
            cout<< "next file : " + (*_it)->path() << endl ;
            cout<< "next name : " + (*_it)->name() << endl << endl;
        }
        else{
            father = (*_it)->getParent();
            grandfather = father->getParent();
            if(nullptr != grandfather){ // have grandfather
                location = std::distance(grandfather->subNodes.begin(), _parent);
                // auto ita = (*_it)->getParent()->subNodes.begin();
                // cout<< (*ita)->path()<< endl;

                cout<< "grandparent folder : " + grandfather->path() <<endl;
                cout<< "parent folder : " + (*_parent)->path() << endl;
                cout<< "parent location in grandparent : ";
                cout<< location << endl<< endl;

                // location = std::distance((*_it)->getParent()->subNodes.begin(), _parent);
                // father->find((*_it)->getParent());
                // _parent = 

                _it = grandfather->subNodes.begin() + location + 1;;
                cout<< "next file : " + (*_it)->path() << endl ;
                cout<< "next name : " + (*_it)->name() << endl << endl;
                
                if(nullptr != grandfather->getParent()){
                    for(auto it = grandfather->getParent()->subNodes.begin(); it != grandfather->getParent()->subNodes.end(); it++){
                        if((*it)->path() == grandfather->path()){
                            _parent = it;
                        }
                    }
                }
            }
            else{ // only have father
                location = std::distance(father->subNodes.begin(), _it);
                cout<< "parent folder : " + father->path() <<endl;
                cout<< "location in parent : ";
                cout<< location << endl<< endl;

                if((father->subNodes.begin() + location + 1) != father->subNodes.end()){
                    _it = father->subNodes.begin() + location + 1;
                    cout<< "next file : " + (*_it)->path() << endl ;
                    cout<< "next name : " + (*_it)->name() << endl << endl;
                }
                else{
                    cout<< "end file : " + (*_it)->path() << endl << endl;
                    _it++;
                    
                }
            }
        }
    }
    
    // if(folder){
    //     if(){
    //         allNodes.push_back(*_it);
    //     }
    //     for(auto it = this->currentItem()->subNodes.begin(); it != this->currentItem()->subNodes.end(); it++){
    //         cout<< "push : " + (*it)->path()<< endl;
    //         allNodes.push_back(*it);
    //     }
    //     if(this->currentItem()->subNodes.begin() == this->currentItem()->subNodes.end()){
    //         _it++;
    //     }
    //     else{
    //         _it = this->currentItem()->subNodes.begin();
    //     } 
    //     cout<< "next folder : " + (*_it)->path() << endl;
    // }
    // else{
    //     cout<< "push : " + (*_it)->path()<< endl;
    //     allNodes.push_back(*_it);
    //     _it++;
    // }

    // for(auto it = allNodes.begin(); it != allNodes.end(); it++){
    //     cout<< "vector exist : " + (*it)->path() << endl;
    // }

    // if(folder){
    //     if(this->currentItem()->numberOfFiles() != 0){
    //         folderCount = this->currentItem()->numberOfFiles();
    //         cout<< folderCount << endl;
    //         cout<< "now folder : " + (*_it)->path() << endl;
    //         mystack.push(_it);
    //         _it = this->currentItem()->subNodes.begin();
    //         cout<< "next folder : " + (*_it)->path() << endl;
    //     }
    //     else{
    //         cout<< "now folder : " + (*_it)->path() << endl;
    //         if(!mystack.empty()){
    //             _it = mystack.top();
    //             mystack.pop();
    //             cout<< "go back folder : " + (*_it)->path() << endl;
    //             mystack.push(_it);
    //             _it = this->currentItem()->subNodes.begin();
    //             if(folder = dynamic_cast<Folder *>(*_it)){
    //                 folderCount -= 1;
    //             }
    //         }
    //         _it++;
    //         cout<< "next folder : " + (*_it)->path() << endl;
    //     }
    // }
    // else{
    //     //cout<< folderCount << endl;
    //     cout<< "now folder : " + (*_it)->path() << endl;
    //     if(folderCount != 0){
    //         _it++;
    //         folderCount -= 1;
    //         cout<< folderCount << endl;
    //         cout<< "next folder : " + (*_it)->path() << endl;
    //     }
    //     else{
    //         cout<< "go back folder : " + (*_it)->path() << endl;
    //         _it = mystack.top();
    //         mystack.pop();
    //         cout<< "next folder : " + (*_it)->path() << endl;
    //     }
    // }

}

BfsIterator::BfsIterator(Node * composite)
    : _composite(composite)
    {}