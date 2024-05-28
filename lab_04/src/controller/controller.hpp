#ifndef LAB_04_CONTROLLER_HPP
#define LAB_04_CONTROLLER_HPP
#include "src/button/button.hpp"
#include "src/config.hpp"
#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

class Controller : public QWidget
{
    Q_OBJECT

    using ControllerState = enum
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller() override = default;

signals:
    void stopCabinSignal();
    void moveCabinSignal(Direction);
    void reachFloorSignal();

public slots:
    void newDestination(int = 1);
    void SearchForDestination(int = 1);
    void reachFloor();

private:
    bool _identifyNewDestination(int &new_destination);
    void _decideDirection();
    void _updateFloor();

private:
    int _curFloor = START_FLOOR;
    int _destinationFloor = START_FLOOR;

    Direction _last_direction = STAY;
    Direction _direction = STAY;

    ControllerState _state = FREE;
    std::vector<bool> _is_visit;

    std::vector<std::shared_ptr<Button>> _buttons_floor;
    std::vector<std::shared_ptr<Button>> _buttons_elevator;
    std::unique_ptr<QVBoxLayout> _layout;
};

#endif // LAB_04_CONTROLLER_HPP
