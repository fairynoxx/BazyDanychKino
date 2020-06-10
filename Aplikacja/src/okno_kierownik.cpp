#include "okno_kierownik.h"
#include "ui_okno_kierownik.h"

okno_kierownik::okno_kierownik(QWidget *parent) :
    QWidget(parent),
    baza(qobject_cast<MainWindow*>(parent)->db),
    ui(new Ui::okno_kierownik)
{
    query = new QSqlQueryModel;
    ui->setupUi(this);
    query2.exec("SELECT * FROM film ORDER BY tytul");
    while(query2.next())
    {
        ui->comboBoxTytul->addItem(query2.value(1).toString());
        ui->comboBoxTytul2->addItem(query2.value(1).toString());
        ui->comboBoxTytul3->addItem(query2.value(1).toString());
    }
    query2.exec("SELECT * FROM sala");
    while (query2.next()) {
        ui->comboBoxSala->addItem(query2.value(0).toString());
        ui->comboBoxSala2->addItem(query2.value(0).toString());
    }
    query2.exec("SELECT * FROM dzwiek");
    while (query2.next()) {
        ui->comboBoxDzwiek->addItem(query2.value(1).toString());
        ui->comboBoxDzwiek2->addItem(query2.value(1).toString());
    }
    query2.exec("SELECT nazwa FROM produkt");
    while(query2.next()){
        ui->comboBoxProdukt->addItem(query2.value(0).toString());
        ui->comboBoxProdukt2->addItem(query2.value(0).toString());
    }
    wyczyscPola1();
    wyczyscPola2();
    wyczyscPola3();
    wyczyscPola4();
    on_pushButtonWyczysc5_clicked();
    query->setQuery("SELECT id_seansu AS ID, tytul, czas_seansu AS 'czas seansu', dzwiek.wersja AS wersja FROM seans JOIN film ON film.id_filmu=seans.id_filmu "
                    "JOIN dzwiek ON dzwiek.id_dzwieku=seans.dzwiek "
                    "ORDER BY czas_seansu");
    ui->tableViewSeanse->setModel(query);
}

okno_kierownik::~okno_kierownik()
{
    delete ui;
}

void okno_kierownik::on_pushButtonDodajSeans_clicked()
{
    QDateTime czas1, czas2;
    int tempsec;
    QString tytul, wersja, sala, temp2, temp3,temp;
    tytul=ui->comboBoxTytul->currentText();
    czas1=ui->dateTimeEdit->dateTime();
    wersja=QString::number(ui->comboBoxDzwiek->currentIndex()+1);
    temp3=ui->comboBoxDzwiek->currentText();
    sala=ui->comboBoxSala->currentText();
    if(tytul.size()==0 || temp3.size()==0 || sala.size()==0)
        QMessageBox::information(this,"Dodawanie seansu","Podaj wszystkie parametry");
    else {
    czas2=czas1.addSecs(3600);
    query->setQuery("SELECT czas_trwania, id_filmu FROM film "
                    "WHERE tytul='"+tytul+"'");
    tempsec=QTime(0,0,0).secsTo(query->record(0).value(0).toTime());
    temp2=query->record(0).value(1).toString();
    czas2=czas2.addSecs(tempsec);
    query->setQuery("SELECT * FROM seans "
    "JOIN film ON seans.id_filmu=film.id_filmu "
    "WHERE id_sali="+sala+
    " AND ("
    "((seans.czas_seansu<'"+czas1.toString("yyyy-MM-dd hh:mm:ss")+"') AND (ADDTIME(ADDTIME(seans.czas_seansu, film.czas_trwania), '1:00:00') > '"+czas1.toString("yyyy-MM-dd hh:mm:ss")+"'))"
    " OR "
    "((seans.czas_seansu<'"+czas2.toString("yyyy-MM-dd hh:mm:ss")+"') AND (ADDTIME(ADDTIME(seans.czas_seansu, film.czas_trwania), '1:00:00')> '"+czas2.toString("yyyy-MM-dd hh:mm:ss")+"')))");
    ui->tableViewSeanse->setModel(query);
    if(query->rowCount()!=0)
        QMessageBox::information(this,"Dodawanie seansu","Sala zajęta");
    else{
        query->setQuery("INSERT INTO seans (czas_seansu,id_sali,id_filmu,dzwiek) VALUES "
                        "('"+czas1.toString("yyyy-MM-dd hh:mm:ss")+"',"
                        "'"+sala+"',"
                        "'"+temp2+"',"
                        "'"+wersja+"')");
        QMessageBox::information(this,"Dodawanie seansu","Dodano seans");
        query2.exec("SELECT MAX(id_seansu) FROM seans");
        while(query2.next())
            temp = query2.value(0).toString();
        query->setQuery("SELECT id_seansu AS ID, tytul, czas_seansu AS 'czas seansu', id_sala AS sala, dzwiek.wersja AS wersja FROM seans JOIN film ON film.id_filmu=seans.id_filmu "
                        "JOIN dzwiek ON dzwiek.id_dzwieku=seans.dzwiek "
                        "WHERE id_seansu="+temp);
        ui->tableViewSeanse->setModel(query);
        dodajMiejsce(temp);
        }
    }
}

