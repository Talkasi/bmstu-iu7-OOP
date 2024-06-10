#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "elevator_system/elevator_system.hpp"
#include <QMainWindow>

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

signals:
    // NOTE(Talkasi): For more convinient testing
    void clientCallFromCabinSignal(int floor_n, cabin_id_t cabin_id);
    void clientCallFromFloorSignal(int floor_n, direction_t direction);

private slots:
    // NOTE(Talkasi): For more convinient testing
    void change_cabin_button_style(int floor_n, cabin_id_t cabin_id, bool is_active);
    void change_floor_button_style(int floor_n, direction_id_t direction, bool is_active);

private:
    Ui::MainWindow *ui;
    ElevatorSystem my_elevator_system;

    std::shared_ptr<QPushButton> elevator_buttons[N_CABINS][N_FLOORS];
    std::shared_ptr<QPushButton> floor_buttons[N_DIRECTIONS][N_FLOORS];
};

#endif // MAINWINDOW_H
