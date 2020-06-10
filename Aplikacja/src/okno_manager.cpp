#include "okno_manager.h"
#include "ui_okno_manager.h"
#include "sstream"
okno_manager::okno_manager(QWidget *parent) :
    QWidget(parent),
    baza(qobject_cast<MainWindow*>(parent)->db),
    ui(new Ui::okno_manager)
{
    ui->setupUi(this);
    query = new QSqlQueryModel;
    query2.exec("SELECT nazwa FROM stanowisko");
    while(query2.next()) {
        ui->comboBoxDodaj->addItem(query2.value(0).toString());
        ui->comboBoxStanowisko->addItem(query2.value(0).toString());
        ui->comboBoxPlanStanowisko->addItem(query2.value(0).toString());
        ui->comboBoxObliczStanowisko->addItem(query2.value(0).toString());
    }
    query2.exec("SELECT czas_we, czas_wy FROM zmiana");
    while(query2.next())
        ui->comboBoxZmiana->addItem(query2.value(0).toString()+" - "+query2.value(1).toString());

    aktualizujPracownika(ui->comboBoxPlanStanowisko,ui->comboBoxObliczPracownik);
    aktualizujPracownika(ui->comboBoxObliczStanowisko, ui->comboBoxObliczPracownik);
    on_pushButtonWyczysc_clicked();
    on_pushButtonWyczysc_clicked();
    on_pushButtonWyczysc3_clicked();
    on_pushButtonWyczysc4_clicked();
    query->setQuery("SELECT id_pracownika AS ID, imie, nazwisko, data_zatrudnienia AS 'data zatrudnienia', stanowisko.nazwa AS stanowisko, "
                    "status_zatrudnienia.opis AS 'status', PESEL nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail', adres "
                    "FROM pracownik "
                    "JOIN status_zatrudnienia ON status_zatrudnienia.stan=pracownik.status_zatrudnienia "
                    "JOIN stanowisko ON stanowisko.id_stanowiska=pracownik.stanowisko ORDER BY status_zatrudnienia, ID");
    ui->tableView->setModel(query);
}

okno_manager::~okno_manager()
{
    delete ui;
}

void okno_manager::on_pushButtonZnajdz_clicked()
{
    QString imie, nazwisko, stanowisko, stanowiskoid, q;
    imie=ui->lineEditImie->text();
    nazwisko=ui->lineEditNazwisko->text();
    stanowisko=ui->comboBoxStanowisko->currentText();
    stanowiskoid=QString::number(ui->comboBoxStanowisko->currentIndex()+1);
    q="SELECT id_pracownika AS ID, imie, nazwisko, data_zatrudnienia AS 'data zatrudnienia', stanowisko.nazwa AS stanowisko, "
      "status_zatrudnienia.opis AS 'status', PESEL, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail', adres "
      "FROM pracownik "
      "JOIN status_zatrudnienia ON status_zatrudnienia.stan=pracownik.status_zatrudnienia "
      "JOIN stanowisko ON stanowisko.id_stanowiska=pracownik.stanowisko ";
    if(imie.size()!=0 || nazwisko.size()!=0 || stanowiskoid!="0")
    {
        q+="WHERE 2=2 ";
        if(imie.size()!=0)
            q+="AND imie='"+imie+"' ";
        if(nazwisko.size()!=0)
            q+="AND nazwisko='"+nazwisko+"' ";
        if(stanowiskoid!="0")
            q+="AND stanowisko="+stanowiskoid;
    }
    q+=" ORDER BY status_zatrudnienia, ID";
    query->setQuery(q);
    ui->tableView->setModel(query);
}

void okno_manager::on_pushButtonWyczysc_clicked()
{
    ui->comboBoxStanowisko->setCurrentIndex(-1);
    ui->lineEditImie->clear();
    ui->lineEditNazwisko->clear();
    ui->lineEditIdPracownika->clear();
}

