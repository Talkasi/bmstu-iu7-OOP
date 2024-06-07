#ifndef LAB_04_DOORS_HPP
#define LAB_04_DOORS_HPP
#include "config.hpp"
#include <QObject>
#include <QTimer>

class Doors : public QObject
{
    Q_OBJECT

public:
    Doors(cabin_id_t cabin_id);

signals:
    void doorClosed();

private slots:
    void startClosing();
    void startOpening();

public slots:
    void open();
    void close();

private:
    enum doors_state_t
    {
        OPEN,
        CLOSED,
        OPENING,
        CLOSING
    };

    doors_state_t _state;
    cabin_id_t _cabin_id;
    QTimer _openTimer;
    QTimer _closeTimer;
    QTimer _waitTimer;
};

#endif // LAB_04_DOORS_HPP
