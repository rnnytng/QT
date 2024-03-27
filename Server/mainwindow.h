#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTcpServer>
#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_begin_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer*server;
    QTcpSocket*tcp;
    QLabel*statue;
};
#endif // MAINWINDOW_H
