#include "./folder.h"
// #include "./node.h"
#include "./iterator.h"

FolderIterator::FolderIterator(Folder * composite)
    : _composite(composite)
    {}
void FolderIterator::first(){
    _it = _composite->_nodes.begin();
}
// Node * FolderIterator::currentItem() const;

// void FolderIterator::next();

bool FolderIterator::isDone(){
    return _it == _composite->_nodes.end();
}