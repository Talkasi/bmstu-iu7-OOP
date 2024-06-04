#ifndef LAB_04_FLOOR_BUTTON_HPP
#define LAB_04_FLOOR_BUTTON_HPP
#include "button/base_button.hpp"
#include "config.hpp"

class FloorButton : public BaseButton
{
    Q_OBJECT;

public:
    FloorButton(int floorN, direction_t direction, QWidget *parent = nullptr);
    ~FloorButton() override = default;

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
    direction_t _direction;
};

#endif // LAB_04_FLOOR_BUTTON_HPP
