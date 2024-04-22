#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "errors.h"
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
    err_t draw();
    void on_LoadFile_clicked();
    void on_SaveFile_clicked();
    void on_GetFileInfo_clicked();
    void on_GetProgramInfo_clicked();

private slots:

    void on_buttonMove_clicked();
    void on_buttonTurn_clicked();
    void on_buttonScale_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
