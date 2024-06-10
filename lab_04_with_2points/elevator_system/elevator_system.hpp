#ifndef ELEVATORSYSTEM_H
#define ELEVATORSYSTEM_H
#include "controller/controller.hpp"
#include <QObject>

class ElevatorSystem : public QObject
{
    Q_OBJECT

public:
    explicit ElevatorSystem(QObject *parent = nullptr);

signals:
    void fromFloorCallSignal(int floor_n, direction_t direction);
    void fromCabinCallSignal(int floor_n, cabin_id_t cabin_id);

    // NOTE(Talkasi): For more convinient testing
    void cabinButtonSystemMediatorSignal(int floor_n, cabin_id_t cabin_id, bool is_active);
    void floorButtonSystemMediatorSignal(int floor_n, direction_id_t direction_id, bool is_active);

public slots:
    void free_system_slot();
    void manage_cabin_call_slot(int floor_n, cabin_id_t cabin_id);
    void manage_floor_call_slot(int floor_n, direction_t direction);

    // NOTE(Talkasi): For more convinient testing
    void cabin_button_system_mediator_slot(int floor_n, cabin_id_t cabin_id, bool is_active);
    void floor_button_system_mediator_slot(int floor_n, direction_id_t direction_id, bool is_active);

private:
    enum elevator_system_state_t
    {
        FREE,
        MANAGING_CABIN_CALL,
        MANAGING_FLOOR_CALL
    };

    elevator_system_state_t _state;
    Controller _controller;
};

#endif // ELEVATORSYSTEM_H
