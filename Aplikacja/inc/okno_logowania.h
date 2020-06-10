#pragma once
#include <QDialog>
#include <QSqlDatabase>
#include <string>
#include <QMessageBox>

namespace Ui {
class okno_logowania;
}

class okno_logowania : public QDialog
{
    Q_OBJECT

public:
    explicit okno_logowania(QSqlDatabase &bazaa, QDialog *parent = nullptr);
    ~okno_logowania();

private slots:

    void on_pushButtonZamknij_clicked();

    void on_pushButtonZaloguj_clicked();

private:
    Ui::okno_logowania *ui;
    QSqlDatabase &baza;
};
