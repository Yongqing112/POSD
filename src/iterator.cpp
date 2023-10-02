#include "./folder.h"
#include "./node.h"
#include "./iterator.h"

FolderIterator::FolderIterator(Folder * composite)
    : _composite(composite)
    {}
void FolderIterator::first(){
    _it = _composite->_nodes.begin();
}

bool FolderIterator::isDone() const{
    return _it == _composite->_nodes.end();
}

Node * FolderIterator::currentItem() const{
    return *_it;
}

void FolderIterator::next(){
    _it++;
}
