#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

class Node;

class NullIterator : public Iterator {
public:
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
    ~NullIterator(){}
};

#endif // NULL_ITERATOR_H
