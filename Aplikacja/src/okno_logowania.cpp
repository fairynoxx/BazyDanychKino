#include "okno_logowania.h"
#include "ui_okno_logowania.h"

okno_logowania::okno_logowania(QSqlDatabase &bazaa, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::okno_logowania),
    baza(bazaa)
{
    ui->setupUi(this);
}

okno_logowania::~okno_logowania()
{
    delete ui;
}

void okno_logowania::on_pushButtonZamknij_clicked()
{
    this->close();
}

void okno_logowania::on_pushButtonZaloguj_clicked()
{
    QString login, haslo;
    login = ui->lineEditLogin->text();
    haslo = ui->lineEditHaslo->text();
    login+="@bazydanychkino";
    baza.setUserName(login);
    baza.setPassword(haslo);
    if(baza.open())
    {
        QMessageBox::information(this, "Logowanie", "Zalogowano");
        this->close();
    }
    else
        QMessageBox::information(this,"Logowanie","Nieprawidłowa nazwa użykownika lub hasło");
}
