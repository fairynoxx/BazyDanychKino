#include "dodawanie_biletow.h"
#include "ui_dodawanie_biletow.h"
#include "okno_kasjer.h"

dodawanie_biletow::dodawanie_biletow(QString id_seansu, QString id_klienta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodawanie_biletow),
    bd(qobject_cast<okno_kasjer*>(parent)->baza),
    idklient(id_klienta),
    idseansu(id_seansu)
{
    ui->setupUi(this);
    query = new QSqlQueryModel;
    QString temp;
    if(idklient=="0")
        isRes=false;
    else{
    query->setQuery("SELECT * FROM rezerwacja WHERE id_klienta="+idklient+" ORDER BY id_rezerwacji DESC");
    idrezerwacji = query->record(0).value(0).toString();
    }
    aktualizujRzad();
    ui->comboBoxRzad->setCurrentIndex(-1);
    query2.exec("SELECT opis,cena FROM rodzaj_biletu");
    while(query2.next())
        ui->comboBoxRodzaj->addItem(query2.value(0).toString()+" - "+query2.value(1).toString()+"zl");

}

dodawanie_biletow::~dodawanie_biletow()
{
    delete ui;
}

void dodawanie_biletow::on_comboBoxRzad_textActivated(const QString &arg1)
{
    aktualizujKolumne(arg1);
}

void dodawanie_biletow::aktualizujRzad()
{
    QString temp;
    query2.exec("SELECT rzad, nr_w_rzedzie FROM bilet WHERE id_seansu="+idseansu+" AND status_miejsca=1");
    while(query2.next())
    {
        temp = query2.value(0).toString();
        if (ui->comboBoxRzad->findText(temp)==-1)
            ui->comboBoxRzad->addItem(temp);
    }
}

void dodawanie_biletow::aktualizujKolumne(QString rzad)
{
    ui->comboBoxKolumna->clear();
    query2.exec("SELECT rzad, nr_w_rzedzie FROM bilet WHERE id_seansu="+idseansu+
                " AND status_miejsca=1 AND rzad="+rzad);
    while(query2.next())
    {
         ui->comboBoxKolumna->addItem(query2.value(1).toString());
    }
}

void dodawanie_biletow::on_pushButtonDodajBilet_clicked()
{
    QString rzad, kolumna, rodzaj;
    rzad=ui->comboBoxRzad->currentText();
    kolumna=ui->comboBoxKolumna->currentText();
    if (ui->comboBoxRodzaj->currentText().contains("normalny"))
        rodzaj=QString::number(1);
    else
        rodzaj=QString::number(2);
    if(rzad.size()==0 || kolumna.size()==0)
        QMessageBox::information(this, "Dodawanie biletów", "Wybierz miejsca");
    else {
    if(isRes)
    {
    query->setQuery("UPDATE bilet SET id_rezerwacji="+idrezerwacji+", status_miejsca="+QString::number(2)+", rodzaj_biletu="+rodzaj+
                    " WHERE id_seansu ="+idseansu+" AND rzad="+rzad+" AND nr_w_rzedzie="+kolumna);
    query->setQuery("SELECT rzad, nr_w_rzedzie, rodzaj_biletu.opis FROM bilet JOIN rezerwacja "
                    "ON rezerwacja.id_rezerwacji=bilet.id_rezerwacji "
                    "JOIN rodzaj_biletu ON bilet.rodzaj_biletu=rodzaj_biletu.rodzaj "
                    "WHERE bilet.id_rezerwacji="+idrezerwacji);
    }
    else
    {
    query->setQuery("UPDATE bilet SET status_miejsca=5, rodzaj_biletu="+rodzaj+
                    " WHERE id_seansu ="+idseansu+" AND rzad="+rzad+" AND nr_w_rzedzie="+kolumna);
    query->setQuery("SELECT rzad, nr_w_rzedzie, rodzaj_biletu.opis FROM bilet "
                    "JOIN rodzaj_biletu ON bilet.rodzaj_biletu=rodzaj_biletu.rodzaj "
                    "WHERE bilet.id_rezerwacji IS NULL AND status_miejsca=5");
    }
    ui->tableView->setModel(query);
    aktualizujRzad();
    aktualizujKolumne(rzad);
    }
}

void dodawanie_biletow::on_pushButtonZakoncz_clicked()
{
    query->setQuery("UPDATE bilet SET status_miejsca=3 WHERE status_miejsca=5");
    if(isRes)
        QMessageBox::information(this,"Dodawanie rezerwacji", "Utworzono rezerwację");
    else
        QMessageBox::information(this,"Dodawanie biletów", "Dodano bilety");
    this->close();
}

void dodawanie_biletow::on_pushButtonUsun_clicked()
{
    if(isRes)
    {
    query->setQuery("UPDATE bilet SET id_rezerwacji=NULL, status_miejsca=1, rodzaj_biletu=NULL "
                    "WHERE id_rezerwacji="+idrezerwacji);
    query->setQuery("SELECT rzad, nr_w_rzedzie, rodzaj_biletu.opis FROM bilet JOIN rezerwacja "
                    "ON rezerwacja.id_rezerwacji=bilet.id_rezerwacji "
                    "JOIN rodzaj_biletu ON bilet.rodzaj_biletu=rodzaj_biletu.rodzaj "
                    "WHERE bilet.id_rezerwacji="+idrezerwacji);
    }
    else {
        query->setQuery("UPDATE bilet SET id_rezerwacji=NULL, status_miejsca=1, rodzaj_biletu=NULL "
                        "WHERE id_rezerwacji IS NULL AND status_miejsca=5");
        query->setQuery("SELECT rzad, nr_w_rzedzie, rodzaj_biletu.opis FROM bilet JOIN rezerwacja "
                        "ON rezerwacja.id_rezerwacji=bilet.id_rezerwacji "
                        "JOIN rodzaj_biletu ON bilet.rodzaj_biletu=rodzaj_biletu.rodzaj "
                        "WHERE bilet.id_rezerwacji IS NULL AND status_miesjca=5");
    }
    ui->tableView->setModel(query);
    aktualizujRzad();
    aktualizujKolumne(ui->comboBoxRzad->currentText());
}
