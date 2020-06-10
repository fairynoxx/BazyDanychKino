#ifndef OKNO_MANAGER_H
#define OKNO_MANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class okno_manager;
}

class okno_manager : public QWidget
{
    Q_OBJECT

public:
    explicit okno_manager(QWidget *parent = nullptr);
    ~okno_manager();
     QSqlDatabase &baza;

private slots:
     void on_pushButtonZnajdz_clicked();

     void on_pushButtonWyczysc_clicked();

     void on_pushButtonUsun_clicked();

     void on_pushButtonZatrudnij_clicked();

     void on_pushButtonWyczysc2_clicked();

     void on_comboBoxPlanStanowisko_textActivated(const QString &arg1);

     void on_pushButtonWyczysc3_clicked();

     void on_pushButtonDodaj_clicked();

     void on_pushButtonPokaz_clicked();

     void on_pushButtonPlanUsun_clicked();

     void on_pushButtonWyczysc4_clicked();

     void on_pushButtonOblicz_clicked();

     void on_pushButtonObliczWszystkich_clicked();

private:
    Ui::okno_manager *ui;
    QSqlQueryModel *query;
    QSqlQuery query2;
    void aktualizujPracownika(QComboBox *, QComboBox *);
    void aktualizujDzien();
};

#endif // OKNO_MANAGER_H
