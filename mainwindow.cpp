#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ogrenci.h"
#include "ders.h"
#include "score.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_ogr->setStyleSheet("border-image:url(:/img/images/ogr.jpg);");
    ui->btn_ders->setStyleSheet("border-image:url(:/img/images/ders.jpg);");
    ui->btn_not->setStyleSheet("border-image:url(:/img/images/notlar.jpg);");


    db.setDatabaseName("C:/Qt/A_lessons/20010011520_odev2/otomasyon.db");
    if(!db.open())
        ui->statusbar->showMessage("Veri tabanina baglanilamadi");
    else
        ui->statusbar->showMessage("Veri tabanina baglanildi");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_ogr_clicked()
{
    ogrenci *ogr = new ogrenci(db,this);
    ogr->show();
}


void MainWindow::on_btn_ders_clicked()
{
    ders *drs = new ders(db,this);
    drs->show();
}


void MainWindow::on_btn_not_clicked()
{
    score *scr = new score(db,this);
    scr->show();
}

