#include "controller.hpp"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent), _state(FREE)
{
    for (int cabin_id = 0; cabin_id < N_CABINS; ++cabin_id) {
        cabin[cabin_id] = std::make_unique<Cabin>((cabin_id_t)cabin_id, this);
        cur_floor_i[cabin_id] = START_FLOOR - 1;
        cur_direction[cabin_id] = STAND;

        QObject::connect(cabin[cabin_id].get(), &Cabin::cabinFinishedBoarding, this, &Controller::reach_floor);
        QObject::connect(&cabin[cabin_id]->_moveTimer, SIGNAL(timeout()), this, SLOT(manage_cabin()));
    }

    QObject::connect(this, &Controller::freeCabinSignal, this, [this](cabin_id_t cabin_id) { cabin[cabin_id]->cabinFree(); });
    QObject::connect(this, &Controller::moveCabinUpSignal, this, [this](cabin_id_t cabin_id) { cabin[cabin_id]->moveCabinUp(); });
    QObject::connect(this, &Controller::moveCabinDownSignal, this, [this](cabin_id_t cabin_id) { cabin[cabin_id]->moveCabinDown(); });
    QObject::connect(this, &Controller::stopCabinSignal, this, [this](cabin_id_t cabin_id) { cabin[cabin_id]->cabinStartBoarding(); });

    for (int floor_i = 1; floor_i <= N_FLOORS; ++floor_i) {
        floor_buttons[UP_ID][floor_i - 1] = std::make_shared<FloorButton>(floor_i, UP);
        floor_buttons[DOWN_ID][floor_i - 1] = std::make_shared<FloorButton>(floor_i, DOWN);
        elevator_buttons[FIRST_CABIN_ID][floor_i - 1] = std::make_shared<ElevatorButton>(floor_i, FIRST_CABIN_ID);
        elevator_buttons[SECOND_CABIN_ID][floor_i - 1] = std::make_shared<ElevatorButton>(floor_i, SECOND_CABIN_ID);

        QObject::connect(floor_buttons[UP_ID][floor_i - 1].get(), SIGNAL(activatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(floor_buttons[DOWN_ID][floor_i - 1].get(), SIGNAL(activatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(elevator_buttons[FIRST_CABIN_ID][floor_i - 1].get(), SIGNAL(activatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(elevator_buttons[SECOND_CABIN_ID][floor_i - 1].get(), SIGNAL(activatedSignal()), this, SLOT(manage_cabin()));

        QObject::connect(floor_buttons[UP_ID][floor_i - 1].get(), SIGNAL(deactivatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(floor_buttons[DOWN_ID][floor_i - 1].get(), SIGNAL(deactivatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(elevator_buttons[FIRST_CABIN_ID][floor_i - 1].get(), SIGNAL(deactivatedSignal()), this, SLOT(manage_cabin()));
        QObject::connect(elevator_buttons[SECOND_CABIN_ID][floor_i - 1].get(), SIGNAL(deactivatedSignal()), this, SLOT(manage_cabin()));

        // NOTE(Talkasi): For more convinient testing
        QObject::connect(floor_buttons[UP_ID][floor_i - 1].get(), &FloorButton::activatedSignal, \
                         this, [=]() { floor_button_change(floor_i, UP_ID, true); });
        QObject::connect(floor_buttons[DOWN_ID][floor_i - 1].get(), &FloorButton::activatedSignal, \
                         this, [=]() { floor_button_change(floor_i, DOWN_ID, true); });
        QObject::connect(elevator_buttons[FIRST_CABIN_ID][floor_i - 1].get(), &ElevatorButton::activatedSignal, \
                         this, [=]() { cabin_button_change(floor_i, FIRST_CABIN_ID, true); });
        QObject::connect(elevator_buttons[SECOND_CABIN_ID][floor_i - 1].get(), &ElevatorButton::activatedSignal, \
                         this, [=]() { cabin_button_change(floor_i, SECOND_CABIN_ID, true); });

        // NOTE(Talkasi): For more convinient testing
        QObject::connect(floor_buttons[UP_ID][floor_i - 1].get(), &FloorButton::deactivatedSignal, \
                         this, [=]() { floor_button_change(floor_i, UP_ID, false); });
        QObject::connect(floor_buttons[DOWN_ID][floor_i - 1].get(), &FloorButton::deactivatedSignal, \
                         this, [=]() { floor_button_change(floor_i, DOWN_ID, false); });
        QObject::connect(elevator_buttons[FIRST_CABIN_ID][floor_i - 1].get(), &ElevatorButton::deactivatedSignal, \
                         this, [=]() { cabin_button_change(floor_i, FIRST_CABIN_ID, false); });
        QObject::connect(elevator_buttons[SECOND_CABIN_ID][floor_i - 1].get(), &ElevatorButton::deactivatedSignal, \
                         this, [=]() { cabin_button_change(floor_i, SECOND_CABIN_ID, false); });
    }

    QObject::connect(this, SIGNAL(free_controller_signal()), this, SLOT(free_controller()));
}

static direction_t get_direction(int difference)
{
    if (difference == 0)
        return STAND;

    return difference < 0 ? DOWN : UP;
}

void Controller::new_floor_destination(int floor_n, direction_t direction)
{
    _state = MANAGING_NEW_FLOOR_DEST;

    cabin_id_t desided_cabin_id = FIRST_CABIN_ID;
    int min_possible_distance = N_FLOORS + 1;

    /*
     * Из всех кабин, которые свободны, или едут в направлении желаемого
     * движения и могут заехать на этаж, выбираем ту, которая ближе всего к
     * этажу вызова.
     */
    for (int cur_cabin_id = 0; cur_cabin_id < N_CABINS; ++cur_cabin_id) {
        int cur_distance = floor_n - cur_floor_i[cur_cabin_id];
        direction_t cabin_needs_to_move = get_direction(cur_distance);

        // Очевидный случай:
        // Нам надо наверх (вниз), кабина ниже (выше) нас и едет наверх (вниз)
        if (cur_direction[cur_cabin_id] == STAND ||
            (cabin_needs_to_move == cur_direction[cur_cabin_id] && direction == cur_direction[cur_cabin_id])) {
            if (min_possible_distance > cur_distance) {
                desided_cabin_id = (cabin_id_t)cur_cabin_id;
                min_possible_distance = cur_distance;
            }
        }
    }

    if (min_possible_distance == N_FLOORS + 1) {
        /*
         * В оставшихся случаях:
         * Нам надо наверх (вниз), кабина выше (ниже) нас и едет наверх (вниз)
         * Нам надо наверх (вниз), кабина ниже (выше) нас и едет вниз (наверх)
         * Нам надо наверх (вниз), кабина выше (ниже) нас и едет вниз (наверх)
         *
         * Выбираем ту кабину, которая ближе к заданному этажу и ?
         */

        int min_n_to_visit = N_FLOORS;
        for (int cur_cabin_id = 0; cur_cabin_id < N_CABINS; ++cur_cabin_id) {
            int n_to_visit = 0;
            for (int i = 0; i <= N_FLOORS; ++i)
                n_to_visit += to_visit[cur_cabin_id][i];

            if (n_to_visit < min_n_to_visit) {
                desided_cabin_id = (cabin_id_t)cur_cabin_id;
                min_n_to_visit = n_to_visit;
            }
        }
    }

    to_visit[desided_cabin_id][floor_n - 1] = true;
    qInfo("Решено было отправить на этот вызов кабину №%d.", desided_cabin_id + 1);

    if (direction == UP)
        emit floor_buttons[UP_ID][floor_n - 1]->activateSignal();
    else
        emit floor_buttons[DOWN_ID][floor_n - 1]->activateSignal();
}

void Controller::new_cabin_destination(int floor_n, cabin_id_t cabin_id)
{
    _state = MANAGING_NEW_CABIN_DEST;
    to_visit[cabin_id][floor_n - 1] = true;

    emit elevator_buttons[cabin_id][floor_n - 1]->activateSignal();
}

void Controller::reach_floor(int floor_n, cabin_id_t cabin_id)
{
    if (_state != MANAGING_NEW_CABIN_DEST && _state != MANAGING_NEW_FLOOR_DEST && _state != MANAGING_CABIN)
        return;

    _state = REACH_FLOOR;
    to_visit[cabin_id][floor_n - 1] = false;

    emit elevator_buttons[cabin_id][floor_n - 1]->deactivateSignal();

    if (cur_direction[cabin_id] == UP)
        emit floor_buttons[UP_ID][floor_n - 1]->deactivateSignal();
    else
        emit floor_buttons[DOWN_ID][floor_n - 1]->deactivateSignal();
}

direction_t Controller::get_next_direction(cabin_id_t cabin_id)
{
    if (cur_direction[cabin_id] == STAND)
        return STAND;

    for (int floor_i = cur_floor_i[cabin_id] + cur_direction[cabin_id]; 0 <= floor_i && floor_i < N_FLOORS;
         floor_i += cur_direction[cabin_id]) {
        if (to_visit[cabin_id][floor_i])
            return cur_direction[cabin_id];
    }

    return cur_direction[cabin_id] == UP ? DOWN : UP;
}

int Controller::get_next_visit_point(cabin_id_t cabin_id)
{
    int dst_visit_point = FLOOR_NOT_FOUND;

    if (cur_direction[cabin_id] == STAND) {
        int min_possible_distance = N_FLOORS;

        for (int floor_i = 0; floor_i < N_FLOORS; ++floor_i) {
            if (to_visit[cabin_id][floor_i]) {
                int difference = cur_floor_i[cabin_id] - floor_i;
                if (min_possible_distance > difference) {
                    min_possible_distance = difference;
                    dst_visit_point = floor_i;
                }
            }
        }
    }
    else {
        for (int floor_i = cur_floor_i[cabin_id]; 0 <= floor_i && floor_i < N_FLOORS;
             floor_i += cur_direction[cabin_id]) {

            if (to_visit[cabin_id][floor_i])
                return floor_i;
        }

        for (int floor_i = cur_floor_i[cabin_id] - cur_direction[cabin_id]; 0 <= floor_i && floor_i < N_FLOORS;
             floor_i -= cur_direction[cabin_id]) {

            if (to_visit[cabin_id][floor_i])
                return floor_i;
        }
    }

    return dst_visit_point;
}

void Controller::manage_cabin()
{
    _state = MANAGING_CABIN;

    int cabins_free = 0;
    for (int cabin_id = 0; cabin_id < N_CABINS; ++cabin_id) {
        int dst_floor = get_next_visit_point((cabin_id_t)cabin_id);

        // NOTE(Talkasi): For more convinient testing
        // if (dst_floor != FLOOR_NOT_FOUND)
        //     qInfo("-------------------------------------------------->" \
        //           " Текущая цель лифта №%d — этаж №%d.", cabin_id + 1, dst_floor + 1);
        // else
        //     qInfo("-------------------------------------------------->" \
        //           " Целей лифта №%d нет.", cabin_id + 1);

        if (dst_floor == FLOOR_NOT_FOUND) {
            cur_direction[cabin_id] = STAND;
            emit freeCabinSignal((cabin_id_t)cabin_id);
            ++cabins_free;
        }
        else if (dst_floor > cur_floor_i[cabin_id]) {
            cur_direction[cabin_id] = UP;
            emit moveCabinUpSignal((cabin_id_t)cabin_id);
            ++cur_floor_i[cabin_id];
        }
        else if (dst_floor < cur_floor_i[cabin_id]) {
            cur_direction[cabin_id] = DOWN;
            emit moveCabinDownSignal((cabin_id_t)cabin_id);
            --cur_floor_i[cabin_id];
        }
        else {
            cur_direction[cabin_id] = get_next_direction((cabin_id_t)cabin_id);
            emit stopCabinSignal((cabin_id_t)cabin_id);
        }
    }

    if (cabins_free == N_CABINS)
        emit free_controller_signal();
}

void Controller::free_controller()
{
    if (_state == FREE)
        return;

    _state = FREE;
    emit controller_freed();
}

// NOTE(Talkasi): For more convinient testing
void Controller::floor_button_change(int floor_n, direction_id_t direction_id, bool is_active)
{
    emit controller_floor_button_change(floor_n, direction_id, is_active);
}

       // NOTE(Talkasi): For more convinient testing
void Controller::cabin_button_change(int floor_n, cabin_id_t cabin_id, bool is_active)
{
    emit controller_cabin_button_change(floor_n, cabin_id, is_active);
}
