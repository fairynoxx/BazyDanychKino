#pragma once

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <string>
#include <QMessageBox>
#include "mainwindow.h"
#include "dodawanie_biletow.h"

namespace Ui {
class okno_kasjer;
}

class okno_kasjer : public QWidget
{
    Q_OBJECT

public:
    explicit okno_kasjer(QWidget *parent = nullptr);
    ~okno_kasjer();
    QSqlDatabase &baza;

private slots:
    void on_pushButtonDodajKlienta_clicked();

    void on_pushButtonZnajdzKlienta_clicked();

    void on_pushButtonWyczysc_clicked();

    void on_pushButtonEdytuj_clicked();

    void on_pushButtonWybierzKlienta_clicked();

    void on_pushButtonDodajRezerwacje_clicked();


    void on_pushButtonSeanse_clicked();

    void on_pushButtonPokazRezerwacje_clicked();

    void on_pushButtonUsunRez_clicked();

    void on_pushButtonZrealizuj_clicked();

    void on_pushButtonDodajBilety_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    QSqlQueryModel *query;
    Ui::okno_kasjer *ui;
    QString seanseMiesiac();
};
