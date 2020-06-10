#pragma once
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <vector>

namespace Ui {
class dodawanie_biletow;
}

class dodawanie_biletow : public QDialog
{
    Q_OBJECT

public:
    explicit dodawanie_biletow(QString id_seansu, QString id_klienta, QWidget *parent = nullptr);
    ~dodawanie_biletow();

private slots:

    void on_comboBoxRzad_textActivated(const QString &arg1);

    void on_pushButtonDodajBilet_clicked();

    void on_pushButtonZakoncz_clicked();

    void on_pushButtonUsun_clicked();

private:
    Ui::dodawanie_biletow *ui;
    QSqlQueryModel *query;
    QSqlDatabase &bd;
    QString idklient;
    QString idrezerwacji;
    QString idseansu;
    QSqlQuery query2;
    void aktualizujRzad();
    void aktualizujKolumne(QString);
    bool isRes=true;
};

