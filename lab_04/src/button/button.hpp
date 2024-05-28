#ifndef LAB_04_BUTTON_HPP
#define LAB_04_BUTTON_HPP
#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT;

    using ButtonState = enum
    {
        ACTIVE,
        INACTIVE
    };

public:
    Button(size_t floorN, QWidget *parent = nullptr);
    ~Button() override = default;

signals:
    void activateSignal(int);
    void deactivateSignal();

public slots:
    void activateSlot();
    void deactivateSlot();

private:
    ButtonState _state;
    size_t _buttonFloorNumber;
};

#endif // LAB_04_BUTTON_HPP
