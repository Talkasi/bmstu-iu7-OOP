#include "elevator.hpp"

Elevator::Elevator(elevator_buttons_t buttons, QObject *parent) : QObject(parent)
{
    _controller = std::make_shared<Controller>(buttons);

    // QObject::connect(&_cabin, SIGNAL(cabinFinished(bool)), &_controller, SLOT(newDestination(bool)));
    // QObject::connect(&_controller, SIGNAL(moveCabinSignal()), &_cabin, SLOT(moveCabin()));
    // QObject::connect(&_controller, SIGNAL(stopCabinSignal()), &_cabin, SLOT(stopCabin()));
}
