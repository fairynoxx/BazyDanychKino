#pragma once
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "mainwindow.h"

namespace Ui {
class okno_technik;
}

class okno_technik : public QWidget
{
    Q_OBJECT

public:
    explicit okno_technik(QWidget *parent = nullptr);
    ~okno_technik();
    QSqlDatabase &baza;

private slots:
    void on_pushButtonZnajdzFilm_clicked();

    void on_pushButtonZnajdzSeans_clicked();

private:
    Ui::okno_technik *ui;

    QSqlQueryModel *query;
    QString sprawdzDaty();
};

