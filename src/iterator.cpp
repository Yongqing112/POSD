#include "./folder.h"
#include "./node.h"
#include "./iterator.h"
#include "./null_iterator.h"
#include "./dfs_iterator.h"

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

void NullIterator::first(){}

bool NullIterator::isDone() const{
    return true;;
}

Node * NullIterator::currentItem() const{
    return nullptr;
}

void NullIterator::next(){}

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
        if(!this->currentItem()->subNodes.empty()){ // have sub nodes;
            _parent = _it;
            _it = this->currentItem()->subNodes.begin();
        }
        else{// don't have sub nodes, so go to next file or folder
            location = std::distance(father->subNodes.begin(), _it);
            if((father->subNodes.begin() + location + 1) != father->subNodes.end()){
                _it = father->subNodes.begin() + location + 1;
            }
            else{
                _it++;
            }
        }
    }
    else{
        father = (*_it)->getParent();
        grandfather = father->getParent();
        if(nullptr != grandfather){ // have grandfather
            if(_it+1 == father->subNodes.end()){
                location = std::distance(grandfather->subNodes.begin(), _parent);
                if((grandfather->subNodes.begin() + location + 1) != grandfather->subNodes.end()){
                    _it = grandfather->subNodes.begin() + location + 1;
                }
                else{
                    _it = grandfather->subNodes.end();
                }
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
            }
        }
        else{ // only have father
            location = std::distance(father->subNodes.begin(), _it);
            if((father->subNodes.begin() + location + 1) != father->subNodes.end()){
                _it = father->subNodes.begin() + location + 1;
            }
            else{
                _it++;
                
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
    Folder * folder;
    folder = dynamic_cast<Folder *>(*_it);
    Node * father;
    if(folder){
        father = (*_it)->getParent();
        if(!(*_it)->subNodes.empty()){
            _queue.push_back((*_it)->subNodes.begin());
        }
        if((_it + 1) == father->subNodes.end()){
            _it = _queue.front();
            _queue.erase(_queue.begin());
        }
        else{
            _it++;
        }
    }
    else{
        father = (*_it)->getParent();
        if((_it + 1) == father->subNodes.end()){
            if(!_queue.empty()){
                _it = _queue.front();
                _queue.erase(_queue.begin());
            }
            else{
                _it =  _composite->subNodes.end();
            }
        }
        else{
            _it++;
        }
    }
}