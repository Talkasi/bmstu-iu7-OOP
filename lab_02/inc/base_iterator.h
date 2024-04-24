#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H
#include <cstdlib>

class BaseIterator
{
public:
    BaseIterator();
    explicit BaseIterator(const BaseIterator &iter);
    virtual ~BaseIterator() = 0;

protected:
    size_t index;
    size_t size;
};

#endif // BASE_ITERATOR_H
