#include "serverwidget.h"
#include "ui_serverwidget.h"

serverWidget::serverWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serverWidget)
{
    ui->setupUi(this);

    setWindowTitle("ServerWidget");
}

serverWidget::~serverWidget()
{
    delete ui;
}

void serverWidget::slotUpdateServer(QString msg)
{
    qDebug() << Q_FUNC_INFO;
    ui->textEdit_readText->append(msg);
}

void serverWidget::on_pushButton_createRoom_clicked()
{
    quint16 u16Port = ui->lineEdit_port->text().toUInt();
    qDebug() << "u16Port: " << u16Port;
    server = new Server(this, u16Port);
    connect(server, &Server::updateServer, this, &serverWidget::slotUpdateServer);
    ui->pushButton_createRoom->setEnabled(false);
}


void serverWidget::on_pushButton_addUser_clicked()
{
    ClientWidget *c = new ClientWidget();
    c->show();
}

