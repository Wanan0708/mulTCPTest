#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);

private slots:
    void receiveData();
    void slotClientDisconnect();

signals:
    void updateServer(QString, int);
    void clientDisconnect(int );
};

#endif // TCPCLIENTSOCKET_H
