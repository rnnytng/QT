#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statue=new QLabel;
    setWindowTitle("服务器");
    setFixedSize(400,500);
    ui->port->setText("8899");
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(statue);
    server=new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,[=]()
    {
        tcp=server->nextPendingConnection();
        ui->history->append("成功连接客户端");
        statue->setPixmap(QPixmap(":/img/1.jpg").scaled(20,20));
        connect(tcp,&QTcpSocket::readyRead,this,[=]()
        {
            QString data=tcp->readAll();
            ui->history->append("客户端:"+data);
        });
        connect(tcp,&QTcpSocket::disconnected,this,[=]()
        {
            ui->history->append("客户端连接已断开");
            tcp->close();
            tcp->deleteLater();
            statue->setPixmap(QPixmap(":/img/2.jpg").scaled(20,20));
        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_begin_clicked()
{
    unsigned short port=ui->port->text().toUShort();
    server->listen(QHostAddress::Any,port);
    ui->begin->setDisabled(true);
}

void MainWindow::on_send_clicked()
{
    QString mes=ui->message->toPlainText();
    tcp->write(mes.toUtf8());
    ui->history->append("服务器:"+mes);

}
