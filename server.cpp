#include "server.h"

Server::Server()
{

}

Server::Server(QObject *parent, int port)
{
    Q_UNUSED(parent);

    listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr socketDescription)
{
    qDebug() << Q_FUNC_INFO;
    TcpClientSocket *tcpClientSocket = new TcpClientSocket();
    tcpClientSocket->setSocketDescriptor(socketDescription);
    tcpClientSocketList.append(tcpClientSocket);

    connect(tcpClientSocket, &TcpClientSocket::updateServer, this, &Server::slotUpdateServer);
    connect(tcpClientSocket, &TcpClientSocket::clientDisconnect, this, &Server::slotClientDisconnect);
}

void Server::slotUpdateServer(QString msg, int length)
{
    qDebug() << Q_FUNC_INFO << msg << length;
    emit updateServer(msg, length);

    for (int i = 0; i < tcpClientSocketList.count(); i++)
    {
        TcpClientSocket *tmpSocket = tcpClientSocketList.at(i);
        tmpSocket->write(msg.toUtf8().data());
    }
}

void Server::slotClientDisconnect(int descriptor)
{
    for (int i = 0; i < tcpClientSocketList.count(); i++)
    {
        TcpClientSocket *tmpSocket = tcpClientSocketList.at(i);
        if (tmpSocket->socketDescriptor() == descriptor)
        {
            tcpClientSocketList.removeAt(i);
            tmpSocket->disconnectFromHost();
            tmpSocket->close();
            delete tmpSocket;
            tmpSocket = nullptr;
        }
    }
}
