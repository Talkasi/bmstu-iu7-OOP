#ifndef LAB_04_CABIN_HPP
#define LAB_04_CABIN_HPP
#include "src/config.hpp"
#include "src/doors/doors.hpp"
#include <QObject>
#include <QTimer>

class Cabin : public QObject
{
    Q_OBJECT

    using cabinState = enum
    {
        WAIT,
        MOVING_UP,
        MOVING_DOWN,
        STOP
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() override = default;

signals:
    void openDoors();
    void updateFloorSignal();
    void readyToMoveSignal();
    void cabinFinished(int = 1);

public slots:
    void stopCabin();
    void moveCabin(Direction direction);
    void setFree();

private:
    cabinState _state;
    Doors _doors;
    QTimer _moveTimer;
};

#endif // LAB_04_CABIN_HPP
