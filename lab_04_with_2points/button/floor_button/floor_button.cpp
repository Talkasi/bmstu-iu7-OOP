#include "floor_button.hpp"
#include "config.hpp"
#include <QtDebug>

FloorButton::FloorButton(int FloorN, direction_t direction, QWidget *parent)
    : BaseButton(parent), _buttonFloorNumber(FloorN), _direction(direction)
{
    QObject::connect(this, SIGNAL(activateSignal()), this, SLOT(activateSlot()));
    QObject::connect(this, SIGNAL(deactivateSignal()), this, SLOT(deactivateSlot()));
}

void FloorButton::activateSlot()
{
    if (this->_state == ACTIVE)
        return;

    this->_state = ACTIVE;
    if (_direction == UP)
        qInfo("[!] Ожидающий лифта на этаже №%d хочет поехать наверх.", _buttonFloorNumber);
    else
        qInfo("[!] Ожидающий лифта на этаже №%d хочет поехать вниз.", _buttonFloorNumber);

    emit activatedSignal();
}

void FloorButton::deactivateSlot()
{
    if (this->_state == INACTIVE)
        return;

    this->_state = INACTIVE;
    if (_direction == UP)
        qInfo("[!] На этаже №%d кнопка вызова лифта наверх деактивирована.", _buttonFloorNumber);
    else
        qInfo("[!] На этаже №%d кнопка вызова лифта вниз деактивирована.", _buttonFloorNumber);

    emit deactivatedSignal();
}
