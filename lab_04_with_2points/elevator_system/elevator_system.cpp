#include "elevator_system.hpp"

ElevatorSystem::ElevatorSystem(QObject *parent) : QObject(parent), _state(FREE)
{
    QObject::connect(this, SIGNAL(fromFloorCallSignal(int, direction_t)), &_controller, SLOT(new_floor_destination_slot(int, direction_t)));
    QObject::connect(this, SIGNAL(fromCabinCallSignal(int, cabin_id_t)), &_controller, SLOT(new_cabin_destination_slot(int, cabin_id_t)));
    QObject::connect(&_controller, SIGNAL(controllerFreedSignal()), this, SLOT(free_system_slot()));

    // NOTE(Talkasi): For more convinient testing
    QObject::connect(&_controller, SIGNAL(cabinButtonControllerMediatorSignal(int, cabin_id_t, bool)), this,
                     SLOT(cabin_button_system_mediator_slot(int, cabin_id_t, bool)));
    QObject::connect(&_controller, SIGNAL(floorButtonControllerMediatorSignal(int, direction_id_t, bool)), this,
                     SLOT(floor_button_system_mediator_slot(int, direction_id_t, bool)));
}

void ElevatorSystem::manage_cabin_call_slot(int floor_n, cabin_id_t elevator_id)
{
    _state = MANAGING_CABIN_CALL;
    emit fromCabinCallSignal(floor_n, elevator_id);
}

void ElevatorSystem::manage_floor_call_slot(int floor_n, direction_t direction)
{
    _state = MANAGING_FLOOR_CALL;
    emit fromFloorCallSignal(floor_n, direction);
}

void ElevatorSystem::free_system_slot()
{
    _state = FREE;
}

// NOTE(Talkasi): For more convinient testing
void ElevatorSystem::cabin_button_system_mediator_slot(int floor_n, cabin_id_t cabin_id, bool is_active)
{
    emit cabinButtonSystemMediatorSignal(floor_n, cabin_id, is_active);
}

// NOTE(Talkasi): For more convinient testing
void ElevatorSystem::floor_button_system_mediator_slot(int floor_n, direction_id_t direction_id, bool is_active)
{
    emit floorButtonSystemMediatorSignal(floor_n, direction_id, is_active);
}
