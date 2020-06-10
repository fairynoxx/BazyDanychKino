#include "okno_kasjer.h"
#include "ui_okno_kasjer.h"

okno_kasjer::okno_kasjer(QWidget *parent) :
    QWidget(parent),
    baza(qobject_cast<MainWindow*>(parent)->db),
    ui(new Ui::okno_kasjer)
{
    ui->setupUi(this);
    query = new QSqlQueryModel;
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(30));
    query->setQuery(seanseMiesiac()+" ORDER BY czas_seansu DESC");
    ui->tableView_2->setModel(query);
}

okno_kasjer::~okno_kasjer()
{
    delete ui;
}

void okno_kasjer::on_pushButtonDodajKlienta_clicked()
{
    QString imie, nazwisko, nr_telefonu, email;
    bool isGood=true;
    int temp;
    imie = ui->lineEditDodajImie->text();
    nazwisko = ui->lineEditDodajNazwisko->text();
    nr_telefonu=ui->lineEditDodajNr->text();
    email=ui->lineEditDodajEmail->text();
    query->setQuery("SELECT * FROM klient WHERE nr_telefonu="+nr_telefonu+" AND e_mail='"+email+"'");
    if(query->rowCount()==0)
    {
        temp=nr_telefonu.toInt();
        if(QString::number(temp)==nr_telefonu && nr_telefonu.size()!=9)
            QMessageBox::information(this,"Edycja klienta", "Nieprawidłowy numer telefonu"), isGood=false;
        if(!email.contains("@"))
            QMessageBox::information(this,"Edycja klienta", "Nieprawidłowy adres e-mail"), isGood=false;
        if(imie.size()==0 || nazwisko.size()==0 || nr_telefonu.size()==0 || email.size()==0)
            QMessageBox::information(this,"Dodawanie klienta","Nie wypełniono wszystkich pól");
        else if (isGood){
        query->setQuery("INSERT INTO klient (imie, nazwisko, nr_telefonu, e_mail) VALUES"
        "('"+imie+"','"+nazwisko+"','"+nr_telefonu+"','"+email+"')");
        QMessageBox::information(this,"Dodawanie klienta", "Dodano klienta");
        on_pushButtonWyczysc_clicked();
        }
    }
    else
        QMessageBox::information(this, "Dodawanie klienta", "Nie udało się dodać klienta - klient widnieje w bazie");
    query->setQuery("SELECT id_klienta AS id, imie, nazwisko, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail' FROM klient");
    ui->tableView->setModel(query);
}

void okno_kasjer::on_pushButtonZnajdzKlienta_clicked()
{
    QString imie, nazwisko, nr_telefonu, email, q;
    imie = ui->lineEditDodajImie->text();
    nazwisko = ui->lineEditDodajNazwisko->text();
    nr_telefonu=ui->lineEditDodajNr->text();
    email=ui->lineEditDodajEmail->text();
    if (nr_telefonu.size()==0)
        nr_telefonu="00000";
    q="SELECT id_klienta AS ID, imie, nazwisko, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail' FROM klient WHERE 2=2 ";
    if(imie.size()!=0)
        q+="AND imie='"+imie+"' ";
    if(nazwisko.size()!=0)
        q+="AND nazwisko='"+nazwisko+"' ";
    if(email.size()!=0)
        q+="AND email='"+email+"' ";
    if(nr_telefonu!="00000")
        q+="AND nr_telefonu="+nr_telefonu+" ";
    q+="ORDER BY id_klienta";
    query->setQuery(q);
    ui->tableView->setModel(query);

}

void okno_kasjer::on_pushButtonWyczysc_clicked()
{
    ui->lineEditDodajImie->clear();
    ui->lineEditDodajNazwisko->clear();
    ui->lineEditDodajNr->clear();
    ui->lineEditDodajEmail->clear();
}

