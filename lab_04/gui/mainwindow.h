#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "src/elevator/elevator.hpp"
#include <QMainWindow>
#include <QVBoxLayout>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QVBoxLayout> layout_;
    Elevator my_elevator;
};

#endif // MAINWINDOW_H
