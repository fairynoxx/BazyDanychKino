#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "mainwindow.h"
#include <QSqlQuery>

namespace Ui {
class okno_kierownik;
}

class okno_kierownik : public QWidget
{
    Q_OBJECT

public:
    explicit okno_kierownik(QWidget *parent = nullptr);
    ~okno_kierownik();
    QSqlDatabase &baza;

private slots:
    void on_pushButtonDodajSeans_clicked();

    void on_pushButtonWyszukaj_clicked();

    void on_pushButtonUsunSeans_clicked();

    void on_pushButtonWyczysc_clicked();

    void on_pushButtonWyczysc2_clicked();

    void on_pushButtonWyczysc3_clicked();

    void on_checkBoxIdSeansu_stateChanged(int arg1);

    void on_checkBoxCzas_stateChanged(int arg1);

    void on_checkBoxTytul_stateChanged(int arg1);

    void on_pushButtonSprawdz_clicked();

    void on_pushButtonSprawdz2_clicked();

    void on_pushButtonWyczysc4_clicked();

    void on_pushButtonZnajdz_clicked();

    void on_pushButtonEdytuj_clicked();

    void on_pushButtonWyczysc5_clicked();

private:
    Ui::okno_kierownik *ui;
    QSqlQueryModel *query;
    QString seanseMiesiac();
    QSqlQuery query2;
    void wyczyscPola1();
    void wyczyscPola2();
    void wyczyscPola3();
    void wyczyscPola4();
    void dodajMiejsce(QString idseansu);
    void usunMiejsce(QString idseansu);

};


