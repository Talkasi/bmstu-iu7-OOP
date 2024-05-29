#include "cabin.hpp"
#include "src/config.hpp"
#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    _state = STOP;

    // Соединяем сигнал открытия дверей с обработчиком открытия
    QObject::connect(this, SIGNAL(openDoors()), &_doors, SLOT(startOpening()));
    // Кабина закончила движение => она свободна, выдаём сигнал cabinFinished()
    QObject::connect(&_moveTimer, SIGNAL(timeout()), this, SLOT(setFree()));
    // Двери закрылись => кабина освободилась, выдаём сигнал cabinFinished()
    QObject::connect(&_doors, SIGNAL(doorClosed()), this, SLOT(setFree()));
}

void Cabin::stopCabin()
{
    _state = WAIT;
    _moveTimer.stop();
    emit openDoors();
}

void Cabin::moveCabin()
{
    if (_state == STOP || _state == MOVING) {
        _state = MOVING;
        _moveTimer.start(MOVE_TIME);
    }
}

void Cabin::setFree()
{
    if (_state != STOP) {
        _state = STOP;
        emit cabinFinished(false);
    }
}
