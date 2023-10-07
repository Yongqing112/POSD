#pragma once

class Node;

class NullIterator : public Iterator {
public:
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
    ~NullIterator(){}
};