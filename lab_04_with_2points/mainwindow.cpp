#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(client_call_from_cabin(int, cabin_id_t)), &my_elevator_system,
                     SLOT(manage_cabin_call(int, cabin_id_t)));
    QObject::connect(this, SIGNAL(client_call_from_floor(int, direction_t)), &my_elevator_system,
                     SLOT(manage_floor_call(int, direction_t)));

    // QObject::connect(&my_elevator_system, SIGNAL(change_button_state(bool)), ui->el1_floor1,
    // SLOT(on_el1_floor1_toggled(bool))); QObject::connect(&my_elevator_system, SIGNAL(change_button_state(bool)),
    // ui->el1_floor1, SLOT(on_el1_floor1_toggled(bool))); QObject::connect(&my_elevator_system,
    // SIGNAL(change_button_state(bool)), ui->el1_floor1, SLOT(on_el1_floor1_toggled(bool)));

    qInfo("-> Начало симуляции. Оба лифта находятся на 1м этаже с закрытыми дверями.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_el1_floor10_clicked()
{
    emit client_call_from_cabin(10, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor9_clicked()
{
    emit client_call_from_cabin(9, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor8_clicked()
{
    emit client_call_from_cabin(8, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor7_clicked()
{
    emit client_call_from_cabin(7, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor6_clicked()
{
    emit client_call_from_cabin(6, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor5_clicked()
{
    emit client_call_from_cabin(5, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor4_clicked()
{
    emit client_call_from_cabin(4, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor3_clicked()
{
    emit client_call_from_cabin(3, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor2_clicked()
{
    emit client_call_from_cabin(2, FIRST_CABIN_ID);
}

void MainWindow::on_el1_floor1_clicked()
{
    emit client_call_from_cabin(1, FIRST_CABIN_ID);
}

void MainWindow::on_el2_floor10_clicked()
{
    emit client_call_from_cabin(10, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor9_clicked()
{
    emit client_call_from_cabin(9, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor8_clicked()
{
    emit client_call_from_cabin(8, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor7_clicked()
{
    emit client_call_from_cabin(7, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor6_clicked()
{
    emit client_call_from_cabin(6, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor5_clicked()
{
    emit client_call_from_cabin(5, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor4_clicked()
{
    emit client_call_from_cabin(4, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor3_clicked()
{
    emit client_call_from_cabin(3, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor2_clicked()
{
    emit client_call_from_cabin(2, SECOND_CABIN_ID);
}

void MainWindow::on_el2_floor1_clicked()
{
    emit client_call_from_cabin(1, SECOND_CABIN_ID);
}

void MainWindow::on_floor10_down_clicked()
{
    emit client_call_from_floor(10, DOWN);
}

void MainWindow::on_floor9_down_clicked()
{
    emit client_call_from_floor(9, DOWN);
}

void MainWindow::on_floor8_down_clicked()
{
    emit client_call_from_floor(8, DOWN);
}

void MainWindow::on_floor7_down_clicked()
{
    emit client_call_from_floor(7, DOWN);
}

void MainWindow::on_floor6_down_clicked()
{
    emit client_call_from_floor(6, DOWN);
}

void MainWindow::on_floor5_down_clicked()
{
    emit client_call_from_floor(5, DOWN);
}

void MainWindow::on_floor4_down_clicked()
{
    emit client_call_from_floor(4, DOWN);
}

void MainWindow::on_floor3_down_clicked()
{
    emit client_call_from_floor(3, DOWN);
}

void MainWindow::on_floor2_down_clicked()
{
    emit client_call_from_floor(2, DOWN);
}

void MainWindow::on_floor9_up_clicked()
{
    emit client_call_from_floor(9, UP);
}

void MainWindow::on_floor8_up_clicked()
{
    emit client_call_from_floor(8, UP);
}

void MainWindow::on_floor7_up_clicked()
{
    emit client_call_from_floor(7, UP);
}

void MainWindow::on_floor6_up_clicked()
{
    emit client_call_from_floor(6, UP);
}

void MainWindow::on_floor5_up_clicked()
{
    emit client_call_from_floor(5, UP);
}

void MainWindow::on_floor4_up_clicked()
{
    emit client_call_from_floor(4, UP);
}

void MainWindow::on_floor3_up_clicked()
{
    emit client_call_from_floor(3, UP);
}

void MainWindow::on_floor2_up_clicked()
{
    emit client_call_from_floor(2, UP);
}

void MainWindow::on_floor1_up_clicked()
{
    emit client_call_from_floor(1, UP);
}

// static void update_button_state(QPushButton *button, bool checked) {
//     if (checked) {
//         button->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
//         button->update();
//         button->setDisabled(true);
//     } else {
//         button->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);
//         button->update();
//         button->setEnabled(true);
//     }
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el1_floor1, checked);
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el_floor1, checked);
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el1_floor1, checked);
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el1_floor1, checked);
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el1_floor1, checked);
// }

// void MainWindow::on_el1_floor1_toggled(bool checked)
// {
//     update_button_state(ui->el1_floor1, checked);
// }
