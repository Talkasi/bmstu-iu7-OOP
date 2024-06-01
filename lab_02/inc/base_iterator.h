#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H
#include <cstdlib>

class BaseIterator
{
public:
    BaseIterator();
    explicit BaseIterator(const BaseIterator &iter);
    ~BaseIterator() = default;

protected:
    size_t index;
};

#endif // BASE_ITERATOR_H
