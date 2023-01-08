#include "ogrenci.h"
#include "ui_ogrenci.h"
#include <QString>

ogrenci::ogrenci(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    model = new QSqlQueryModel;
    listele();

}

ogrenci::~ogrenci()
{
    delete ui;
}

void ogrenci::listele()
{
    if(!sorgu->exec("select * from ogrenci"))
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    else
    {
        model->setQuery(*sorgu);
        ui->tv_ogr->setModel(model);
    }

}

void ogrenci::on_tv_ogr_clicked(const QModelIndex &index)
{
    ui->lnedNo->setText(model->index(index.row(),0).data().toString());
    ui->lnedAd->setText(model->index(index.row(),1).data().toString());
    ui->lnedSoyad->setText(model->index(index.row(),2).data().toString());
}


void ogrenci::on_btnYeniKayit_clicked()
{
    if(ui->lnedAd->text().isEmpty() || ui->lnedSoyad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!");

    }
    else
    {
        sorgu->prepare("insert into ogrenci (ogr_ad, ogr_soyad) values (:ad,:soyad)");
        sorgu->bindValue(":ad",ui->lnedAd->text());
        sorgu->bindValue(":soyad",ui->lnedSoyad->text());
        if(!sorgu->exec())
        {
             QMessageBox::critical(this,"Hata",sorgu->lastError().text());
        }
        else
        {
            QMessageBox::information(this,"Ekleme Durumu","Başarılı");
        }
    }
    listele();
}


void ogrenci::on_btnSil_clicked()
{
    int ctrl_drs_var=0;

    if(!ui->lnedNo->text().isEmpty())
    {
        sorgu->prepare("select * from notlar where ogr_no = (:no)");
        sorgu->bindValue(":no",ui->lnedNo->text());
        if(!sorgu->exec())
        {
             QMessageBox::critical(this,"Hata",sorgu->lastError().text());
             return;
        }
        while(sorgu->next())
            ctrl_drs_var++;

        if(ctrl_drs_var==0)
        {
            sorgu->prepare("delete from ogrenci where ogr_no = (:no)");
            sorgu->bindValue(":no",ui->lnedNo->text());
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata","Kayıt silinemedi!");
            }
            else
            {
                QMessageBox::information(this,"Silme Durumu","Başarılı");
                listele();
                //line editlerdeki silinenin bilgilerini kaldırıyoruz
                ui->lnedNo->clear();
                ui->lnedAd->clear();
                ui->lnedSoyad->clear();

            }

        }
        else
            QMessageBox::information(this,"Hata","Bu öğrenci silinemez. Bu öğrencinin üstüne tanımlanmış dersler vardır!");
    }
    else
        QMessageBox::critical(this,"Hata","Lütfen silinecek kaydı seçiniz!");

}


void ogrenci::on_btnGuncelle_clicked()
{
    int ctrl=0;
    if(!ui->lnedNo->text().isEmpty())
    {
        sorgu->prepare("select * from notlar where ogr_no=:no");
        sorgu->bindValue(":no",ui->lnedNo->text());
        if(!sorgu->exec())
        {
             QMessageBox::critical(this,"Hata",sorgu->lastError().text());
             return;
        }
        while(sorgu->next())
            ctrl++;
        if(ctrl==0)
        {
            sorgu->prepare("update ogrenci set  ogr_ad=:ad,ogr_soyad=:soyad where ogr_no=:no");
            sorgu->bindValue(":no",ui->lnedNo->text());
            sorgu->bindValue(":ad",ui->lnedAd->text());
            sorgu->bindValue(":soyad",ui->lnedSoyad->text());
            if(!sorgu->exec())
            {
                 QMessageBox::critical(this,"Hata",sorgu->lastError().text());
            }
            else
            {
                QMessageBox::information(this,"Güncelleme Durumu","Başarılı");
                listele();
            }
        }
        else
            QMessageBox::critical(this,"Hata","Bu öğrencinin bilgileri artık güncellenemez!");

    }
    else
    {
        QMessageBox::critical(this,"Hata","Lutfen güncellenecek kaydı seçiniz!");
    }
}

