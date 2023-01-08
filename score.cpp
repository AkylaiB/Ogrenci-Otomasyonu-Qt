#include "score.h"
#include "ui_score.h"

score::score(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);

    sorgu->prepare("select * from ogrenci");
    if(!sorgu->exec())
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    model = new QSqlQueryModel;
    model->setQuery(*sorgu);
    ui->tv_ogr->setModel(model);

    sorgu->prepare("select * from dersler");
    if(!sorgu->exec())
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    model2 = new QSqlQueryModel;
    model2->setQuery(*sorgu);
    ui->tv_ders->setModel(model2);

    model3 = new QSqlQueryModel;
    listele();
}

score::~score()
{
    delete ui;
}

void score::listele()
{
    sorgu->prepare("select * from notlar");
    if(!sorgu->exec())
    {
         QMessageBox::critical(this,"Hata",sorgu->lastError().text());
    }
    model3->setQuery(*sorgu);
    ui->tv_OgrDrs->setModel(model3);

}

void score::on_tv_ogr_clicked(const QModelIndex &index)
{
    ui->ln_no->setText(model->index(index.row(),0).data().toString());
}


void score::on_tv_ders_clicked(const QModelIndex &index)
{
    ui->ln_kod->setText(model2->index(index.row(),0).data().toString());
}


void score::on_btn_KayitEkle_clicked()
{
    if(ui->ln_no->text().isEmpty() || ui->ln_kod->text().isEmpty() || ui->ln_vize->text().isEmpty() || ui->ln_final->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!");
    }
    else
    {
        QList<int> liste, liste2;
        int ctrl_var=0;
        if(!sorgu->exec("select * from notlar"))
        {
             QMessageBox::critical(this,"Hata",sorgu->lastError().text());
        }
        model4 = new QSqlQueryModel;
        model4->setQuery(*sorgu);
        for(int i=0; i<model4->rowCount(); i++)
        {
            liste.append(model4->index(i,0).data().toInt());
        }
        for(int j=0; j<liste.size(); j++)
        {
            if(liste[j]==ui->ln_no->text().toInt())
            {
                if(model4->index(j,1).data().toInt()==ui->ln_kod->text().toInt())
                    ctrl_var=1;
            }
        }
        if(ctrl_var==0)
        {
            float gnot = ui->ln_vize->text().toInt()*0.4+ui->ln_final->text().toInt()*0.6;
            float gec_notu = round(gnot*100)/100;
            sorgu->prepare("insert into notlar (ogr_no,ders_kodu,vize_not,final_not,gecme_notu) values (:no,:kod,:vize,:final,:gn)");
            sorgu->bindValue(":no",ui->ln_no->text());
            sorgu->bindValue(":kod",ui->ln_kod->text());
            sorgu->bindValue(":vize",ui->ln_vize->text());
            sorgu->bindValue(":final",ui->ln_final->text());
            sorgu->bindValue(":gn",gec_notu);
            if(!sorgu->exec())
            {
                 QMessageBox::critical(this,"Hata",sorgu->lastError().text());
            }
            else
            {
                QMessageBox::information(this,"Ekleme Durumu","Başarılı");
                listele();
            }
        }
        else
            QMessageBox::information(this,"Hata!","Bu öğrenci üzerinde bu ders zaten tanımlı!");
    }
}

