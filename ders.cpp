#include "ders.h"
#include "ui_ders.h"

ders::ders(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ders)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    model = new QSqlQueryModel;
    listele();
}

ders::~ders()
{
    delete ui;
}

void ders::listele()
{
    if(!sorgu->exec("select * from dersler"))
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    model->setQuery(*sorgu);
    ui->tv_dersler->setModel(model);

}
void ders::on_tv_dersler_clicked(const QModelIndex &index)
{
    ui->lnedKod->setText(model->index(index.row(),0).data().toString());
    ui->lnedAd->setText(model->index(index.row(),1).data().toString());

    if(!sorgu->exec("select * from notlar where ders_kodu="+ui->lnedKod->text()))
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    model2 = new QSqlQueryModel;
    model2->setQuery(*sorgu);
    ui->tv_ogrler->setModel(model2);
}


void ders::on_btnYeniKayit_clicked()
{
    if(ui->lnedKod->text().isEmpty() || ui->lnedAd->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!");

    }
    else
    {
        int ctrl_kod_bos=0;
        sorgu->prepare("select * from dersler where ders_kodu=:kod");
        sorgu->bindValue(":kod",ui->lnedKod->text());
        if(!sorgu->exec())
        {
             QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
             return;
        }
        while(sorgu->next())
            ctrl_kod_bos++;

        if(ctrl_kod_bos==0)
        {
            sorgu->prepare("insert into dersler values (:kod,:ad)");
            sorgu->bindValue(":ad",ui->lnedAd->text());
            sorgu->bindValue(":kod",ui->lnedKod->text());
            if(!sorgu->exec())
            {
                 QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
            }
            else
            {
                QMessageBox::information(this,"Ekleme Durumu","Başarılı");
                listele();
            }
        }
        else
            QMessageBox::information(this,"Hata!","Bu kodda başka bir ders vardır. Farklı kodda ders ekleyiniz!");

    }
}


void ders::on_btnSil_clicked()
{
    if(!ui->lnedAd->text().isEmpty())
    {
        int ctrl_ogr_var=0;
        sorgu->prepare("select * from notlar where ders_kodu=:kod");
        sorgu->bindValue(":kod",ui->lnedKod->text());
        if(!sorgu->exec())
        {
             QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
             return;
        }
        while(sorgu->next())
            ctrl_ogr_var++;
        if(ctrl_ogr_var==0)
        {
            sorgu->prepare("delete from dersler where ders_adi = (:ad)");
            sorgu->bindValue(":ad",ui->lnedAd->text());
            if(sorgu->exec())
            {
                QMessageBox::information(this,"Silme Durumu","Başarılı");
                ui->lnedAd->clear();
                ui->lnedKod->clear();
                listele();
            }
            else
                QMessageBox::critical(this,"Hata","Ders silinemedi!");
        }
        else
            QMessageBox::information(this,"Hata!","Bu ders silinemez. Bu derse kayıtlı öğrenciler vardır!");

    }
    else
        QMessageBox::critical(this,"Hata","Lütfen silinecek dersi seçiniz!");
}


void ders::on_btnGuncelle_clicked()
{
    if(!ui->lnedKod->text().isEmpty())
    {
        int ctrl=0;
         sorgu->prepare("select * from notlar where ders_kodu=:kod");
         sorgu->bindValue(":kod",ui->lnedKod->text());
         if(!sorgu->exec())
         {
             QMessageBox::critical(this,"Hata",sorgu->lastError().text());
         }
         while(sorgu->next())
             ctrl++;
         if(ctrl==0)
         {
             sorgu->prepare("update dersler set  ders_adi=:ad where ders_kodu=:kod");
             sorgu->bindValue(":kod",ui->lnedKod->text());
             sorgu->bindValue(":ad",ui->lnedAd->text());
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
             QMessageBox::critical(this,"Hata","Bu ders artık güncellenemez!");
    }
    else
    {
        QMessageBox::critical(this,"Hata","Lutfen güncellenecek dersi seçiniz!");
    }
}

