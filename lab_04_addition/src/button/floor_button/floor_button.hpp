#ifndef LAB_04_FLOOR_BUTTON_HPP
#define LAB_04_FLOOR_BUTTON_HPP
#include "src/button/base_button.hpp"
#include "src/config.hpp"

class FloorButton : public BaseButton
{
    Q_OBJECT;

public:
    FloorButton(QWidget *parent, size_t floorN, Direction direction);
    ~FloorButton() override = default;

signals:
    void activateSignal(size_t floorN, Direction direction);
    void deactivateSignal();

public slots:
    void activateSlot();
    void deactivateSlot();

private:
    size_t _buttonFloorNumber;
    Direction _direction;
};

#endif // LAB_04_FLOOR_BUTTON_HPP