void okno_kierownik::on_pushButtonWyszukaj_clicked()
{
     QString tytul, wersja, sala, czas1, czas2, q, temp;
     tytul = ui->comboBoxTytul2->currentText();
     wersja = ui->comboBoxDzwiek2->currentText();
     temp = ui->comboBoxDzwiek2->currentIndex()+1;
     sala = ui->comboBoxSala2->currentText();
     czas1 = ui->dateTimeEditCzasOd->dateTime().toString("yyyy-MM-dd hh:mm:ss");
     czas2 = ui->dateTimeEditCzasDo->dateTime().toString("yyyy-MM-dd hh:mm:ss");
     q = "SELECT id_seansu AS ID, tytul, czas_seansu AS 'czas seansu', id_sali AS sala, wersja FROM seans "
         "JOIN dzwiek ON seans.dzwiek=dzwiek.id_dzwieku "
         "JOIN film ON seans.id_filmu=film.id_filmu "
         "WHERE czas_seansu > '"+czas1+"' AND czas_seansu < '"+czas2+"' ";
     if (tytul.size()!=0)
         q+="AND tytul='"+tytul+"' ";
     if (sala.size()!=0)
         q+="AND id_sali="+sala+" ";
     if (wersja.size()!=0)
         q+="AND wersja='"+temp+"' ";
     q+="ORDER BY id_seansu";
     query->setQuery(q);
     ui->tableViewSeanse->setModel(query);
}

void okno_kierownik::on_pushButtonUsunSeans_clicked()
{
    QString idseansu;
    idseansu=ui->lineEdit->text();
    if(idseansu.size()==0)
        QMessageBox::information(this, "Usuwanie seansu", "Podaj ID seansu");
    else
    {
        query->setQuery("SELECT * FROM seans WHERE id_seansu="+idseansu);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Usuwanie seansu", "Nie ma takiego seansu");
        else
        {
            usunMiejsce(idseansu);
            query->setQuery("DELETE FROM seans WHERE id_seansu="+idseansu);
            QMessageBox::information(this, "Usuwanie seansu", "Usunięto seans");
        }
    }
}

