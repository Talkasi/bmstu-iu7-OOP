#include "floor_button.hpp"
#include "src/config.hpp"
#include <QtDebug>

FloorButton::FloorButton(QWidget *parent, size_t FloorN, Direction direction) : BaseButton(parent)
{
    // Соединяем сигнал нажатия кнопки с обработчиком нажатия
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(activateSlot()));

    // Соединяем сигнал деактивации кнопки с обработчиком деактивации
    // (Кнопка отключается, когда лифт приезжает на нужный этаж)
    QObject::connect(this, SIGNAL(deactivateSignal()), this, SLOT(deactivateSlot()));

    _buttonFloorNumber = FloorN;
    _direction = direction;
}

void FloorButton::activateSlot()
{
    // Если кнопка уже нажата, выходим
    if (this->_state == ACTIVE)
        return;

    // Делаем кнопку активной
    this->_state = ACTIVE;
    this->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
    this->update();

    // Подаем сигнал о необходимости заехать на этаж
    QString direction = (_direction == UP) ? "наверх" : "вниз";
    qInfo() << "[!] Ожидающий лифта на этаже №" << this->_buttonFloorNumber << "хочет поехать" << direction;
    emit activateSignal(this->_buttonFloorNumber, this->_direction);
}

void FloorButton::deactivateSlot()
{
    // Если кнопка уже деактивирована, выходим
    if (this->_state == INACTIVE)
        return;

    // Делаем кнопку неактивной
    this->_state = INACTIVE;
    this->setStyleSheet((QString("background-color:") + COLOR_BUTTON_INACTIVE));
    this->update();
}
