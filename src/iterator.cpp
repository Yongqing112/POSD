#include "./folder.h"
#include "./node.h"
#include "./iterator.h"
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

DfsIterator::DfsIterator(Node * composite)
    :_composite(composite)
    {}

// void DfsIterator::first(){
//     // _it = _composite->_subNodes.begin();
// }

// bool DfsIterator::isDone() const{
//     return false;//_it == _composite->_subNodes.end();
// }

// Node * DfsIterator::currentItem() const{
//     return *_it;
// }

// void DfsIterator::next(){
//     _it++;
// }

BfsIterator::BfsIterator(Node * composite)
    :_composite(composite)
    {}