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
    void client_call_from_cabin(int floor_n, cabin_id_t cabin_id);
    void client_call_from_floor(int floor_n, direction_t direction);

private slots:
    void on_el1_floor10_clicked();
    void on_el1_floor9_clicked();
    void on_el1_floor8_clicked();
    void on_el1_floor7_clicked();
    void on_el1_floor6_clicked();
    void on_el1_floor5_clicked();
    void on_el1_floor4_clicked();
    void on_el1_floor3_clicked();
    void on_el1_floor2_clicked();
    void on_el1_floor1_clicked();

    void on_el2_floor10_clicked();
    void on_el2_floor9_clicked();
    void on_el2_floor8_clicked();
    void on_el2_floor7_clicked();
    void on_el2_floor6_clicked();
    void on_el2_floor5_clicked();
    void on_el2_floor4_clicked();
    void on_el2_floor3_clicked();
    void on_el2_floor2_clicked();
    void on_el2_floor1_clicked();

    void on_floor10_down_clicked();
    void on_floor9_down_clicked();
    void on_floor8_down_clicked();
    void on_floor7_down_clicked();
    void on_floor6_down_clicked();
    void on_floor5_down_clicked();
    void on_floor4_down_clicked();
    void on_floor3_down_clicked();
    void on_floor2_down_clicked();

    void on_floor9_up_clicked();
    void on_floor8_up_clicked();
    void on_floor7_up_clicked();
    void on_floor6_up_clicked();
    void on_floor5_up_clicked();
    void on_floor4_up_clicked();
    void on_floor3_up_clicked();
    void on_floor2_up_clicked();
    void on_floor1_up_clicked();

    // void on_el1_floor10_toggled(bool checked);
    // void on_el1_floor9_toggled(bool checked);
    // void on_el1_floor8_toggled(bool checked);
    // void on_el1_floor7_toggled(bool checked);
    // void on_el1_floor6_toggled(bool checked);
    // void on_el1_floor5_toggled(bool checked);
    // void on_el1_floor4_toggled(bool checked);
    // void on_el1_floor3_toggled(bool checked);
    // void on_el1_floor2_toggled(bool checked);
    // void on_el1_floor1_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    ElevatorSystem my_elevator_system;
};

#endif // MAINWINDOW_H
