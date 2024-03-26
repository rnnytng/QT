#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QLabel>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/1.jpg"));
    setWindowTitle("sql");
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setPassword("1125");
    db.setUserName("root");
    db.setDatabaseName("4");
    db.open();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_people_clicked()
{


    QSqlQuery query;
    query.exec("select * from person");
    QString d;
    while(query.next())
    {

        QString a=query.value("name").toString();
        QString b=query.value("age").toString();
        QString c=query.value("country").toString();
        d=d+a+"   "+b+"   "+c+"\n";

    }
    QMessageBox::information(this,"people",d);
}

void MainWindow::on_add_clicked()
{
    QString name = QInputDialog::getText(this, "Enter name", "Name:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags());
    int age = QInputDialog::getInt(this, "Enter age", "Age:", 0, 0, 100, 1);
    QString country = QInputDialog::getText(this, "Enter country", "Country:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags());

        // 准备SQL语句
        QString insertQuery = "INSERT INTO person (name, age, country) VALUES (:name, :age, :country)";

        // 执行SQL语句
        QSqlQuery query;
        query.prepare(insertQuery);
        query.bindValue(":name", name);
        query.bindValue(":age", age);
        query.bindValue(":country", country);
        query.exec();
        ui->label->setText("add successful");

}

void MainWindow::on_delete_2_clicked()
{
    QString deleteQuery = "DELETE FROM person WHERE Name = :name";

       // 绑定要删除的人物的名字
       QString name = QInputDialog::getText(this, "Enter name", "Name:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags());

       // 执行SQL语句
       QSqlQuery query;
       query.prepare(deleteQuery);
       query.bindValue(":name", name);
       query.exec();
       ui->label->setText("delete successful");

}
