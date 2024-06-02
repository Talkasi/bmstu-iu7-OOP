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
    // void change_button_state(bool);

public slots:
    void free_system();
    void manage_cabin_call(int floor_n, cabin_id_t cabin_id);
    void manage_floor_call(int floor_n, direction_t direction);

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
