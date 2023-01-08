#ifndef DERS_H
#define DERS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class ders;
}

class ders : public QDialog
{
    Q_OBJECT

public:
    explicit ders(QSqlDatabase,QWidget *parent = nullptr);
    ~ders();
    void listele();

private slots:
    void on_tv_dersler_clicked(const QModelIndex &index);

    void on_btnYeniKayit_clicked();

    void on_btnSil_clicked();

    void on_btnGuncelle_clicked();

private:
    Ui::ders *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model,*model2;
};

#endif // DERS_H
