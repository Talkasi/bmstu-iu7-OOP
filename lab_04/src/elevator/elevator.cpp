#include "elevator.hpp"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    _controller.setStyleSheet("background-color:lightblue");

    QObject::connect(&_cabin, SIGNAL(cabinFinished()), &_controller, SLOT(SearchForDestination()));
    QObject::connect(&_controller, SIGNAL(moveCabinSignal(Direction)), &_cabin, SLOT(moveCabin(Direction)));
    QObject::connect(&_controller, SIGNAL(stopCabinSignal()), &_cabin, SLOT(stopCabin()));
}

QWidget *Elevator::widget()
{
    return &_controller;
}
