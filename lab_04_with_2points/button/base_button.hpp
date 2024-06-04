#ifndef LAB_04_BASE_BUTTON_HPP
#define LAB_04_BASE_BUTTON_HPP
#include <QPushButton>

enum ButtonState
{
    ACTIVE,
    INACTIVE
};

class BaseButton : public QObject
{
    Q_OBJECT;

public:
    BaseButton(QWidget *parent = nullptr);
    ~BaseButton() override = default;

protected:
    ButtonState _state;
};

#endif // LAB_04_BASE_BUTTON_HPP
