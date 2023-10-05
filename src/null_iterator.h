#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

class NullIterator : public Iterator {
    void first(){}
    Node * currentItem() const{return nullptr;}
    void next(){}
    bool isDone() const{
        return true;
    }
    ~NullIterator(){}
};

#endif // NULL_ITERATOR_H
