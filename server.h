#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpclientsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    Server(QObject *parent = 0, int port = 0);
    QList<TcpClientSocket *> tcpClientSocketList;

protected:
    virtual void incomingConnection(qintptr socketDescription);

private slots:
    void slotUpdateServer(QString msg, int length);
    void slotClientDisconnect(int descriptor);

signals:
    void updateServer(QString msg, int length);

private:
    int port;

};

#endif // SERVER_H