void okno_kasjer::on_pushButtonEdytuj_clicked()
{
    QString imie, nazwisko, nr_telefonu, email, id;
    int temp;
    bool isGood=true;
    imie = ui->lineEditDodajImie->text();
    nazwisko = ui->lineEditDodajNazwisko->text();
    nr_telefonu=ui->lineEditDodajNr->text();
    email=ui->lineEditDodajEmail->text();
    id = ui->lineEditEdycja->text();
    if(ui->lineEditEdycja==0)
        QMessageBox::information(this, "Edycja kienta", "Podaj ID klienta");
    else{
        temp=nr_telefonu.toInt();
        if(QString::number(temp)==nr_telefonu && nr_telefonu.size()!=9)
            QMessageBox::information(this,"Edycja klienta", "Nieprawidłowy numer telefonu"), isGood=false;
        if(!email.contains("@"))
            QMessageBox::information(this,"Edycja klienta", "Nieprawidłowy adres e-mail"), isGood=false;
        if(imie.size()!=0 && nazwisko.size()!=0 && nr_telefonu.size()!=0 && email.size()!=0 && isGood)
         {
             query->setQuery("SELECT * FROM klient WHERE id_klienta="+id);
             if(query->rowCount()!=0)
             {
                 query->setQuery("UPDATE klient SET imie='"+imie+"', nazwisko='"+nazwisko+"', nr_telefonu="+nr_telefonu+", e_mail='"
                 +email+"' WHERE id_klienta ="+id);
                 QMessageBox::information(this,"Edycja klienta", "Dokonano edycji klienta");
                 query->setQuery("SELECT id_klienta AS id, imie, nazwisko, nr_telefonu AS 'nr telefonu', e_mail AS 'e-mail' FROM klient WHERE id_klienta="+id);
                 ui->tableView->setModel(query);
             }
            else
            QMessageBox::information(this,"Edycja klienta", "Nie ma takiego klienta");
        }
    }
}

void okno_kasjer::on_pushButtonWybierzKlienta_clicked()
{
    QString id;
    QString imie, nazwisko, nr_telefonu, email;
    id=ui->lineEditEdycja->text();
    if (id.size()==0)
        QMessageBox::information(this, "Edycja", "Podaj ID klienta");
    else
    {
        query->setQuery("SELECT * FROM klient WHERE id_klienta="+id);
        if (query->rowCount()==0)
            QMessageBox::information(this, "Edycja", "Nie ma takiego klienta");
        else
        {
            imie = query->record(0).value(1).toString();
            nazwisko = query->record(0).value(2).toString();
            nr_telefonu = query->record(0).value(3).toString();
            email = query->record(0).value(4).toString();
            ui->lineEditDodajImie->setText(imie);
            ui->lineEditDodajNazwisko->setText(nazwisko);
            ui->lineEditDodajNr->setText(nr_telefonu);
            ui->lineEditDodajEmail->setText(email);
        }
    }
}

void okno_kasjer::on_pushButtonDodajRezerwacje_clicked()
{
    QString klient, film, temp2;
    int temp;
    klient=ui->lineEditIdKlienta->text();
    film=ui->lineEditIdSeansu->text();
    if(klient.size()==0 || film.size()==0)
        QMessageBox::information(this, "Dodawanie rezerwacji", "Wypełnij wszystkie pola");
    else
    {
        temp2 = seanseMiesiac()+" AND id_seansu="+film;
        query->setQuery(temp2);
        temp=query->rowCount();
        query->setQuery("SELECT * from klient WHERE id_klienta ="+klient);
        if (temp == 0 || query->rowCount()==0)
            QMessageBox::information(this, "Dodawanie rezerwacji", "Nie ma takiego seansu lub klienta");
        else
        {
            query->setQuery("INSERT INTO rezerwacja (id_klienta) VALUES ("+klient+")");
            dodawanie_biletow *dodawanieOkno = new dodawanie_biletow(film,klient, this);
            dodawanieOkno->exec();
        }
    }
}

QString okno_kasjer::seanseMiesiac()
{
    QDateTime date, enddate;
    QString string;
    enddate=ui->dateTimeEdit->dateTime();
    date=QDateTime::currentDateTime();
    string="SELECT id_seansu AS ID, tytul, czas_seansu AS 'czas seansu', dzwiek.wersja FROM seans JOIN film ON film.id_filmu=seans.id_filmu JOIN dzwiek ON dzwiek.id_dzwieku=seans.dzwiek WHERE czas_seansu >'"
                    +date.toString("yyyy-MM-dd hh:mm:ss")+"' AND czas_seansu <'"
                    +enddate.toString("yyyy-MM-dd hh:mm:ss")+"'";
    return string;
}

