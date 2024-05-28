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

void Cabin::moveCabin(Direction direction)
{
    if (direction == UP && (_state == STOP || _state == MOVING_UP)) {
        _state = MOVING_UP;
        _moveTimer.start(MOVE_TIME);
        qInfo() << "Кабина знает, что едет вверх";
        return;
    }

    if (direction == DOWN && (_state == STOP || _state == MOVING_DOWN)) {
        _state = MOVING_DOWN;
        _moveTimer.start(MOVE_TIME);
        qInfo() << "Кабина знает, что едет вниз";
        return;
    }
}

void Cabin::setFree()
{
    if (_state != STOP) {
        _state = STOP;
        emit cabinFinished();
    }
}
