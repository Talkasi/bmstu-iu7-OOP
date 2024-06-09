#include "cabin.h"
#include "config.hpp"
#include <QDebug>
#include <QString>

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _cur_floor(START_FLOOR), _state(BOARDING_FINISHED), _doors(id)
{
    _moveTimer.setSingleShot(true);
    QObject::connect(this, SIGNAL(cabinStop()), this, SLOT(cabinStartBoarding()));
    QObject::connect(this, SIGNAL(openDoors()), &_doors, SLOT(startOpening()));
    QObject::connect(&_doors, SIGNAL(doorIsClosed()), this, SLOT(cabinStopBoarding()));
}

void Cabin::freeCabin()
{
    if (_state != BOARDIG_STARTED)
        return;

    _state = FREE;
}

void Cabin::moveCabinUp()
{
    if (_state == BOARDIG_STARTED)
        return;

    _state = MOVING_UP;
    qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, _cur_floor, _cur_floor + UP);
    ++_cur_floor;
    _moveTimer.start(MOVE_TIME);
}

void Cabin::moveCabinDown()
{
    if (_state == BOARDIG_STARTED)
        return;

    _state = MOVING_DOWN;
    qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, _cur_floor, _cur_floor + DOWN);
    --_cur_floor;
    _moveTimer.start(MOVE_TIME);
}

void Cabin::cabinStartBoarding()
{
    if (_state == BOARDIG_STARTED)
        return;

    _state = BOARDIG_STARTED;
    qInfo("Лифт №%d остановился на этаже №%d.", _id + 1, _cur_floor);
    emit openDoors();
}

void Cabin::cabinStopBoarding()
{
    if (_state == BOARDING_FINISHED)
        return;

    _state = BOARDING_FINISHED;
    qInfo("Посадка/высадка пассажиров в лифте №%d завершена.", _id + 1);
    emit cabinFinishedBoarding(_cur_floor, _id);
}
