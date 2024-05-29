#include "mainwindow.h"
#include "src/button/elevator_button/elevator_button.hpp"
#include "src/button/floor_button/floor_button.hpp"
#include "src/config.hpp"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(800, 600);

    std::array<std::shared_ptr<ElevatorButton>, FLOORS> elevator1_buttons;
    std::array<std::shared_ptr<ElevatorButton>, FLOORS> elevator2_buttons;
    std::array<std::array<std::shared_ptr<FloorButton>, N_DIRECTIONS>, FLOORS> floor_buttons;

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

    for (int i = FLOORS; i > 1; --i) {
        QGridLayout *floor_grid = new QGridLayout();
        floor_grid->setObjectName("floor_grid_" + QString::number(i));

        QLabel *label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::number(i));
        label->setAlignment(Qt::AlignCenter);
        label->setText(QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
        floor_grid->addWidget(label, 0, 0, 2, 1);

        floor_buttons[i - 1][UP] = std::make_shared<FloorButton>(gridLayoutWidget, i, UP);
        floor_buttons[i - 1][UP]->setObjectName("button_up_" + QString::number(i));
        floor_buttons[i - 1][UP]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\205", nullptr));
        floor_grid->addWidget(floor_buttons[i - 1][UP].get(), 0, 1, 1, 1);

        floor_buttons[i - 1][DOWN] = std::make_shared<FloorButton>(gridLayoutWidget, i, DOWN);
        floor_buttons[i - 1][DOWN]->setObjectName("button_down_" + QString::number(i));
        floor_buttons[i - 1][DOWN]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\207", nullptr));
        floor_grid->addWidget(floor_buttons[i - 1][DOWN].get(), 1, 1, 1, 1);

        gridLayout->addLayout(floor_grid, FLOORS - i + 1, 0, 1, 2);
    }

    QGridLayout *first_floor_grid = new QGridLayout();
    first_floor_grid->setObjectName("floor_grid_0");

    QLabel *label = new QLabel(gridLayoutWidget);
    label->setObjectName("1");
    label->setAlignment(Qt::AlignCenter);
    label->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    first_floor_grid->addWidget(label, 0, 0, 1, 1);

    floor_buttons[0][UP] = std::make_shared<FloorButton>(gridLayoutWidget, 0, UP);
    floor_buttons[0][UP]->setObjectName("button_up_0");
    floor_buttons[0][UP]->setText(QCoreApplication::translate("MainWindow", "\360\237\241\205", nullptr));
    first_floor_grid->addWidget(floor_buttons[0][UP].get(), 0, 1, 1, 1);
    gridLayout->addLayout(first_floor_grid, FLOORS, 0, 1, 2);

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

    for (int i = FLOORS; i > 0; --i) {
        elevator1_buttons[i - 1] = std::make_shared<ElevatorButton>(gridLayoutWidget, i);
        elevator1_buttons[i - 1]->setObjectName("button_elevator1_" + QString::number(i));
        elevator1_buttons[i - 1]->setText(
            QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
        elevator1_buttons[i - 1]->setMinimumSize(QSize(0, 50));
        gridLayout->addWidget(elevator1_buttons[i - 1].get(), FLOORS - i + 1, 3, 1, 1);

        elevator2_buttons[i - 1] = std::make_shared<ElevatorButton>(gridLayoutWidget, i);
        elevator2_buttons[i - 1]->setObjectName("button_elevator2_" + QString::number(i));
        elevator2_buttons[i - 1]->setMinimumSize(QSize(0, 50));
        elevator2_buttons[i - 1]->setText(
            QCoreApplication::translate("MainWindow", qPrintable(QString::number(i)), nullptr));
        gridLayout->addWidget(elevator2_buttons[i - 1].get(), FLOORS - i + 1, 4, 1, 1);
    }

    this->setCentralWidget(centralwidget);
    my_elevator_manager = std::make_shared<Manager>(floor_buttons, elevator1_buttons, elevator2_buttons);
}

MainWindow::~MainWindow()
{
    delete ui;
}
