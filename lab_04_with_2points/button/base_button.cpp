#include "base_button.hpp"
#include <QtDebug>

BaseButton::BaseButton(QWidget *parent) : QObject(parent)
{
    _state = INACTIVE;
}
