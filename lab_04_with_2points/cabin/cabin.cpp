#include "cabin.hpp"
#include "config.hpp"
#include <QDebug>

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _state(STOP), _id(id), _cur_floor(START_FLOOR), _doors(id)
{
    _moveTimer.setSingleShot(true);

    QObject::connect(this, SIGNAL(openDoors()), &_doors, SLOT(startOpening()));
    QObject::connect(&_moveTimer, SIGNAL(timeout()), this, SLOT(setFree()));
    QObject::connect(&_doors, SIGNAL(doorClosed()), this, SLOT(setFree()));
    QObject::connect(this, SIGNAL(cabinArrived()), this, SLOT(stopCabin()));
}

void Cabin::stopCabin()
{
    qInfo("[!] Лифт №%d остановился на этаже №%d.", _id + 1, _cur_floor);
    _state = WAIT;
    _moveTimer.stop();
    emit openDoors();
}

void Cabin::moveCabinUp(int dest_floor)
{
    if (_state == WAIT)
        return;

    if (_cur_floor < dest_floor) {
        _state = MOVING_UP;
        qInfo("[!] Лифт №%d едет наверх и проезжает этаж №%d.", _id + 1, _cur_floor);
        ++_cur_floor;
        _moveTimer.start(MOVE_TIME);
    }
    else {
        emit cabinArrived();
    }
}

void Cabin::moveCabinDown(int dest_floor)
{
    if (_state == WAIT)
        return;

    if (_cur_floor > dest_floor) {
        _state = MOVING_DOWN;
        qInfo("[!] Лифт №%d едет вниз и проезжает этаж №%d.", _id + 1, _cur_floor);
        --_cur_floor;
        _moveTimer.start(MOVE_TIME);
    }
    else {
        emit cabinArrived();
    }
}

void Cabin::setFree()
{
    if (_state != STOP) {
        _state = STOP;
        emit cabinFinished(_cur_floor, _id);
    }
}