void okno_kasjer::on_pushButtonSeanse_clicked()
{
    query->setQuery(seanseMiesiac()+" ORDER BY czas_seansu DESC");
    ui->tableView_2->setModel(query);
}

void okno_kasjer::on_pushButtonPokazRezerwacje_clicked()
{
    QString idklienta;
    idklienta=ui->lineEditIdKlienta->text();
    if (idklienta.size()==0)
        QMessageBox::information(this, "Rezerwacje","Podaj numer klienta");
    else
    {
        query->setQuery("SELECT * from klient WHERE id_klienta="+idklienta);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Rezerwacje","Nie ma takiego klienta");
        else
        {
            query->setQuery("SELECT bilet.id_rezerwacji AS ID, tytul, czas_seansu AS 'czas seansu', COUNT(bilet.id_rezerwacji) AS ilosc, status_miejsca.opis FROM bilet "
                            "JOIN rezerwacja ON bilet.id_rezerwacji=rezerwacja.id_rezerwacji "
                            "JOIN seans ON bilet.id_seansu=seans.id_seansu "
                            "JOIN film ON seans.id_filmu=film.id_filmu "
                            "JOIN status_miejsca ON bilet.status_miejsca=status_miejsca.stan "
                            "WHERE rezerwacja.id_klienta="+idklienta+
                            " GROUP BY bilet.id_rezerwacji");
            ui->tableView_2->setModel(query);
        }
    }
}

void okno_kasjer::on_pushButtonUsunRez_clicked()
{
    QString idrezerwacji;
    idrezerwacji=ui->lineEditIdRezerwacji->text();
    if(idrezerwacji.size()==0)
        QMessageBox::information(this, "Usuwanie rezerwacji", "Podaj numer rezerwacji");
    else
    {
        query->setQuery("SELECT * FROM rezerwacja WHERE id_rezerwacji="+idrezerwacji);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Usuwanie rezerwacji", "Nie ma takiej rezerwacji");
        else
        {
            query->setQuery("UPDATE bilet SET id_rezerwacji=NULL, status_miejsca=1, rodzaj_biletu=NULL "
                            "WHERE id_rezerwacji="+idrezerwacji);
            query->setQuery("DELETE FROM rezerwacja WHERE id_rezerwacji="+idrezerwacji);
            QMessageBox::information(this, "Usuwanie rezerwacji", "Usunięto rezerwację");
        }
    }
}



void okno_kasjer::on_pushButtonZrealizuj_clicked()
{
    QString idrezerwacji;
    idrezerwacji=ui->lineEditIdRezerwacji->text();
    if(idrezerwacji.size()==0)
        QMessageBox::information(this, "Usuwanie rezerwacji", "Podaj numer rezerwacji");
    else
    {
        query->setQuery("SELECT * FROM rezerwacja WHERE id_rezerwacji="+idrezerwacji);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Usuwanie rezerwacji", "Nie ma takiej rezerwacji");
        else
        {
            query->setQuery("UPDATE bilet SET status_miejsca=3 "
                            "WHERE id_rezerwacji="+idrezerwacji);
            QMessageBox::information(this, "Usuwanie rezerwacji", "Zrealizowano rezerwację");
        }
    }
}

void okno_kasjer::on_pushButtonDodajBilety_clicked()
{
    QString idseansu;
    idseansu=ui->lineEditIdSeansu->text();
    if(idseansu.size()==0)
        QMessageBox::information(this, "Dodawanie biletów", "Podaj ID seansu");
    else
    {
        query->setQuery( seanseMiesiac()+" AND id_seansu="+idseansu);
        if(query->rowCount()==0)
            QMessageBox::information(this, "Dodawanie biletów", "Nie ma takiego seansu");
        else
        {
            dodawanie_biletow *dodawanieOkno = new dodawanie_biletow(idseansu,QString::number(0), this);
            dodawanieOkno->exec();
        }
    }


}

void okno_kasjer::on_tabWidget_currentChanged(int index)
{
    if(index==0){
       query->setQuery("");
       ui->tableView->setModel(query);
    }
}
