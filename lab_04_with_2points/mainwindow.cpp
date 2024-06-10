#include "mainwindow.h"
#include "config.hpp"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(800, 781);

    QWidget *centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");
    QWidget *gridLayoutWidget = new QWidget(centralwidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(9, 9, 781, 733));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *floor_label = new QLabel(gridLayoutWidget);
    floor_label->setObjectName("floor_label");
    floor_label->setAlignment(Qt::AlignCenter);
    floor_label->setText(QCoreApplication::translate("MainWindow", "Этажи", nullptr));
    gridLayout->addWidget(floor_label, 0, 0, 1, 1);

    for (int i = N_FLOORS - 1; i > 1; --i) {
        QGridLayout *floor_grid = new QGridLayout();
        floor_grid->setObjectName("floor_grid_" + QString::number(i));

        QLabel *label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::number(i));
        label->setAlignment(Qt::AlignCenter);
        label->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
        floor_grid->addWidget(label, 0, 0, 2, 1);

        floor_buttons[UP_ID][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
        floor_buttons[UP_ID][i - 1]->setObjectName("floor" + QString::number(i) + "_up");
        floor_buttons[UP_ID][i - 1]->setText(QCoreApplication::translate("MainWindow", "\342\207\247", nullptr));
        floor_grid->addWidget(floor_buttons[UP_ID][i - 1].get(), 0, 1, 1, 1);

        floor_buttons[DOWN_ID][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
        floor_buttons[DOWN_ID][i - 1]->setObjectName("floor" + QString::number(i) + "_down");
        floor_buttons[DOWN_ID][i - 1]->setText(QCoreApplication::translate("MainWindow", "\342\207\251", nullptr));
        floor_grid->addWidget(floor_buttons[DOWN_ID][i - 1].get(), 1, 1, 1, 1);

        QFrame *line = new QFrame(gridLayoutWidget);
        line->setObjectName("line_" + QString::number(i));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        floor_grid->addWidget(line, 2, 0, 1, 2);

        QObject::connect(floor_buttons[UP_ID][i - 1].get(), &QPushButton::clicked,
                         [=]() { my_elevator_system.manage_floor_call_slot(i, UP); });

        QObject::connect(floor_buttons[DOWN_ID][i - 1].get(), &QPushButton::clicked,
                         [=]() { my_elevator_system.manage_floor_call_slot(i, DOWN); });

        gridLayout->addLayout(floor_grid, N_FLOORS - i + 1, 0, 1, 1);
    }

    // First floor
    QGridLayout *floor1_grid = new QGridLayout();
    floor1_grid->setObjectName("floor_grid_" + QString::number(1));

    QLabel *label1 = new QLabel(gridLayoutWidget);
    label1->setObjectName(QString::number(1));
    label1->setAlignment(Qt::AlignCenter);
    label1->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(1)), nullptr));
    floor1_grid->addWidget(label1, 0, 0, 1, 1);

    floor_buttons[UP_ID][0] = std::make_shared<QPushButton>(gridLayoutWidget);
    floor_buttons[UP_ID][0]->setObjectName("floor" + QString::number(1) + "_up");
    floor_buttons[UP_ID][0]->setText(QCoreApplication::translate("MainWindow", "\342\207\247", nullptr));
    floor1_grid->addWidget(floor_buttons[UP_ID][0].get(), 0, 1, 1, 1);
    gridLayout->addLayout(floor1_grid, N_FLOORS, 0, 1, 1);

    QObject::connect(floor_buttons[UP_ID][0].get(), &QPushButton::clicked, [=]() { my_elevator_system.manage_floor_call_slot(1, UP); });

    // Last floor
    QGridLayout *floorN_grid = new QGridLayout();
    floorN_grid->setObjectName("floor_grid_" + QString::number(N_FLOORS));

    QLabel *labelN = new QLabel(gridLayoutWidget);
    labelN->setObjectName(QString::number(N_FLOORS));
    labelN->setAlignment(Qt::AlignCenter);
    labelN->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(N_FLOORS)), nullptr));
    floorN_grid->addWidget(labelN, 0, 0, 1, 1);

    floor_buttons[DOWN_ID][N_FLOORS - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
    floor_buttons[DOWN_ID][N_FLOORS - 1]->setObjectName("floor" + QString::number(N_FLOORS) + "_down");
    floor_buttons[DOWN_ID][N_FLOORS - 1]->setText(QCoreApplication::translate("MainWindow", "\342\207\251", nullptr));
    floorN_grid->addWidget(floor_buttons[DOWN_ID][N_FLOORS - 1].get(), 0, 1, 1, 1);

    QObject::connect(floor_buttons[DOWN_ID][N_FLOORS - 1].get(), &QPushButton::clicked,
                     [=]() { my_elevator_system.manage_floor_call_slot(N_FLOORS, DOWN); });

    QFrame *lineN = new QFrame(gridLayoutWidget);
    lineN->setObjectName("line_" + QString::number(N_FLOORS));
    lineN->setFrameShape(QFrame::HLine);
    lineN->setFrameShadow(QFrame::Sunken);
    floorN_grid->addWidget(lineN, 1, 0, 1, 2);
    gridLayout->addLayout(floorN_grid, 1, 0, 1, 1);

    QObject::connect(&my_elevator_system, SIGNAL(floorButtonSystemMediatorSignal(int, direction_id_t, bool)), this,
                     SLOT(change_floor_button_style(int, direction_id_t, bool)));

    QObject::connect(&my_elevator_system, SIGNAL(floorButtonSystemMediatorSignal(int, direction_id_t, bool)), this,
                     SLOT(change_floor_button_style(int, direction_id_t, bool)));

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

    QLabel *elevator1_label = new QLabel(gridLayoutWidget);
    elevator1_label->setObjectName("elevator1_label");
    elevator1_label->setAlignment(Qt::AlignCenter);
    elevator1_label->setText(QCoreApplication::translate("MainWindow", "Лифт 1", nullptr));
    gridLayout->addWidget(elevator1_label, 0, 2, 1, 1);

    QLabel *elevator2_label = new QLabel(gridLayoutWidget);
    elevator2_label->setObjectName("elevator2_label");
    elevator2_label->setAlignment(Qt::AlignCenter);
    elevator2_label->setText(QCoreApplication::translate("MainWindow", "Лифт 2", nullptr));
    gridLayout->addWidget(elevator2_label, 0, 3, 1, 1);

    auto &tmp_elevator_system = my_elevator_system;
    for (int i = N_FLOORS; i > 0; --i) {
        for (int cabin_id = 0; cabin_id < N_CABINS; ++cabin_id) {
            elevator_buttons[cabin_id][i - 1] = std::make_shared<QPushButton>(gridLayoutWidget);
            elevator_buttons[cabin_id][i - 1]->setObjectName("el1_floor" + QString::number(i));
            elevator_buttons[cabin_id][i - 1]->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));

            if (i != N_FLOORS && i != 1)
                elevator_buttons[cabin_id][i - 1]->setMinimumSize(QSize(0, 50));
            gridLayout->addWidget(elevator_buttons[cabin_id][i - 1].get(), N_FLOORS - i + 1, 2 + cabin_id, 1, 1);

            QObject::connect(elevator_buttons[cabin_id][i - 1].get(), &QPushButton::clicked,
                             [=]() { my_elevator_system.manage_cabin_call_slot(i, (cabin_id_t)cabin_id); });

            QObject::connect(&my_elevator_system, SIGNAL(cabinButtonSystemMediatorSignal(int, cabin_id_t, bool)), this,
                             SLOT(change_cabin_button_style(int, cabin_id_t, bool)));
        }
    }

    this->setCentralWidget(centralwidget);

    QMenuBar *menubar = new QMenuBar(this);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, 800, 23));
    this->setMenuBar(menubar);
    QStatusBar *statusbar = new QStatusBar(this);
    statusbar->setObjectName("statusbar");
    this->setStatusBar(statusbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// NOTE(Talkasi): For more convinient testing
void MainWindow::change_floor_button_style(int floor_n, direction_id_t direction_id, bool is_active)
{
    if (is_active) {
        floor_buttons[direction_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
        this->update();
    }
    else {
        floor_buttons[direction_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);
        this->update();
    }
}

// NOTE(Talkasi): For more convinient testing
void MainWindow::change_cabin_button_style(int floor_n, cabin_id_t cabin_id, bool is_active)
{
    if (is_active) {
        elevator_buttons[cabin_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_ACTIVE);
        this->update();
    }
    else {
        elevator_buttons[cabin_id][floor_n - 1]->setStyleSheet(QString("background-color:") + COLOR_BUTTON_INACTIVE);
        this->update();
    }
}
