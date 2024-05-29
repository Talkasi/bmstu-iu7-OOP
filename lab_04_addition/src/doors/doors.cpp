#include "doors.hpp"
#include "../config.hpp"
#include <QDebug>

Doors::Doors() : _state(CLOSED)
{
    QObject::connect(&_openTimer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&_waitTimer, SIGNAL(timeout()), this, SLOT(startClosing()));
    QObject::connect(&_closeTimer, SIGNAL(timeout()), this, SLOT(close()));
}

void Doors::open()
{
    // Если двери до этого не открывались, выходим
    if (this->_state != OPENING)
        return;

    this->_state = OPEN;
    qInfo() << "[*] Двери открыты!";

    // Запуск таймера на посадку пассажиров
    this->_waitTimer.start(WAIT_TIME);
}

void Doors::startOpening()
{
    // Если двери уже открыты или уже открываются, ничего не делаем
    if (_state == OPEN || _state == OPENING)
        return;

    if (_state == CLOSED) {
        // Если двери зыкрыты, полностью открываем
        this->_openTimer.start(DOOR_TIME);
    }
    else {
        // Eсли двери закрывались, открываем ту часть, которая успела закрыться
        auto timer = this->_closeTimer.remainingTime();
        _closeTimer.stop();

        // Если времени осталось меньше 0, значит двери успели закрыться, пока мы обрабатывали сигнал
        if (timer < 0)
            this->_openTimer.start(DOOR_TIME);
        else
            this->_openTimer.start(DOOR_TIME - timer);
    }

    qInfo() << "Двери открываются...";
    this->_state = OPENING;
}

void Doors::close()
{
    // Если двери до этого не закрывались, выходим
    if (this->_state != CLOSING)
        return;

    this->_state = CLOSED;
    qInfo() << "[*] Двери закрылись!";

    // Посылаем сигнал о закрытии
    emit doorClosed();
}

void Doors::startClosing()
{
    // Если двери до этого не открыты, закрывать не можем
    if (this->_state != OPEN)
        return;

    this->_state = CLOSING;
    qInfo() << "Двери закрываются...";

    // Запуск таймера на закрытие двери
    this->_closeTimer.start(DOOR_TIME);
}
