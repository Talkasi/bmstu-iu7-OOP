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
    void from_floor_call(int floor_n, direction_t direction);
    void from_cabin_call(int floor_n, cabin_id_t cabin_id);

    // NOTE(Talkasi): For more convinient testing
    void change_cabin_button_signal(int floor_n, cabin_id_t cabin_id, bool is_active);
    void change_floor_button_signal(int floor_n, direction_id_t direction_id, bool is_active);

public slots:
    void free_system();
    void manage_cabin_call(int floor_n, cabin_id_t cabin_id);
    void manage_floor_call(int floor_n, direction_t direction);

    // NOTE(Talkasi): For more convinient testing
    void system_cabin_button_change(int floor_n, cabin_id_t cabin_id, bool is_active);
    void system_floor_button_change(int floor_n, direction_id_t direction_id, bool is_active);

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
