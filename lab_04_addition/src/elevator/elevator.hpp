#ifndef LAB_04_ELEVATOR_HPP
#define LAB_04_ELEVATOR_HPP
#include "src/cabin/cabin.hpp"
#include "src/controller/controller.hpp"
#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT

public:
    explicit Elevator(elevator_buttons_t buttons, QObject *parent = nullptr);
    ~Elevator() = default;

private:
    std::shared_ptr<Controller> _controller;
    Cabin _cabin;
};

#endif // LAB_04_ELEVATOR_HPP
