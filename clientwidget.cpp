#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle("ClientWidget");
    status = false;
    port = 8888;
    ui->lineEdit_port->setText(QString::number(port));

    serverIP = new QHostAddress();

    ui->pushButton_send->setEnabled(false);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_createRoom_clicked()
{
    if (status == false)
    {
        QString strIP = ui->lineEdit_address->text();
        if (!serverIP->setAddress(strIP))
        {
            ui->textEdit_readText->append("ip地址不正确");
            return;
        }

        if (ui->lineEdit_userName->text().isEmpty())
        {
            ui->textEdit_readText->append("请输入用户名");
            return;
        }

        userName = ui->lineEdit_userName->text();
        quint16 u16Port = ui->lineEdit_port->text().toUInt();
        tcpSocket = new QTcpSocket();
        tcpSocket->connectToHost(strIP, u16Port);
        qDebug() << userName << u16Port << strIP;

        connect(tcpSocket, &QTcpSocket::connected, this, &ClientWidget::slotConnectSuccess);
        connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientWidget::slotReceived);

        status = true;
    }
    else
    {
        qDebug() << "status = true";
        QString strMsg = userName + "leave chat room;";
        tcpSocket->write(strMsg.toUtf8().data());
        tcpSocket->disconnectFromHost();
        status = false;

        connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientWidget::slotDisConnected);
    }
}


void ClientWidget::on_pushButton_send_clicked()
{
    if (ui->textEdit_writeText->toPlainText().isEmpty())
    {
        return;
    }

    QString strMsg = userName + ":" + ui->textEdit_writeText->toPlainText();
    tcpSocket->write(strMsg.toUtf8().data());
    if (tcpSocket->waitForBytesWritten(3000))
    {
        ui->textEdit_writeText->clear();
    }
    else
    {
        ui->textEdit_readText->append("send fail!");
    }
}

void ClientWidget::slotConnectSuccess()
{
    ui->pushButton_send->setEnabled(true);
    ui->pushButton_createRoom->setText("离开聊天室");

    QString strMsg = userName + " :Enter chat room;";
    tcpSocket->write(strMsg.toUtf8().data());
    qDebug() << tcpSocket->waitForBytesWritten(2000);
}

void ClientWidget::slotReceived()
{
    QByteArray array = tcpSocket->readAll();
    ui->textEdit_readText->append(array);
}

void ClientWidget::slotDisConnected()
{
    ui->pushButton_send->setEnabled(false);
    ui->pushButton_createRoom->setText("进入聊天室");
}