void okno_manager::on_pushButtonUsun_clicked()
{
    QString id;
    id=ui->lineEditIdPracownika->text();
    query->setQuery("UPDATE pracownik SET status_zatrudnienia=2 WHERE id_pracownika="+id);
    query->setQuery("SELECT id_pracownika AS ID, imie, nazwisko, data_zatrudnienia AS 'data zatrudnienia', stanowisko.nazwa AS stanowisko, "
                    "status_zatrudnienia.opis AS 'status', PESEL, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail', adres "
                    "FROM pracownik "
                    "JOIN status_zatrudnienia ON status_zatrudnienia.stan=pracownik.status_zatrudnienia "
                    "JOIN stanowisko ON stanowisko.id_stanowiska=pracownik.stanowisko WHERE id_pracownika="+id);
}

void okno_manager::on_pushButtonZatrudnij_clicked()
{
    QString imie, nazwisko, pesel, nr, email, stanowisko, adres, data, temp2;
    int temp;
    qlonglong temp3;
    bool isGood = true;
    data=QDate::currentDate().toString("yyyy-MM-dd");
    imie = ui->lineEditDodajImie->text();
    nazwisko = ui->lineEditDodajNazwisko->text();
    adres = ui->lineEditDodajAdres->text();
    nr = ui->lineEditDodajNrTel->text();
    email = ui->lineEditDodajEmail->text();
    pesel = ui->lineEditDodajPesel->text();
    stanowisko = QString::number(ui->comboBoxDodaj->currentIndex()+1);
    if (imie.size() == 0 || nazwisko.size() == 0 || nr.size() == 0 || pesel.size() == 0 || email.size() == 0 || stanowisko == "0" || adres.size() == 0)
        QMessageBox::information(this, "Zatrudnianie pracownika", "Wypełnij wszystkie pola");
    else
    {
        temp=nr.toInt();
        if(nr!=QString::number(temp) || nr.size()!=9)
            QMessageBox::information(this, "Zatrudnianie pracownika", "Nieprawidłowy numer telefonu"), isGood = false;
        temp3=pesel.toLongLong();
        if(pesel!=QString::number(temp3) || pesel.size()!=11)
            QMessageBox::information(this, "Zatrudnianie pracownika", "Nieprawidłowy numer PESEL"), isGood = false;
        if(!email.contains("@"))
            QMessageBox::information(this, "Zatrudnianie pracownika", "Nieprawidłowy adres e-mail"), isGood = false;
        query->setQuery("SELECT * FROM pracownik WHERE pesel="+pesel);
        if(query->rowCount()!=0)
            QMessageBox::information(this, "Zatrudnianie pracownika", "W bazie widnieje pracownik o podanym numerze PESEL"), isGood = false;
        if(isGood)
        {
            query->setQuery("INSERT INTO pracownik(imie, nazwisko, adres, nr_telefonu, e_mail, PESEL, stanowisko, data_zatrudnienia, status_zatrudnienia) "
                            "VALUES "
                            "('"+imie+"', "
                            "'"+nazwisko+"', "
                            "'"+adres+"', "
                               +nr+", "
                            "'"+email+"', "
                               +pesel+", "
                               +stanowisko+", "
                            "'"+data+"', "
                            "1)");
            QMessageBox::information(this,"Zatrudnianie pracownika", "Dodano pracownika");
            query2.exec("SELECT id_pracownika AS ID, imie, nazwisko, data_zatrudnienia AS 'data zatrudnienia', stanowisko.nazwa AS stanowisko, "
                        "status_zatrudnienia.opis AS 'status', PESEL, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail', adres "
                        "FROM pracownik "
                        "JOIN status_zatrudnienia ON status_zatrudnienia.stan=pracownik.status_zatrudnienia "
                        "JOIN stanowisko ON stanowisko.id_stanowiska=pracownik.stanowisko ORDER BY ID");
            while(query2.next())
                temp2 = query2.value(0).toString();
            query->setQuery("SELECT id_pracownika AS ID, imie, nazwisko, data_zatrudnienia AS 'data zatrudnienia', stanowisko.nazwa AS stanowisko, "
                            "status_zatrudnienia.opis AS 'status', PESEL, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail', adres "
                            "FROM pracownik "
                            "JOIN status_zatrudnienia ON status_zatrudnienia.stan=pracownik.status_zatrudnienia "
                            "JOIN stanowisko ON stanowisko.id_stanowiska=pracownik.stanowisko WHERE id_pracownika="+temp2);
            ui->tableView_2->setModel(query);
        }

    }

}

