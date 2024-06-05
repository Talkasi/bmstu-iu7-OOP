#ifndef CABIN_H
#define CABIN_H
#include "config.hpp"
#include "doors/doors.hpp"
#include <QObject>
#include <QTimer>

class Cabin : public QObject
{
    Q_OBJECT

public:
    explicit Cabin(cabin_id_t id, QObject *parent = nullptr);
    ~Cabin() override = default;
    QTimer _moveTimer;

    enum cabin_state_t
    {
        BOARD_PASSENGERS,
        MOVING_UP,
        MOVING_DOWN,
        STOP
    };

signals:
    void openDoors();
    void updateFloorSignal();
    void readyToMoveSignal();
    void cabinFinished(int, cabin_id_t);
    void cabinArrived();

public slots:
    void stopCabin();
    void moveCabinUp(int dest_floor);
    void moveCabinDown(int dest_floor);
    void setFree();

private:
    int _cur_floor;
    cabin_state_t _state;
    cabin_id_t _id;
    Doors _doors;
};

#endif // CABIN_H
