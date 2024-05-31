#include <Composite.h>

static Point computeCenter(const std::vector<std::shared_ptr<BaseObject>> &vector);

Composite::Composite(std::shared_ptr<BaseObject> &element)
{
    _elements.push_back(element);
    _center = element->getCenter();
}


Composite::Composite(const std::vector<std::shared_ptr<BaseObject>> &vector)
{
    _elements = vector;
    // Call to virtual method during construction bypasses virtual dispatch
    // updateCenter();
    _center = computeCenter(_elements);
}


bool Composite::add(const std::shared_ptr<BaseObject> &element)
{
    _elements.push_back(element);
    updateCenter();

    return true;
}


bool Composite::remove(const Iterator &iter)
{
    _elements.erase(iter);
    updateCenter();

    return true;
}

void Composite::updateCenter()
{
    _center = computeCenter(_elements);
    // _center = Point(0, 0, 0);
    // size_t count = 0;

    // for (const auto &element : _elements)
    // {
    //     _center = _center + element->getCenter();
    //     count++;
    // }

    // _center = Point(_center.getX() / count,
    //                 _center.getY() / count,
    //                 _center.getZ() / count);
}

bool Composite::isVisible()
{
    return false;
}

bool Composite::isComposite()
{
    return true;
}

Point Composite::getCenter() const
{
    return _center;
}

void Composite::moveElemsToOrigin(const Point &center)
{
    Point diff = Point(0, 0, 0) - center;

    Matrix<double> mtr = {{    1,            0,            0,             0      },
                          {    0,            1,            0,             0      },
                          {    0,            0,            1,             0      },
                          {diff.getX(),  diff.getY(),  diff.getZ(),       1      }};

    transformElems(mtr);
    updateCenter();
}

void Composite::moveElemsToCenter(const Point &center)
{
    Point diff = center - _center;

    Matrix<double> mtr = {{    1,            0,            0,             0      },
                          {    0,            1,            0,             0      },
                          {    0,            0,            1,             0      },
                          {diff.getX(),  diff.getY(),  diff.getZ(),       1      }};

    transformElems(mtr);
    updateCenter();
}

void Composite::transformElems(const Matrix<double> &mtr)
{
    for (const auto &element : _elements)
    {
        element->updateCenter();
        element->transform(mtr, _center);
    }
}

void Composite::transform(const Matrix<double> &mtr, const Point &center)
{
    updateCenter();

    moveElemsToOrigin(center);
    transformElems(mtr);
    moveElemsToCenter(center);
}

Iterator Composite::begin()
{
    return _elements.begin();
}


Iterator Composite::end()
{
    return _elements.end();
}

static Point computeCenter(const std::vector<std::shared_ptr<BaseObject>> &vector)
{
    Point center = Point(0, 0, 0);
    size_t count = 0;

    for (const auto &element : vector)
    {
        center = center + element->getCenter();
        count++;
    }

    center.setX(center.getX() / count);
    center.setY(center.getY() / count);
    center.setZ(center.getZ() / count);

    return center;
}
