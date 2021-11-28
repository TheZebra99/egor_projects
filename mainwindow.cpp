#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!connOpen())
    {
        ui->label->setText("Failed to open the database");
    }
    else
    {
        ui->label->setText("Connected the database");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString Username, Password;
    Username=ui->lineEdit_Username->text();
    Password=ui->lineEdit_Password->text();
    if (!my_database.isOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connOpen();
    QSqlQuery query;
    query.prepare("SELECT * FROM employee_info WHERE username='"+Username+"' AND password='"+Password+"'");
    if (query.exec())
    {
        int count=0;
        while (query.next())
        {
            count++;
        }
        if (count==1)
        {
            ui->label->setText("Correct username and password!");
            connClose();
            this->hide(); // скроет текущее меню
            // создаем объект для нового окна
            EmployeeInfo employeeinfo;
            employeeinfo.setModal(true);
            employeeinfo.exec();

        }
        if (count >1)
            ui->label->setText("Duplicate username and password");
        if (count <1)
            ui->label->setText("Incorrect username or password!");
    }
}

bool MainWindow::connOpen()
{
    // создание объекта базы данных (sqlite)
    my_database = QSqlDatabase::addDatabase("QSQLITE");
    // вставить здесь расположение файла базы данных
    my_database.setDatabaseName("E:/Sqlite/employee.db");

    if (!my_database.open())
    {
        qDebug()<<("Failed to open the database");
        return false;
    }
    else
    {
        qDebug()<<("Connected the database");
        return true;
    }
}

void MainWindow::connClose()
{
    my_database.close();
    my_database.removeDatabase(QSqlDatabase::defaultConnection);
}
