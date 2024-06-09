#include "elevator_system.hpp"

ElevatorSystem::ElevatorSystem(QObject *parent) : QObject(parent), _state(FREE)
{
    QObject::connect(this, SIGNAL(from_floor_call(int, direction_t)), &_controller, SLOT(new_floor_destination(int, direction_t)));
    QObject::connect(this, SIGNAL(from_cabin_call(int, cabin_id_t)), &_controller, SLOT(new_cabin_destination(int, cabin_id_t)));
    QObject::connect(&_controller, SIGNAL(controller_freed()), this, SLOT(free_system()));

    // NOTE(Talkasi): For more convinient testing
    QObject::connect(&_controller, SIGNAL(controller_cabin_button_change(int, cabin_id_t, bool)), this, SLOT(system_cabin_button_change(int, cabin_id_t, bool)));
    QObject::connect(&_controller, SIGNAL(controller_floor_button_change(int, direction_id_t, bool)), this, SLOT(system_floor_button_change(int, direction_id_t, bool)));
}

void ElevatorSystem::manage_cabin_call(int floor_n, cabin_id_t elevator_id)
{
    // qInfo() << floor_n << elevator_id;

    _state = MANAGING_CABIN_CALL;
    emit from_cabin_call(floor_n, elevator_id);
}

void ElevatorSystem::manage_floor_call(int floor_n, direction_t direction)
{
    // qInfo() << floor_n << direction;

    _state = MANAGING_FLOOR_CALL;
    emit from_floor_call(floor_n, direction);
}

void ElevatorSystem::free_system()
{
    _state = FREE;
}

// NOTE(Talkasi): For more convinient testing
void ElevatorSystem::system_cabin_button_change(int floor_n, cabin_id_t cabin_id, bool is_active)
{
    emit change_cabin_button_signal(floor_n, cabin_id, is_active);
}

// NOTE(Talkasi): For more convinient testing
void ElevatorSystem::system_floor_button_change(int floor_n, direction_id_t direction_id, bool is_active)
{
    emit change_floor_button_signal(floor_n, direction_id, is_active);
}
