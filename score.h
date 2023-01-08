#ifndef SCORE_H
#define SCORE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class score;
}

class score : public QDialog
{
    Q_OBJECT

public:
    explicit score(QSqlDatabase,QWidget *parent = nullptr);
    ~score();
    void listele();

private slots:
    void on_tv_ogr_clicked(const QModelIndex &index);

    void on_tv_ders_clicked(const QModelIndex &index);

    void on_btn_KayitEkle_clicked();

private:
    Ui::score *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model, *model2, *model3, *model4;
};

#endif // SCORE_H
