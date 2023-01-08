#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

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

    void on_btn_ogr_clicked();

    void on_btn_ders_clicked();

    void on_btn_not_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");

};
#endif // MAINWINDOW_H
