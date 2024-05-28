#ifndef LAB_04_ELEVATOR_HPP
#define LAB_04_ELEVATOR_HPP
#include "src/cabin/cabin.hpp"
#include "src/controller/controller.hpp"
#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT

public:
    explicit Elevator(QObject *parent = nullptr);
    ~Elevator() = default;

    QWidget *widget();

private:
    Controller _controller;
    Cabin _cabin;
};

#endif // LAB_04_ELEVATOR_HPP
