#ifndef CABIN_H
#define CABIN_H
#include "config.hpp"
#include "doors_new/doors.h"
#include <QObject>
#include <QTimer>

class Cabin : public QObject
{
    Q_OBJECT

public:
    explicit Cabin(cabin_id_t id, QObject *parent = nullptr);
    QTimer _moveTimer;

signals:
    void cabinFinishedBoarding(int floor_n, cabin_id_t cabin_id);
    void cabinFree();

    void cabinStop();
    void passingFloor();
    void openDoors();

public slots:
    void freeCabin();
    void moveCabinUp();
    void moveCabinDown();
    void cabinStartBoarding();
    void cabinStopBoarding();

private:
    enum cabin_state_t
    {
        FREE,
        MOVING_UP,
        MOVING_DOWN,
        BOARDIG_STARTED,
        BOARDING_FINISHED,
    };

    cabin_id_t _id;
    int _cur_floor;

    cabin_state_t _state;
    Doors _doors;
};

#endif // CABIN_H
