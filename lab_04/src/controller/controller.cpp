#include "controller.hpp"

#include <QDebug>
#include <QLabel>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    this->_layout = std::make_unique<QVBoxLayout>();
    this->setLayout(this->_layout.get());

    auto new_button = std::make_shared<Button>(FLOORS + 1);
    new_button->setStyleSheet("background-color:white; color:black");
    new_button->setText("Floor Buttons");
    new_button->setDisabled(true);

    this->_buttons_floor.insert(this->_buttons_floor.begin(), new_button);
    _layout->addWidget(dynamic_cast<QPushButton *>(new_button.get()));

    for (size_t i = 0; i < FLOORS; i++) {
        auto new_button = std::make_shared<Button>(FLOORS - i);
        new_button->setText(QString::number(FLOORS - i));
        new_button->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);

        this->_buttons_floor.insert(this->_buttons_floor.begin(), new_button);
        _layout->addWidget(dynamic_cast<QPushButton *>(new_button.get()));
        _is_visit.push_back(false);

        // Соединяем сигнал нажатия кнопки с добавлением этаж в цели
        QObject::connect(new_button.get(), SIGNAL(activateSignal(int)), this, SLOT(newDestination(int)));
    }

    auto elevator_button = std::make_shared<Button>(FLOORS + 1);
    elevator_button->setStyleSheet("background-color:white; color:black");
    elevator_button->setText("Elevator Buttons");
    elevator_button->setDisabled(true);

    this->_buttons_elevator.insert(this->_buttons_elevator.begin(), elevator_button);
    _layout->addWidget(dynamic_cast<QPushButton *>(elevator_button.get()));

    for (size_t i = 0; i < FLOORS; i++) {
        auto button = std::make_shared<Button>(FLOORS - i);
        button->setText(QString::number(FLOORS - i));
        button->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);

        this->_buttons_elevator.insert(this->_buttons_elevator.begin(), button);
        _layout->addWidget(dynamic_cast<QPushButton *>(button.get()));
        _is_visit.push_back(false);

        // Соединяем сигнал нажатия кнопки с добавлением этаж в цели
        QObject::connect(button.get(), SIGNAL(activateSignal(int)), this, SLOT(newDestination(int)));
    }

    QObject::connect(this, SIGNAL(reachFloorSignal()), this, SLOT(reachFloor()));
}

void Controller::newDestination(int floor)
{
    this->_state = BUSY;
    // if (got_new) {
    this->_is_visit[floor - 1] = true;

    _identifyNewDestination(floor);
    _destinationFloor = floor;
    _decideDirection();
    if (_direction == STAY) {
        emit reachFloorSignal();
    }
    else {
        emit moveCabinSignal(_direction);
    }
    // }
    // else if (_identifyNewDestination(floor)) {
    //     _destinationFloor = floor;
    //     _decideDirection();

    //     if (_direction != STAY) {
    //         _updateFloor();
    //         emit moveCabinSignal();
    //     }
    //     else {
    //         emit reachFloorSignal();
    //     }
    // }
}

void Controller::SearchForDestination(int floor)
{
    this->_state = BUSY;
    if (_identifyNewDestination(floor)) {
        _destinationFloor = floor;
        _decideDirection();

        if (_direction != STAY) {
            _updateFloor();
            emit moveCabinSignal(_direction);
        }
        else {
            emit reachFloorSignal();
        }
    }
}

void Controller::_decideDirection()
{
    if (_destinationFloor > _curFloor) {
        _direction = UP;
    }
    else if (_destinationFloor < _curFloor) {
        _direction = DOWN;
    }
    else {
        _last_direction = _direction;
        _direction = STAY;
    }
}

bool Controller::_identifyNewDestination(int &new_target)
{
    bool rc = false;

    Direction dir;

    if (_direction != STAY)
        dir = _direction;
    else
        dir = (_last_direction == STAY) ? UP : _last_direction;

    for (int i = _curFloor; !rc && i <= FLOORS && i > 0; i = i + dir)
        if (_is_visit[i - 1]) {
            new_target = i;
            rc = true;
        }

    if (!rc) {
        dir = ((dir == UP) ? DOWN : UP);

        for (int i = _curFloor; !rc && i <= FLOORS && i > 0; i = i + dir) {
            if (_is_visit[i - 1]) {
                new_target = i;
                rc = true;
            }
        }
    }

    return rc;
}

void Controller::reachFloor()
{
    // Если контроллер не занят, выходим [лифт не движется]
    if (_state != BUSY)
        return;

    qInfo() << "[!] Лифт приехал на этаж № " << _destinationFloor;

    emit _buttons_floor[_destinationFloor - 1]->deactivateSignal();
    emit _buttons_elevator[_destinationFloor - 1]->deactivateSignal();

    _is_visit[_destinationFloor - 1] = false; // посещать его уже не надо

    // проверим, есть ли ещё цели
    if (_identifyNewDestination(_destinationFloor)) {
        emit stopCabinSignal();
    }
    else {
        // Целей нет
        _state = FREE; // Контроллер освободился
        emit stopCabinSignal();
    }
}

void Controller::_updateFloor()
{
    qInfo() << "... Лифт едет на этаж № " << _curFloor;
    _curFloor += _direction;
}
