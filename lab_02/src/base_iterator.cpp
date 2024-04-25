#include "base_iterator.h"

BaseIterator::BaseIterator()
{
    index = 0;
}

BaseIterator::BaseIterator(const BaseIterator &iter)
{
    index = iter.index;
}
