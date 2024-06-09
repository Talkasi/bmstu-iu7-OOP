#include "mainwindow.h"
#include "config.hpp"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 781);

    QWidget *centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");
    QWidget *gridLayoutWidget = new QWidget(centralwidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(9, 9, 781, 541));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *floor_label = new QLabel(gridLayoutWidget);
    floor_label->setObjectName("floor_buttons_label");
    floor_label->setAlignment(Qt::AlignCenter);
    floor_label->setText(QCoreApplication::translate("MainWindow", "Floor buttons", nullptr));
    gridLayout->addWidget(floor_label, 0, 0, 1, 2);

    for (int i = N_FLOORS; i >= 1; --i) {
        QGridLayout *floor_grid = new QGridLayout();
        floor_grid->setObjectName("floor_grid_" + QString::number(i));

        QLabel *label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::number(i));
        label->setAlignment(Qt::AlignCenter);
        label->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
        floor_grid->addWidget(label, 0, 0, 2, 1);

        floor_buttons[UP_ID][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
        floor_buttons[UP_ID][i - 1]->setObjectName("button_up_" + QString::number(i));
        floor_buttons[UP_ID][i - 1]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\205", nullptr));
        floor_grid->addWidget(floor_buttons[UP_ID][i - 1].get(), 0, 1, 1, 1);

        floor_buttons[DOWN_ID][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
        floor_buttons[DOWN_ID][i - 1]->setObjectName("button_down_" + QString::number(i));
        floor_buttons[DOWN_ID][i - 1]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\207", nullptr));
        floor_grid->addWidget(floor_buttons[DOWN_ID][i - 1].get(), 1, 1, 1, 1);

        QObject::connect(floor_buttons[UP_ID][i - 1].get(), &QPushButton::clicked, \
            [=]() { my_elevator_system.manage_floor_call(i, UP); });

        QObject::connect(floor_buttons[DOWN_ID][i - 1].get(), &QPushButton::clicked, \
            [=]() { my_elevator_system.manage_floor_call(i, DOWN); });

        QObject::connect(&my_elevator_system, SIGNAL(change_floor_button_signal(int, direction_id_t, bool)), \
                         this, SLOT(change_floor_button_style(int, direction_id_t, bool)));

        QObject::connect(&my_elevator_system, SIGNAL(change_floor_button_signal(int, direction_id_t, bool)), \
                         this, SLOT(change_floor_button_style(int, direction_id_t, bool)));

        gridLayout->addLayout(floor_grid, N_FLOORS - i + 1, 0, 1, 2);
    }

    QGridLayout *first_floor_grid = new QGridLayout();
    first_floor_grid->setObjectName("floor_grid_0");

    QLabel *label = new QLabel(gridLayoutWidget);
    label->setObjectName("1");
    label->setAlignment(Qt::AlignCenter);
    label->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    first_floor_grid->addWidget(label, 0, 0, 1, 1);

    // floor_buttons[UP_ID][0] = std::make_shared<QPushButton>(gridLayoutWidget);
    // floor_buttons[UP_ID][0]->setObjectName("button_up_0");
    // floor_buttons[UP_ID][0]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\205", nullptr));
    // first_floor_grid->addWidget(floor_buttons[UP_ID][0].get(), 0, 1, 1, 1);
    // gridLayout->addLayout(first_floor_grid, N_FLOORS, 0, 1, 2);

    QSpacerItem *horizontalSpacer =
        new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

    QLabel *elevator1_label = new QLabel(gridLayoutWidget);
    elevator1_label->setObjectName("floor_buttons_label");
    elevator1_label->setAlignment(Qt::AlignCenter);
    elevator1_label->setText(QCoreApplication::translate("MainWindow", "Elevator 1", nullptr));
    gridLayout->addWidget(elevator1_label, 0, 3, 1, 1);

    QLabel *elevator2_label = new QLabel(gridLayoutWidget);
    elevator2_label->setObjectName("floor_buttons_label");
    elevator2_label->setAlignment(Qt::AlignCenter);
    elevator2_label->setText(QCoreApplication::translate("MainWindow", "Elevator 2", nullptr));
    gridLayout->addWidget(elevator2_label, 0, 4, 1, 1);

    auto &tmp_elevator_system = my_elevator_system;
    for (int i = N_FLOORS; i > 0; --i) {
        for (int cabin_id = 0; cabin_id < N_CABINS; ++cabin_id) {
            elevator_buttons[cabin_id][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
            elevator_buttons[cabin_id][i - 1]->setObjectName("button_elevator1_" + QString::number(i));
            elevator_buttons[cabin_id][i - 1]->setText(
                QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
            elevator_buttons[cabin_id][i - 1]->setMinimumSize(QSize(0, 50));
            gridLayout->addWidget(elevator_buttons[cabin_id][i - 1].get(), N_FLOORS - i + 1, 3 + cabin_id, 1, 1);

            QObject::connect(elevator_buttons[cabin_id][i - 1].get(), &QPushButton::clicked, \
                [=]() { my_elevator_system.manage_cabin_call(i, (cabin_id_t)cabin_id); });

            QObject::connect(&my_elevator_system, SIGNAL(change_cabin_button_signal(int, cabin_id_t, bool)), \
                             this, SLOT(change_cabin_button_style(int, cabin_id_t, bool)));
        }
    }

    this->setCentralWidget(centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_floor_button_style(int floor_n, direction_id_t direction_id, bool is_active)
{
    if (is_active) {
        floor_buttons[direction_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
        this->update();
    } else {
        floor_buttons[direction_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);
        this->update();
    }
}

void MainWindow::change_cabin_button_style(int floor_n, cabin_id_t cabin_id, bool is_active)
{
    if (is_active) {
        elevator_buttons[cabin_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
        this->update();
    } else {
        elevator_buttons[cabin_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);
        this->update();
    }
}
