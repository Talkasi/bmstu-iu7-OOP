#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H
#include <cstdlib>

class BaseIterator
{
public:
    BaseIterator();
    explicit BaseIterator(const BaseIterator &iter);
    virtual ~BaseIterator() = default;

protected:
    size_t index = 0;
};

#endif // BASE_ITERATOR_H
