#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "src/manager/manager.hpp"
#include <QMainWindow>
#include <QVBoxLayout>

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
    std::shared_ptr<Manager> my_elevator_manager;
};

#endif // MAINWINDOW_H
