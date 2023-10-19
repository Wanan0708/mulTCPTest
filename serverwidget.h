#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include "server.h"
#include "clientwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class serverWidget; }
QT_END_NAMESPACE

class serverWidget : public QWidget
{
    Q_OBJECT

public:
    serverWidget(QWidget *parent = nullptr);
    ~serverWidget();

private:
    Ui::serverWidget *ui;
    Server *server;

private slots:
    void slotUpdateServer(QString msg);
    void on_pushButton_createRoom_clicked();

    void on_pushButton_addUser_clicked();
};
#endif // SERVERWIDGET_H
