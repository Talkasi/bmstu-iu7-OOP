#include "doors.hpp"
#include "config.hpp"
#include <QDebug>

Doors::Doors(cabin_id_t cabin_id) : _cabin_id(cabin_id), _state(CLOSED)
{
    _openTimer.setSingleShot(true);
    _waitTimer.setSingleShot(true);
    _closeTimer.setSingleShot(true);

    QObject::connect(&_openTimer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&_waitTimer, SIGNAL(timeout()), this, SLOT(startClosing()));
    QObject::connect(&_closeTimer, SIGNAL(timeout()), this, SLOT(close()));
}

void Doors::startOpening()
{
    if (_state == OPEN || _state == OPENING)
        return;

    if (_state == CLOSED) {
        this->_openTimer.start(DOOR_TIME);
    }
    else {
        auto timer = this->_closeTimer.remainingTime();
        _closeTimer.stop();

        if (timer < 0)
            this->_openTimer.start(DOOR_TIME);
        else
            this->_openTimer.start(DOOR_TIME - timer);
    }

    qInfo("Двери лифта №%d открываются...", _cabin_id + 1);
    this->_state = OPENING;
}

void Doors::open()
{
    if (this->_state != OPENING)
        return;

    this->_state = OPEN;
    qInfo("[*] Двери лифта №%d открыты!", _cabin_id + 1);

    this->_waitTimer.start(WAIT_TIME);
}

void Doors::close()
{
    if (this->_state != CLOSING)
        return;

    this->_state = CLOSED;
    qInfo("[*] Двери лифта №%d закрылись!", _cabin_id + 1);

    emit doorClosed();
}

void Doors::startClosing()
{
    if (this->_state != OPEN)
        return;

    this->_state = CLOSING;
    qInfo("Двери лифта №%d закрываются...", _cabin_id + 1);

    this->_closeTimer.start(DOOR_TIME);
}
