#include "doors.h"
#include "config.hpp"
#include <QDebug>

Doors::Doors(cabin_id_t cabin_id, QObject *parent) : QObject(parent), currentState(CLOSED), _cabin_id(cabin_id)
{
    openDoorTimer.setSingleShot(true);
    openStateDoorTimer.setSingleShot(true);
    closeDoorTimer.setSingleShot(true);

    QObject::connect(&openDoorTimer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&openStateDoorTimer, SIGNAL(timeout()), this, SLOT(startClosing()));
    QObject::connect(&closeDoorTimer, SIGNAL(timeout()), this, SLOT(close()));
}

void Doors::startOpening()
{
    if (currentState != CLOSED)
        return;

    currentState = OPENING;
    qInfo("[*] Двери лифта №%d открываются...", _cabin_id + 1);
    openDoorTimer.start(WAIT_TIME);
}

void Doors::open()
{
    if (currentState != OPENING)
        return;

    currentState = OPENED;
    qInfo("[*] Двери лифта №%d открылись.", _cabin_id + 1);
    openStateDoorTimer.start(WAIT_TIME);
}

void Doors::startClosing()
{
    if (currentState != OPENED)
        return;

    currentState = CLOSING;
    qInfo("[*] Двери лифта №%d закрываются...", _cabin_id + 1);
    closeDoorTimer.start(WAIT_TIME);
}

void Doors::close()
{
    if (currentState != CLOSING)
        return;

    currentState = CLOSED;
    qInfo("[*] Двери лифта №%d закрылись.", _cabin_id + 1);
    emit doorIsClosed();
}
