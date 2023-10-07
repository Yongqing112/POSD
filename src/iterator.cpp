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
                if(_it+1 == father->subNodes.end()){
                    location = std::distance(grandfather->subNodes.begin(), _parent);
                    _it = grandfather->subNodes.begin() + location + 1;;
                    
                    for(auto it = father->subNodes.begin(); it != father->subNodes.end(); it++){
                        cout<< "---------------------" + (*it)->path() << endl;
                    }

                    cout<< "grandparent folder : " + grandfather->path() <<endl;
                    cout<< "parent folder : " + (*_parent)->path() << endl;
                    cout<< "parent location in grandparent : ";
                    cout<< location << endl<< endl;

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
                else{
                    _it++;
                    cout<< "next file : " + (*_it)->path() << endl ;
                    cout<< "next name : " + (*_it)->name() << endl << endl;
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
    

}

BfsIterator::BfsIterator(Node * composite)
    : _composite(composite)
    {}

void BfsIterator::first(){
    _it = _composite->subNodes.begin();
}

bool BfsIterator::isDone() const{
    return _it == _composite->subNodes.end();
}

Node * BfsIterator::currentItem() const{
    return *_it;
}

void BfsIterator::next(){
    _it++;
}