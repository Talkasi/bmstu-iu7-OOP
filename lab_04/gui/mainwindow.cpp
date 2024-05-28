#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(500, 500);
    this->layout_ = std::make_unique<QVBoxLayout>();
    this->ui->centralwidget->setLayout(this->layout_.get());
    this->layout_->addWidget(this->my_elevator.widget());
}

MainWindow::~MainWindow()
{
    delete ui;
}
