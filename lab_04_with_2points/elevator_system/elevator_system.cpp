#include "elevator_system.hpp"

ElevatorSystem::ElevatorSystem(QObject *parent) : QObject(parent), _state(FREE)
{
    QObject::connect(this, SIGNAL(from_floor_call(int, direction_t)), &_controller,
                     SLOT(new_floor_destination(int, direction_t)));
    QObject::connect(this, SIGNAL(from_cabin_call(int, cabin_id_t)), &_controller,
                     SLOT(new_cabin_destination(int, cabin_id_t)));
    QObject::connect(&_controller, SIGNAL(controller_freed()), this, SLOT(free_system()));
}

void ElevatorSystem::manage_cabin_call(int floor_n, cabin_id_t elevator_id)
{
    _state = MANAGING_CABIN_CALL;
    emit from_cabin_call(floor_n, elevator_id);
}

void ElevatorSystem::manage_floor_call(int floor_n, direction_t direction)
{
    _state = MANAGING_FLOOR_CALL;
    emit from_floor_call(floor_n, direction);
}

void ElevatorSystem::free_system()
{
    _state = FREE;
}
