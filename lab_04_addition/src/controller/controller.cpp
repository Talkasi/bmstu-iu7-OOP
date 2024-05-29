#include "controller.hpp"
#include <QDebug>
#include <QLabel>

Controller::Controller(elevator_buttons_t elevator_buttons, QWidget *parent) : QWidget(parent)
{
    for (size_t i = 0; i < FLOORS; i++) {
        QObject::connect(elevator_buttons[i].get(), SIGNAL(activateSignal(size_t)), this, SLOT(newVisitPoint(size_t)));
    }

    // QObject::connect(this, SIGNAL(reachFloorSignal()), this, SLOT(reachFloor()));
}

void Controller::newVisitPoint(size_t floor)
{
    to_visit[floor - 1] = true;
}
// void Controller::newDestination(bool got_new, int floor)
// {
//     this->_state = BUSY;
//     if (got_new) {
//         this->_is_visit[floor - 1] = true;

//         _identifyNewDestination(floor);
//         _destinationFloor = floor;
//         _decideDirection();
//         if (_direction == STAY) {
//             emit reachFloorSignal();
//         }
//         else {
//             emit moveCabinSignal();
//         }
//     }
//     else if (_identifyNewDestination(floor)) {
//         _destinationFloor = floor;
//         _decideDirection();

//         if (_direction != STAY) {
//             _updateFloor();
//             emit moveCabinSignal();
//         }
//         else {
//             emit reachFloorSignal();
//         }
//     }
// }

// void Controller::_decideDirection()
// {
//     if (_destinationFloor > _curFloor) {
//         _direction = UP;
//     }
//     else if (_destinationFloor < _curFloor) {
//         _direction = DOWN;
//     }
//     else {
//         _last_direction = _direction;
//         _direction = STAY;
//     }
// }

// bool Controller::_identifyNewDestination(int &new_target)
// {
//     bool rc = false;

//     Direction dir;

//     if (_direction != STAY)
//         dir = _direction;
//     else
//         dir = (_last_direction == STAY) ? UP : _last_direction;

//     for (int i = _curFloor; !rc && i <= FLOORS && i > 0; i = i + dir)
//         if (_is_visit[i - 1]) {
//             new_target = i;
//             rc = true;
//         }

//     if (!rc) {
//         dir = ((dir == UP) ? DOWN : UP);

//         for (int i = _curFloor; !rc && i <= FLOORS && i > 0; i = i + dir) {
//             if (_is_visit[i - 1]) {
//                 new_target = i;
//                 rc = true;
//             }
//         }
//     }

//     return rc;
// }

// void Controller::reachFloor()
// {
//     // Если контроллер не занят, выходим [лифт не движется]
//     if (_state != BUSY)
//         return;

//     qInfo() << "[!] Лифт приехал на этаж № " << _destinationFloor;

//     emit _buttons_floor[_destinationFloor - 1]->deactivateSignal();
//     emit _buttons_elevator[_destinationFloor - 1]->deactivateSignal();

//     _is_visit[_destinationFloor - 1] = false; // посещать его уже не надо

//     // проверим, есть ли ещё цели
//     if (_identifyNewDestination(_destinationFloor)) {
//         emit stopCabinSignal();
//     }
//     else {
//         // Целей нет
//         _state = FREE; // Контроллер освободился
//         emit stopCabinSignal();
//     }
// }

// void Controller::_updateFloor()
// {
//     qInfo() << "... Лифт едет на этаж № " << _curFloor;
//     _curFloor += _direction;
// }