void okno_manager::on_pushButtonWyczysc2_clicked()
{
    ui->lineEditDodajImie->clear();
    ui->lineEditDodajAdres->clear();
    ui->lineEditDodajEmail->clear();
    ui->lineEditDodajNrTel->clear();
    ui->lineEditDodajPesel->clear();
    ui->lineEditDodajNazwisko->clear();
    ui->comboBoxDodaj->setCurrentIndex(-1);
}

void okno_manager::aktualizujPracownika(QComboBox * stano, QComboBox * praco)
{
    QString stanowisko;
    QString kupa;
    stanowisko = QString::number(stano->currentIndex()+1);
    QString q = "SELECT id_pracownika, imie, nazwisko FROM pracownik WHERE status_zatrudnienia=1 ";
    praco->clear();
    if(stanowisko != "0")
        q+="AND stanowisko="+stanowisko;
    query2.exec(q);
    while(query2.next())
    {
         praco->addItem(query2.value(1).toString()+" "+query2.value(2).toString()+" ID: " +query2.value(0).toString());
    }
}

void okno_manager::on_comboBoxPlanStanowisko_textActivated(const QString &arg1)
{
    aktualizujPracownika(ui->comboBoxPlanStanowisko, ui->comboBoxPlanPracownik);
}

void okno_manager::on_pushButtonWyczysc3_clicked()
{
    ui->comboBoxPlanStanowisko->setCurrentIndex(-1);
    ui->dateEditPlan->setDate(QDate::currentDate());
    ui->comboBoxZmiana->setCurrentIndex(-1);
    ui->lineEdit->clear();
    aktualizujPracownika(ui->comboBoxPlanStanowisko, ui->comboBoxPlanPracownik);
    ui->comboBoxPlanPracownik->setCurrentIndex(-1);
}

void okno_manager::on_pushButtonDodaj_clicked()
{
    QString pracownik, data, zmiana, temp;
    std::string robocze;
    temp = ui->comboBoxPlanPracownik->currentText();
    data = ui->dateEditPlan->date().toString("yyyy-MM-dd");
    zmiana = QString::number(ui->comboBoxZmiana->currentIndex()+1);
    std::istringstream a(temp.toStdString());
    int id;
    a >> robocze >> robocze >> robocze >> id;
    pracownik=QString::number(id);
    if(temp.size() == 0 || zmiana == "0")
        QMessageBox::information(this, "Układanie harmonogramu", "Podaj parametry");
    else{
        query->setQuery("SELECT * FROM harmonogram "
                        "WHERE id_pracownika="+pracownik+
                        " AND dzien='"+data+"'");
        if(query->rowCount()!=0)
            QMessageBox::information(this, "Układanie harmonogramu", "Ten pracownik jest już w harmonogramie na ten dzień");
        else
            query->setQuery("INSERT INTO harmonogram (dzien, id_pracownika, id_zmiany) VALUES "
                        "('"+data+"', "
                            +pracownik+","
                            +zmiana+")");
    }
    aktualizujDzien();

}

void okno_manager::on_pushButtonPokaz_clicked()
{
    aktualizujDzien();
}

void okno_manager::on_pushButtonPlanUsun_clicked()
{
    QString pracownik, data;
    data = ui->dateEditPlan->date().toString("yyyy-MM-dd");
    pracownik = ui->lineEdit->text();
    if(pracownik.size() == 0)
        QMessageBox::information(this, "Ukadanie harmonogramu", "Podaj ID pracownika");
    else{
        query->setQuery("SELECT * FROM harmonogram WHERE dzien='"+data+"' AND id_pracownika="+pracownik);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Ukadanie harmonogramu", "W tym dniu nie ma takiego pracownika");
        else
            query->setQuery("DELETE FROM harmonogram WHERE dzien='"+data+"' AND id_pracownika="+pracownik);

    }
    aktualizujDzien();
}

