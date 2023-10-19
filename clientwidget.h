#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QHostAddress>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_pushButton_createRoom_clicked();
    void on_pushButton_send_clicked();
    void slotConnectSuccess();
    void slotReceived();
    void slotDisConnected();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;
    bool status;
    int port;
    QString userName;
    QHostAddress *serverIP;
};

#endif // CLIENTWIDGET_H