void okno_kierownik::wyczyscPola1()
{
    ui->comboBoxSala->setCurrentIndex(-1);
    ui->comboBoxTytul->setCurrentIndex(-1);
    ui->comboBoxDzwiek->setCurrentIndex(-1);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

void okno_kierownik::wyczyscPola2()
{
    ui->comboBoxDzwiek2->setCurrentIndex(-1);
    ui->comboBoxTytul2->setCurrentIndex(-1);
    ui->comboBoxSala2->setCurrentIndex(-1);
    ui->dateTimeEditCzasOd->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditCzasDo->setDateTime(QDateTime::currentDateTime());
    ui->lineEdit->clear();
}

void okno_kierownik::wyczyscPola3()
{
    ui->comboBoxTytul3->setCurrentIndex(-1);
    ui->dateTimeEditBiletyOd->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditBiletyDo->setDateTime(QDateTime::currentDateTime());
    ui->checkBoxCzas->setChecked(false);
    ui->checkBoxTytul->setChecked(false);
    ui->checkBoxIdSeansu->setChecked(false);
    ui->lineEditIdSeansu->clear();
}

void okno_kierownik::wyczyscPola4()
{
    ui->comboBoxProdukt->setCurrentIndex(-1);
    ui->dateTimeEditBarOd->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditBarDo->setDateTime(QDateTime::currentDateTime());
    ui->checkBoxProdukt->setChecked(false);
    ui->checkBoxCzas2->setChecked(false);
    ui->textBrowser2->clear();

}
void okno_kierownik::on_pushButtonWyczysc2_clicked()
{
   wyczyscPola2();
}

void okno_kierownik::on_pushButtonWyczysc_clicked()
{
    wyczyscPola1();
}

void okno_kierownik::dodajMiejsce(QString idseansu)
{
    QString rzad, kolumna, temp;
    query2.exec("SELECT liczba_rzedow, liczba_miejsc_w_rzedzie FROM seans "
                    "JOIN sala ON seans.id_sali=sala.id_sali "
                    "WHERE id_seansu="+idseansu);
    while(query2.next()) {
    rzad=query2.value(0).toInt();
    kolumna=query2.value(1).toInt();
    }
    for (int i=1;i<=rzad;i++)
    {
        for(int j=1;j<=kolumna;j++)
        {
            query->setQuery("INSERT INTO bilet (rzad, nr_w_rzedzie, id_seansu, status_miejsca) VALUES "
                            "("+QString::number(i)+", "
                            +QString::number(j)+", "
                            +idseansu+", "
                            "1)");
        }
    }
}

void okno_kierownik::usunMiejsce(QString idseansu)
{
    query->setQuery("DELETE FROM bilet WHERE id_seansu="+idseansu);
}

void okno_kierownik::on_pushButtonWyczysc3_clicked()
{
    wyczyscPola3();
}

void okno_kierownik::on_pushButtonWyczysc4_clicked()
{
    wyczyscPola4();
}

void okno_kierownik::on_checkBoxIdSeansu_stateChanged(int arg1)
{
    if (arg1==2)
    {
        ui->checkBoxCzas->setChecked(false);
        ui->checkBoxTytul->setChecked(false);
    }
}

void okno_kierownik::on_checkBoxCzas_stateChanged(int arg1)
{
    if (arg1==2)
    {
        ui->checkBoxIdSeansu->setChecked(false);
    }
}

void okno_kierownik::on_checkBoxTytul_stateChanged(int arg1)
{
    if (arg1==2)
    {
        ui->checkBoxIdSeansu->setChecked(false);
    }
}

void okno_kierownik::on_pushButtonSprawdz_clicked()
{
    QString q, tytul, idseansu, czas1, czas2, temp, temp2;
    int cena1 = 0, cena2 = 0, cena = 0;
    tytul=ui->comboBoxTytul3->currentText();
    idseansu=ui->lineEditIdSeansu->text();
    czas1 = ui->dateTimeEditBiletyOd->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    czas2 = ui->dateTimeEditBiletyDo->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    q = "SELECT opis, COUNT(id_miejsca) AS ilosc, SUM(cena) AS przychod FROM bilet "
                    "JOIN rodzaj_biletu ON rodzaj_biletu.rodzaj=bilet.rodzaj_biletu "
                    "JOIN seans ON bilet.id_seansu= seans.id_seansu "
                    "JOIN film ON seans.id_filmu=film.id_filmu WHERE status_miejsca=3 ";
    if (ui->checkBoxCzas->isChecked() || ui->checkBoxTytul->isChecked() || ui->checkBoxIdSeansu->isChecked())  {
        if(ui->checkBoxTytul->isChecked() && !ui->checkBoxCzas->isChecked())
         {
             if (tytul.size()==0){
                 QMessageBox::information(this, "Bilety","Wybierz tytuł");
                 temp2+="Przychód ze wszystkich sprzedanych biletów: ";
             }
             else
             {
                 temp2+="Przychód z filmu "+tytul+": ";
                 q+="AND tytul='"+tytul+"'";
             }
         }
        else if (ui->checkBoxTytul->isChecked() && ui->checkBoxCzas->isChecked())
        {
            if (tytul.size()==0)
                QMessageBox::information(this, "Bilety","Wybierz tytuł");
            else
            {
                temp2+="Przychód z filmów ";
                temp2+=tytul+" w czasie od "+czas1+" do "+czas2+": ";
                q+=" AND tytul='"+tytul+"' AND czas_seansu>'"+czas1+"' AND czas_seansu<'"+czas2+"'";
            }
        }
        else if (!ui->checkBoxTytul->isChecked() && ui->checkBoxCzas->isChecked())
        {
            temp2+="Przychód z filmów w czasie od "+czas1+" do "+czas2+": ";
            q+="AND czas_seansu>'"+czas1+"' AND czas_seansu<'"+czas2+"'";
        }
        else if (ui->checkBoxIdSeansu->isChecked())
        {
            if (idseansu.size()==0)
                QMessageBox::information(this, "Bilety","Podaj ID seansu");
            else{
                query->setQuery("SELECT tytul, czas_seansu FROM seans JOIN film ON seans.id_filmu=film.id_filmu WHERE id_seansu="+idseansu);
                if (query->rowCount()==0)  {
                        QMessageBox::information(this, "Bilety","Nie ma takiego seansu");
                        temp2+="Przychód ze wszystkich sprzedanych biletów: ";
                }
                else
                {
                    temp2+="Przychód z seansu filmu "+query->record(0).value(0).toString()+" dnia "+query->record(0).value(1).toDate().toString("dd-MM-yyyy")+
                            " o godzinie "+query->record(0).value(1).toTime().toString("hh:mm")+": ";
                    q+="AND bilet.id_seansu="+idseansu;
                }
              }

        }
    }
    else
        temp2+="Przychód ze wszystkich sprzedanych biletów: ";
    q+=" GROUP BY rodzaj_biletu.opis";
    query->setQuery(q);
    cena1=query->record(0).value(2).toInt();
    cena2=query->record(1).value(2).toInt();
    cena=cena1+cena2;
    ui->textBrowser->setText(temp2+"\n"+QString::number(cena)+"zł");
    ui->tableViewBilety->setModel(query);
}


void okno_kierownik::on_pushButtonSprawdz2_clicked()
{
    QString produkt, produktId, data1, data2, q, temp;
    int cena=0;
    produkt=ui->comboBoxProdukt->currentText();
    produktId=QString::number(ui->comboBoxProdukt->currentIndex()+1);
    data1=ui->dateTimeEditBarOd->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    data2=ui->dateTimeEditBarDo->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    q = "SELECT nazwa, SUM(ilosc) AS ilosc, SUM(cena*ilosc) AS przychod FROM element_sprzedazy "
                    "JOIN sprzedaz ON element_sprzedazy.id_sprzedazy=sprzedaz.id_sprzedazy "
                    "JOIN produkt ON produkt.id_produktu= element_sprzedazy.id_produktu ";
    if(ui->checkBoxProdukt->isChecked() && !ui->checkBoxCzas2->isChecked())
    {
        if(produkt.size()==0)
            QMessageBox::information(this, "Bar", "Wybierz produkt");
        else
        {
            temp="Przychód ze sprzedaży produktu "+produkt+": ";
            q+="WHERE element_sprzedazy.id_produktu="+produktId;
        }
    }
    else if(!ui->checkBoxProdukt->isChecked() && ui->checkBoxCzas2->isChecked())
    {
        q+="WHERE data_sprzedazy>'"+data1+"' AND data_sprzedazy<'"+data2+"' ";
        temp="Przychód ze sprzedaży w czasie od "+data1+" do "+data2+": ";
    }
    else if(ui->checkBoxProdukt->isChecked() && ui->checkBoxCzas2->isChecked())
    {
        temp="Przychód ze sprzedaży produktu "+produkt+" w czasie od "+data1+" do "+data2+": ";
        q+="WHERE element_sprzedazy.id_produktu="+produktId+" AND data_sprzedazy>'"+data1+"' AND data_sprzedazy<'"+data2+"' ";
    }
    else
    {
        temp="Przychód ze sprzedaży produktów: ";
    }
    q+=" GROUP BY nazwa";
    query->setQuery(q);
    query2.exec(q);
    while(query2.next())
        cena+=query2.value(2).toInt();
    ui->textBrowser2->setText(temp+"\n"+QString::number(cena)+"zł");
    ui->tableView->setModel(query);
}



void okno_kierownik::on_pushButtonZnajdz_clicked()
{
    QString produktid;
    produktid=QString::number(ui->comboBoxProdukt2->currentIndex()+1);
    if(produktid==0)
        QMessageBox::information(this,"Produkt","Wybierz produkt");
    else
    {
        query->setQuery("SELECT id_produktu AS ID, nazwa,cena,dostepnosc_produktu.opis AS dostepnosc "
                        "FROM produkt "
                        "JOIN dostepnosc_produktu ON produkt.dostepnosc=dostepnosc_produktu.stan "
                        "WHERE id_produktu="+produktid);
        ui->tableView_2->setModel(query);
        ui->lineEdit_2->setText(query->record(0).value(1).toString());
        ui->spinBox->setValue((query->record(0).value(2).toInt()));
    }

}

void okno_kierownik::on_pushButtonEdytuj_clicked()
{
    QString nazwa, cena, produktid;
    produktid=QString::number(ui->comboBoxProdukt2->currentIndex()+1);
    nazwa=ui->lineEdit_2->text();
    cena=QString::number(ui->spinBox->value());
    if(nazwa.size()==0)
        QMessageBox::information(this,"Produkt","Podaj nazwę produktu");
    else
    {
        query->setQuery("SELECT * FROM produkt WHERE nazwa='"+nazwa+" AND nazwa!='"+ui->comboBoxProdukt2->currentText());
        if(query->rowCount()!=0)
            QMessageBox::information(this,"Produkt","Istnieje już taki produkt");
        else{
            query->setQuery("UPDATE produkt SET nazwa='"+nazwa+"', cena="+cena+" WHERE id_produktu="+produktid);
            query->setQuery("SELECT id_produktu AS ID, nazwa,cena,dostepnosc_produktu.opis AS dostepnosc "
                        "FROM produkt "
                        "JOIN dostepnosc_produktu ON produkt.dostepnosc=dostepnosc_produktu.stan "
                        "WHERE id_produktu="+produktid);
            on_pushButtonWyczysc5_clicked();
        }
    }
}

void okno_kierownik::on_pushButtonWyczysc5_clicked()
{
    ui->lineEdit_2->clear();
    ui->spinBox->setValue(0);
    ui->comboBoxProdukt2->clear();
    query2.exec("SELECT nazwa FROM produkt");
    while(query2.next()){
        ui->comboBoxProdukt->addItem(query2.value(0).toString());
        ui->comboBoxProdukt2->addItem(query2.value(0).toString());
    }
    ui->comboBoxProdukt2->setCurrentIndex(-1);
}
