#include "okno_barman.h"
#include "ui_okno_barman.h"

okno_barman::okno_barman(QWidget *parent) :
    QWidget(parent),
    baza(qobject_cast<MainWindow*>(parent)->db),
    ui(new Ui::okno_barman)
{
    ui->setupUi(this);
    query = new QSqlQueryModel;
    query2.exec("SELECT * FROM produkt ORDER BY nazwa");
    while(query2.next())
        ui->comboBoxProdukt->addItem(query2.value(2).toString());
    ui->comboBoxProdukt->setCurrentIndex(-1);
    ui->tabWidget->removeTab(1);

}

okno_barman::~okno_barman()
{
    delete ui;
}

void okno_barman::on_pushButtonUtworz_clicked()
{
    QString sprzedaz;
    query->setQuery("INSERT INTO sprzedaz (data_sprzedazy) VALUES "
                    "('"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"')");
    sprzedaz="INSERT INTO sprzedaz (data_sprzedazy) VALUES"
             "('"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm")+"')";
    query2.exec("SELECT * FROM sprzedaz");
    while(query2.next())
        sprzedaz=query2.value(0).toString();
    ui->lineEdit->setText(sprzedaz);
    query->setQuery("SELECT nazwa, ilosc, SUM(cena), as cena FROM element_sprzedazy "
                    "WHERE id_sprzedazy="+sprzedaz+" ORDER BY id_elementu DESC");
    ui->tableView->setModel(query);
}

void okno_barman::on_pushButtonDodajProdukt_clicked()
{
    QString produkt, ilosc, temp;
    int cena=0;
    produkt=ui->comboBoxProdukt->currentText();
    ilosc=ui->spinBoxIlosc->text();
    temp=QString::number(ui->comboBoxProdukt->currentIndex()+1);
    if(produkt.size()==0)
        QMessageBox::information(this,"Dodawanie produktów","Wybierz produkt");
    else if(ui->lineEdit->text().size()==0)
        QMessageBox::information(this,"Dodawanie produktów","Utwórz sprzedaż");
    else
    {
        query->setQuery("SELECT * FROM element_sprzedazy "
                    "WHERE id_produktu="+temp+" AND id_sprzedazy="+ui->lineEdit->text());
        if(query->rowCount()==0)
        {
            query->setQuery("INSERT INTO element_sprzedazy (id_sprzedazy,id_produktu,ilosc) VALUES "
                            "("+ui->lineEdit->text()+", "
                            +temp+", "
                            +ilosc+")");
        }
        else
            query->setQuery("UPDATE element_sprzedazy SET ilosc=ilosc+"+ilosc+" "
                            "WHERE id_sprzedazy="+ui->lineEdit->text()+" AND id_produktu="+temp);
    }
    query->setQuery("SELECT nazwa, ilosc, cena*ilosc AS cena FROM element_sprzedazy "
                    "JOIN produkt ON element_sprzedazy.id_produktu=produkt.id_produktu "
                    "WHERE id_sprzedazy="+ui->lineEdit->text()+" GROUP BY id_elementu ORDER BY id_elementu DESC ");
    query2.exec("SELECT nazwa, ilosc, cena*ilosc AS cena FROM element_sprzedazy "
                "JOIN produkt ON element_sprzedazy.id_produktu=produkt.id_produktu "
                "WHERE id_sprzedazy="+ui->lineEdit->text()+" GROUP BY id_elementu ORDER BY id_elementu DESC ");
    ui->tableView->setModel(query);
    while(query2.next())
        cena+=query2.value(2).toInt();
    ui->lineEdit_2->setText(QString::number(cena));

}

void okno_barman::on_pushButtonWyczysc_clicked()
{
    query->setQuery("DELETE FROM element_sprzedazy WHERE id_sprzedazy="+ui->lineEdit->text());
    ui->comboBoxProdukt->setCurrentIndex(-1);
    ui->spinBoxIlosc->setValue(1);
}

void okno_barman::on_pushButtonAnuluj_clicked()
{
    query->setQuery("DELETE FROM element_sprzedazy WHERE id_sprzedazy="+ui->lineEdit->text());
    query->setQuery("DELETE FROM sprzedaz WHERE id_sprzedazy="+ui->lineEdit->text());
    ui->comboBoxProdukt->setCurrentIndex(-1);
    ui->spinBoxIlosc->setValue(1);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void okno_barman::on_pushButtonZakoncz_clicked()
{
    ui->comboBoxProdukt->setCurrentIndex(-1);
    ui->spinBoxIlosc->setValue(1);
    ui->lineEdit->setText("");
    query->setQuery("");
    ui->tableView->setModel(query);
    ui->lineEdit_2->setText("");
}
