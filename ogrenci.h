#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class ogrenci;
}

class ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci(QSqlDatabase,QWidget *parent = nullptr);
    ~ogrenci();
    void listele();

private slots:
    void on_tv_ogr_clicked(const QModelIndex &index);

    void on_btnYeniKayit_clicked();

    void on_btnSil_clicked();

    void on_btnGuncelle_clicked();

private:
    Ui::ogrenci *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
};

#endif // OGRENCI_H
