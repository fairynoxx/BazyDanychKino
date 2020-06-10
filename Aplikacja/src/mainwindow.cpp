#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo("D:/OneDrive/studia/BD/bd/logo.png");
    ui->labelLogo->setPixmap(logo);
    ui->labelLogo->setScaledContents(true);
    ui->label->setPixmap(logo);
    ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonLogowanie_clicked()
{
    if(db.isOpen())
        QMessageBox::information(this,"Logowanie","Najpierw należy się wylogować");
    else{
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("bazydanychkino.mysql.database.azure.com");
        db.setDatabaseName("kino");
        okno_logowania oknoLogowania(db);
        oknoLogowania.setModal(true);
        oknoLogowania.exec();
        if(db.isOpen()){
        if(db.userName().contains("kasjer"))
        {
            tab_kasjer = new okno_kasjer(this);
            ui->horizontalLayout_2->removeWidget(ui->label);
            ui->label->hide();
            ui->horizontalLayout_2->insertWidget(0,tab_kasjer);
        }
        else if(db.userName().contains("technikaw"))
        {
            tab_technik=new okno_technik(this);
            ui->horizontalLayout_2->removeWidget(ui->label);
            ui->label->hide();ui->horizontalLayout_2->insertWidget(0,tab_technik);
        }
        else if(db.userName().contains("kierownik"))
        {
            tab_kierownik = new okno_kierownik(this);
            ui->horizontalLayout_2->removeWidget(ui->label);
            ui->label->hide();
            ui->horizontalLayout_2->insertWidget(0,tab_kierownik);
        }
        else if(db.userName().contains("barman"))
        {
            tab_barman = new okno_barman(this);
            ui->horizontalLayout_2->removeWidget(ui->label);
            ui->label->hide();
            ui->horizontalLayout_2->insertWidget(0,tab_barman);
        }
        else if(db.userName().contains("manager"))
        {
            tab_manager = new okno_manager(this);
            ui->horizontalLayout_2->removeWidget(ui->label);
            ui->label->hide();
            ui->horizontalLayout_2->insertWidget(0,tab_manager);
        }
        }
    }
}

void MainWindow::on_pushButtonZamknij_clicked()
{
    this->close();
}


void MainWindow::on_pushButtonWyloguj_clicked()
{
    if(db.userName().contains("technik"))
        tab_technik->close();
    else if(db.userName().contains("kasjer"))
        tab_kasjer->close();
    else if(db.userName().contains("kierownik"))
        tab_kierownik->close();
    else if(db.userName().contains("barman"))
        tab_barman->close();
    else if(db.userName().contains("manager"))
        tab_manager->close();
    db.close();
    ui->horizontalLayout_2->insertWidget(0,ui->label);
    ui->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label->show();
}
