#pragma once
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QMainWindow>
#include "okno_logowania.h"
#include "okno_technik.h"
#include "okno_kasjer.h"
#include "okno_kierownik.h"
#include "okno_barman.h"
#include "okno_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class okno_manager;
class okno_kasjer;
class okno_technik;
class okno_kierownik;
class okno_barman;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;
private slots:
    void on_pushButtonLogowanie_clicked();

    void on_pushButtonZamknij_clicked();

    void on_pushButtonWyloguj_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *tableModel;
    QSqlQueryModel *query;
    okno_technik *tab_technik;
    okno_kasjer *tab_kasjer;
    okno_kierownik *tab_kierownik;
    okno_barman *tab_barman;
    okno_manager *tab_manager;
};

