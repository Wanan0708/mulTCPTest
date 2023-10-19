#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    Q_UNUSED(parent);
    connect(this, &TcpClientSocket::readyRead, this, &TcpClientSocket::receiveData);
    connect(this, &TcpClientSocket::disconnected, this, &TcpClientSocket::slotClientDisconnect);
}

void TcpClientSocket::receiveData()
{
    QByteArray arrayData = readAll();
    QString strData = arrayData;
    emit updateServer(strData, 10);
}

void TcpClientSocket::slotClientDisconnect()
{
    emit clientDisconnect(this->socketDescriptor());
}
