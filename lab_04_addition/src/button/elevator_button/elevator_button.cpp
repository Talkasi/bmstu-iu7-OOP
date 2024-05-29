#include "elevator_button.hpp"
#include "src/config.hpp"
#include <QtDebug>

ElevatorButton::ElevatorButton(QWidget *parent, size_t FloorN) : BaseButton(parent)
{
    // Соединяем сигнал нажатия кнопки с обработчиком нажатия
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(activateSlot()));

    // Соединяем сигнал деактивации кнопки с обработчиком деактивации
    // (Кнопка отключается, когда лифт приезжает на нужный этаж)
    QObject::connect(this, SIGNAL(deactivateSignal()), this, SLOT(deactivateSlot()));

    _buttonFloorNumber = FloorN;
}

void ElevatorButton::activateSlot()
{
    // Если кнопка уже нажата, выходим
    if (this->_state == ACTIVE)
        return;

    // Делаем кнопку активной
    this->_state = ACTIVE;
    this->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
    this->update();

    // Подаем сигнал о необходимости заехать на этаж
    qInfo() << "[!] Пассажир в кабине лифта хочет на этаж №" << this->_buttonFloorNumber;
    emit activateSignal(this->_buttonFloorNumber);
}

void ElevatorButton::deactivateSlot()
{
    // Если кнопка уже деактивирована, выходим
    if (this->_state == INACTIVE)
        return;

    // Делаем кнопку неактивной
    this->_state = INACTIVE;
    this->setStyleSheet((QString("background-color:") + COLOR_BUTTON_INACTIVE));
    this->update();
}
