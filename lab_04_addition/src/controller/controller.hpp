#ifndef LAB_04_CONTROLLER_HPP
#define LAB_04_CONTROLLER_HPP
#include "src/button/elevator_button/elevator_button.hpp"
#include "src/config.hpp"
#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>

using elevator_buttons_t = std::array<std::shared_ptr<ElevatorButton>, FLOORS>;

class Controller : public QWidget
{
    Q_OBJECT

    using ControllerState = enum
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(elevator_buttons_t _elevator_button, QWidget *parent = nullptr);
    ~Controller() override = default;

signals:
    // void stopCabinSignal();
    // void moveCabinSignal();
    // void reachFloorSignal();

public slots:
    void newVisitPoint(size_t floor);
    // void newDestination(bool, int = 1);
    // void reachFloor();

private:
    // bool _identifyNewDestination(int &new_destination);
    // void _decideDirection();
    // void _updateFloor();

private:
    int _curFloor = START_FLOOR;
    int _destinationFloor = START_FLOOR;

    Direction _last_direction = NONE;
    Direction _direction = NONE;

    ControllerState _state = FREE;

    std::array<bool, FLOORS> to_visit;
    std::vector<std::shared_ptr<ElevatorButton>> _elevator_button;
};

#endif // LAB_04_CONTROLLER_HPP
