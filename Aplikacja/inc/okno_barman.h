#ifndef OKNO_BARMAN_H
#define OKNO_BARMAN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "mainwindow.h"

namespace Ui {
class okno_barman;
}

class okno_barman : public QWidget
{
    Q_OBJECT

public:
    explicit okno_barman(QWidget *parent = nullptr);
    QSqlDatabase &baza;
    QSqlQueryModel *query;
    QSqlQuery query2;
    ~okno_barman();

private slots:
    void on_pushButtonUtworz_clicked();

    void on_pushButtonDodajProdukt_clicked();

    void on_pushButtonWyczysc_clicked();

    void on_pushButtonAnuluj_clicked();

    void on_pushButtonZakoncz_clicked();

private:
    Ui::okno_barman *ui;
};

#endif // OKNO_BARMAN_H
