#ifndef LAB_04_ELEVATOR_BUTTON_HPP
#define LAB_04_ELEVATOR_BUTTON_HPP
#include "button/base_button.hpp"
#include "config.hpp"

class ElevatorButton : public BaseButton
{
    Q_OBJECT;

public:
    ElevatorButton(int FloorN, cabin_id_t cabin_id, QWidget *parent = nullptr);
    ~ElevatorButton() override = default;

signals:
    void activateSignal();
    void deactivateSignal();

    void activatedSignal();
    void deactivatedSignal();

public slots:
    void activateSlot();
    void deactivateSlot();

private:
    int _buttonFloorNumber;
    cabin_id_t _cabin_id;
};

#endif // LAB_04_ELEVATOR_BUTTON_HPP
