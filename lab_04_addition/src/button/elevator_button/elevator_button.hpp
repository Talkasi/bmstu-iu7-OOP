#ifndef LAB_04_ELEVATOR_BUTTON_HPP
#define LAB_04_ELEVATOR_BUTTON_HPP
#include "src/button/base_button.hpp"

class ElevatorButton : public BaseButton
{
    Q_OBJECT;

public:
    ElevatorButton(QWidget *parent, size_t FloorN);
    ~ElevatorButton() override = default;

signals:
    void activateSignal(size_t);
    void deactivateSignal();

public slots:
    void activateSlot();
    void deactivateSlot();

private:
    size_t _buttonFloorNumber;
    // size_t _elevator_number;
};

#endif // LAB_04_ELEVATOR_BUTTON_HPP
