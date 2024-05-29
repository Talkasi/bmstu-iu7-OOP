#include "base_button.hpp"
#include <QtDebug>

BaseButton::BaseButton(QWidget *parent) : QPushButton(parent)
{
    _state = INACTIVE;
}
