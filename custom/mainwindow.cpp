#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statue=new QLabel;
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(statue);
    setWindowTitle("客户端");
    setFixedSize(400,500);
    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");
    tcp=new QTcpSocket;
    connect(tcp,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray data=tcp->readAll();
        ui->history->append("服务器:"+data);
    });

    connect(tcp,&QTcpSocket::disconnected,this,[=]()
    {
        ui->history->append("服务器已经断开了连接, ...");
        tcp->close();
        tcp->deleteLater();
        statue->setPixmap(QPixmap(":/img/2.jpg").scaled(20,20));

    });
    connect(tcp,&QTcpSocket::connected,this,[=]()

    {
        ui->history->append("恭喜, 连接服务器成功!!!");
        statue->setPixmap(QPixmap(":/img/1.jpg").scaled(20,20));

    });

    connect(ui->on,&QPushButton::clicked,this,[=]()
    {
        QString ip=ui->ip->text();
        unsigned short port=ui->port->text().toUShort();
        tcp->connectToHost(QHostAddress(ip),port);
        ui->on->setDisabled(true);
        ui->off->setDisabled(false);

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_send_clicked()
{
    QString mes=ui->mes->toPlainText();
    tcp->write(mes.toUtf8());
    ui->history->append("客户端:"+mes);
}

void MainWindow::on_off_clicked()
{
    tcp->close();
    ui->on->setDisabled(false);
    ui->off->setDisabled(true);

}
