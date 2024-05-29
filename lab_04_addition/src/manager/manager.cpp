#include "manager.hpp"
#include <QDebug>
#include <QLabel>

Manager::Manager(floor_buttons_t floor_buttons, elevator_buttons_t elevator1_buttons,
                 elevator_buttons_t elevator2_buttons, QWidget *parent)
    : QWidget(parent)
{
    _elevator1 = std::make_shared<Elevator>(elevator1_buttons);
    _elevator2 = std::make_shared<Elevator>(elevator2_buttons);
    _floor_buttons = floor_buttons;

    QObject::connect(_floor_buttons[0][UP].get(), SIGNAL(activateSignal(size_t, Direction)), this,
                     SLOT(newVisitPoint(size_t, Direction)));
    for (int i = 1; i < FLOORS; ++i) {
        QObject::connect(_floor_buttons[i][UP].get(), SIGNAL(activateSignal(size_t, Direction)), this,
                         SLOT(newVisitPoint(size_t, Direction)));
        QObject::connect(_floor_buttons[i][DOWN].get(), SIGNAL(activateSignal(size_t, Direction)), this,
                         SLOT(newVisitPoint(size_t, Direction)));
    }
}

void Manager::newVisitPoint(size_t floor, Direction direction = ANY)
{
    this->to_visit[floor - 1] = direction;
}

// /usr/include/c++/13/bits/stl_construct.h:119: error: undefined reference to
// `Manager::Manager(std::array<std::array<std::shared_ptr<FloorButton>, 2ul>, 5ul>,
// std::array<std::shared_ptr<ElevatorButton>, 5ul>, std::array<std::shared_ptr<ElevatorButton>, 5ul>, QWidget*)'
