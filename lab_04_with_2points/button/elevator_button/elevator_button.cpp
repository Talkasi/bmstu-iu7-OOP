#include "elevator_button.hpp"
#include <QtDebug>

ElevatorButton::ElevatorButton(int FloorN, cabin_id_t cabin_id, QWidget *parent)
    : BaseButton(parent), _buttonFloorNumber(FloorN), _cabin_id(cabin_id)
{
    QObject::connect(this, SIGNAL(activateSignal()), this, SLOT(activateSlot()));
    QObject::connect(this, SIGNAL(deactivateSignal()), this, SLOT(deactivateSlot()));
}

void ElevatorButton::activateSlot()
{
    if (this->_state == ACTIVE)
        return;

    this->_state = ACTIVE;
    qInfo("[!] Пассажир в кабине лифта №%d нажал на кнопку этажа №%d.", _cabin_id + 1, _buttonFloorNumber);
    emit activatedSignal();
}

void ElevatorButton::deactivateSlot()
{
    if (this->_state == INACTIVE)
        return;

    this->_state = INACTIVE;
    qInfo("[!] В кабине лифта №%d кнопка этажа №%d деактивирована.", _cabin_id + 1, _buttonFloorNumber);
    emit deactivatedSignal();
}