void okno_manager::aktualizujDzien()
{
    query->setQuery("SELECT harmonogram.id_pracownika AS 'ID pracownika', imie, nazwisko, stanowisko.nazwa AS stanowisko, czas_we AS poczatek, czas_wy AS koniec "
                    "FROM harmonogram "
                    "JOIN pracownik ON pracownik.id_pracownika=harmonogram.id_pracownika "
                    "JOIN stanowisko ON pracownik.stanowisko=stanowisko.id_stanowiska "
                    "JOIN zmiana ON harmonogram.id_zmiany=zmiana.id_zmiany "
                    "WHERE dzien='"+ui->dateEditPlan->date().toString("yyyy-MM-dd")+"'");
    ui->tableView_3->setModel(query);
}

void okno_manager::on_pushButtonWyczysc4_clicked()
{
    ui->comboBoxObliczStanowisko->setCurrentIndex(-1);
    aktualizujPracownika(ui->comboBoxObliczStanowisko, ui->comboBoxObliczPracownik);
    ui->comboBoxObliczPracownik->setCurrentIndex(-1);
    ui->dateEditObliczOd->setDate(QDate::currentDate());
    ui->dateEditObliczDo->setDate(QDate::currentDate());

}

void okno_manager::on_pushButtonOblicz_clicked()
{
    QString pracownik, data1, data2, temp, q;
    int id;
    std::string robocze;
    temp = ui->comboBoxObliczPracownik->currentText();
    data1 = ui->dateEditObliczOd->date().toString("yyyy-MM-dd");
    data2 = ui->dateEditObliczDo->date().toString("yyyy-MM-dd");
    std::istringstream a(temp.toStdString());
    a >> robocze >> robocze >> robocze >> id;
    pracownik=QString::number(id);
    if(ui->comboBoxObliczPracownik->currentText()==-1)
        QMessageBox::information(this, "Obliczanie wynagrodzenia","Wybierz pracownika");
    else {
        q = "SELECT harmonogram.id_pracownika AS 'ID pracownika', imie, nazwisko, stanowisko.nazwa, SUM(godziny) AS godziny, SUM(godziny*wynagrodzenie) AS wynagrodzenie "
            "FROM harmonogram "
            "JOIN pracownik ON harmonogram.id_pracownika=pracownik.id_pracownika "
            "JOIN stanowisko ON pracownik.stanowisko=stanowisko.id_stanowiska "
            "JOIN zmiana ON harmonogram.id_zmiany=zmiana.id_zmiany "
            "WHERE harmonogram.id_pracownika="+pracownik+
            " AND dzien>='"+data1+"' AND dzien<='"+data2+"'";
        query->setQuery(q);
        ui->tableView_4->setModel(query);
    }
}

void okno_manager::on_pushButtonObliczWszystkich_clicked()
{
   QString data1, data2;
   data1 = ui->dateEditObliczOd->date().toString("yyyy-MM-dd");
   data2 = ui->dateEditObliczDo->date().toString("yyyy-MM-dd");
   QString q = "SELECT harmonogram.id_pracownika AS 'ID pracownika', imie, nazwisko, stanowisko.nazwa, SUM(godziny) AS godziny, SUM(godziny*wynagrodzenie) AS wynagrodzenie "
                 "FROM harmonogram "
                 "JOIN pracownik ON harmonogram.id_pracownika=pracownik.id_pracownika "
                 "JOIN stanowisko ON pracownik.stanowisko=stanowisko.id_stanowiska "
                 "JOIN zmiana ON harmonogram.id_zmiany=zmiana.id_zmiany "
                 "WHERE dzien>='"+data1+"' AND dzien<='"+data2+"' "
                 "GROUP BY harmonogram.id_pracownika ORDER BY harmonogram.id_pracownika ";
    query->setQuery(q);
    ui->tableView_4->setModel(query);
}
