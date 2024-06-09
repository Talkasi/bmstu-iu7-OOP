#ifndef DOOR_H
#define DOOR_H
#include "config.hpp"
#include <QObject>
#include <QTimer>

class Doors : public QObject
{
    Q_OBJECT

public:
    explicit Doors(cabin_id_t cabin_id, QObject *parent = nullptr);

signals:
    void doorIsClosed();

public slots:
    void startOpening();
    void startClosing();

private slots:
    void open();
    void close();

private:
    enum door_state_t
    {
        OPENED,
        OPENING,
        CLOSED,
        CLOSING
    };

    cabin_id_t _cabin_id;
    QTimer openDoorTimer;
    QTimer closeDoorTimer;
    QTimer openStateDoorTimer;
    door_state_t currentState;
};

#endif // DOOR_H
