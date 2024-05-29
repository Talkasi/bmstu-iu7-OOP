#ifndef LAB_04_MANAGER_HPP
#define LAB_04_MANAGER_HPP
#include "src/button/floor_button/floor_button.hpp"
#include "src/config.hpp"
#include "src/elevator/elevator.hpp"
#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>
#include <array>

using floor_buttons_t = std::array<std::array<std::shared_ptr<FloorButton>, N_DIRECTIONS>, FLOORS>;

class Manager : public QWidget
{
    Q_OBJECT

    using ManagerState = enum
    {
        FREE,
        BUSY
    };

public:
    Manager(floor_buttons_t, elevator_buttons_t, elevator_buttons_t, QWidget *parent = nullptr);
    ~Manager() override = default;

public slots:
    void newVisitPoint(size_t floor, Direction direction);

private:
    ManagerState _state = FREE;
    std::array<Direction, FLOORS> to_visit;

    std::shared_ptr<Elevator> _elevator1;
    std::shared_ptr<Elevator> _elevator2;
    std::array<std::array<std::shared_ptr<FloorButton>, N_DIRECTIONS>, FLOORS> _floor_buttons;
};

#endif // LAB_04_MANAGER_HPP
