#include "button.hpp"
#include "src/config.hpp"
#include <QtDebug>

Button::Button(size_t floorN, QWidget *parent) : QPushButton(parent)
{
    // Соединяем сигнал нажатия кнопки с обработчиком нажатия
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(activateSlot()));

    // Соединяем сигнал деактивации кнопки с обработчиком деактивации
    // (Кнопка отключается, когда лифт приезжает на нужный этаж)
    QObject::connect(this, SIGNAL(deactivateSignal()), this, SLOT(deactivateSlot()));

    _state = INACTIVE;
    _buttonFloorNumber = floorN;
}

void Button::activateSlot()
{
    // Если кнопка уже нажата, выходим
    if (this->_state == ACTIVE)
        return;

    // Делаем кнопку активной
    this->_state = ACTIVE;
    this->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
    this->update();

    // Подаем сигнал о необходимости заехать на этаж
    qInfo() << "[!] Вызов на этаж №" << this->_buttonFloorNumber;
    emit activateSignal(this->_buttonFloorNumber);
}

void Button::deactivateSlot()
{
    // Если кнопка уже деактивирована, выходим
    if (this->_state == INACTIVE)
        return;

    // Делаем кнопку неактивной
    this->_state = INACTIVE;
    this->setStyleSheet((QString("background-color:") + COLOR_BUTTON_INACTIVE));
    this->update();
}
