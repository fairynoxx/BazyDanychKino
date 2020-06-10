#include "okno_technik.h"
#include "ui_okno_technik.h"

okno_technik::okno_technik(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::okno_technik),
    baza(qobject_cast<MainWindow*>(parent)->db)
{
    ui->setupUi(this);
    query = new QSqlQueryModel;
    ui->tabWidget->removeTab(1);
    ui->comboBoxParametr->addItem("tytuł");
    ui->comboBoxParametr->addItem("sala");
    ui->dateTimeEditPoczatek->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditKoniec->setDateTime(QDateTime::currentDateTime().addDays(30));
    ui->checkBoxData->setChecked(true);
    query->setQuery("SELECT id_seansu AS 'ID', film.tytul AS 'tytul', czas_seansu AS 'czas seansu', id_sali AS 'sala', dzwiek.wersja AS 'wersja' FROM seans "
                    "JOIN film ON seans.id_filmu=film.id_filmu "
                    "JOIN dzwiek ON seans.dzwiek=dzwiek.id_dzwieku "
                    "WHERE"+sprawdzDaty());
    ui->tableView->setModel(query);
}
okno_technik::~okno_technik()
{
    delete ui;
}

void okno_technik::on_pushButtonZnajdzFilm_clicked()
{
    QString parametr, temp;
    temp = "SELECT tytul, wytwornia, rezyser, data_premiery AS 'data piermiery', czas_trwania AS 'czas trwania', ograniczenia.wiek AS ograniczenia "
           "FROM film JOIN ograniczenia ON ograniczenia.id_ograniczenia=film.ograniczenia_wiekowe"
           "WHERE tytul LIKE '%"+parametr+"%'";
    parametr=ui->lineEdit->text();
    if (parametr.size()==0 || !ui->comboBoxParametr->currentText().contains("tyt"))
        QMessageBox::information(this,"Szukaj","Nieprawidłowe parametry wyszukiwania");
    else
    {
        query->setQuery("SELECT tytul, wytwornia, rezyser, data_premiery AS 'data premiery', czas_trwania AS 'czas trwania', ograniczenia.wiek "
                        "FROM film JOIN ograniczenia ON ograniczenia.id_ograniczenia=film.ograniczenie_wiekowe "
                        "WHERE tytul LIKE '%"+parametr+"%'");
        ui->tableView->setModel(query);
    }
}

QString okno_technik::sprawdzDaty()
{
    QString temp;
    temp = " czas_seansu >'"+ui->dateTimeEditPoczatek->dateTime().toString("yyyy-MM-dd hh:mm:ss")+
            "' AND czas_seansu <'"+ui->dateTimeEditKoniec->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"'";
    return temp;
}

void okno_technik::on_pushButtonZnajdzSeans_clicked()
{
    QString parametr, temp, temp2;
    parametr=ui->lineEdit->text();
    temp="SELECT film.tytul AS tytul, czas_seansu AS 'czas seansu', id_sali AS sala, dzwiek.wersja AS wersja FROM seans "
         "JOIN film ON film.id_filmu=seans.id_filmu "
         "JOIN dzwiek ON dzwiek.id_dzwieku=seans.dzwiek "
         "WHERE ";
    temp2=ui->comboBoxParametr->currentText();
    if(temp2.contains("tyt")){
        temp2="tytul";
        temp+=temp2+" LIKE '%"+parametr+"%'";
    }
    else
        temp+="id_sali="+parametr;
    if(ui->checkBoxData->isChecked())
        temp+=" AND "+sprawdzDaty();
    temp+=" ORDER BY czas_seansu";
    query->setQuery(temp);
    ui->tableView->setModel(query);
}


