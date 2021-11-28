#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include "mainwindow.h"
#include <QMessageBox>

EmployeeInfo::EmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);
    MainWindow connection;
    if (!connection.connOpen())
    {
        ui->label_second_status->setText("Failed to open the database");
    }
    else
    {
        ui->label_second_status->setText("Connected...");
    }
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_pushButton_clicked()
{
    QString Employee_id, Name, Surname, Age;
    MainWindow connection;
    Employee_id=ui->lineEdit_Employee_id->text();
    Name=ui->lineEdit_Name->text();
    Surname=ui->lineEdit_Surname->text();
    Age=ui->lineEdit_Age->text();
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();
    QSqlQuery query;
    query.prepare("INSERT INTO employee_info (employee_id, name, surname, age) VALUES ('"+Employee_id+"','"+Name+"','"+Surname+"','"+Age+"')");
    if (query.exec())
    {
        QMessageBox::information(this, tr("Save"), tr("Saved"));
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}


void EmployeeInfo::on_pushButton_update_clicked()
{
    QString Employee_id, Name, Surname, Age;
    MainWindow connection;
    Employee_id=ui->lineEdit_Employee_id->text();
    Name=ui->lineEdit_Name->text();
    Surname=ui->lineEdit_Surname->text();
    Age=ui->lineEdit_Age->text();
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();
    QSqlQuery query;
    query.prepare("UPDATE employee_info SET employee_id='"+Employee_id+"', name='"+Name+"', surname='"+Surname+"', age='"+Age+"' where employee_id='"+Employee_id+"'");
    if (query.exec())
    {
        QMessageBox::information(this, tr("Edit"), tr("Updated"));
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}


void EmployeeInfo::on_pushButton_update_delete_clicked()
{
    QString Employee_id, Name, Surname, Age;
    MainWindow connection;
    Employee_id=ui->lineEdit_Employee_id->text();
    // для удаление нужно ввести только номер строки (primary key)
   //Name=ui->lineEdit_Name->text();
    //Surname=ui->lineEdit_Surname->text();
    //Age=ui->lineEdit_Age->text();
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();
    QSqlQuery query;
    query.prepare("DELETE FROM employee_info WHERE employee_id='"+Employee_id+"'");
    if (query.exec())
    {
        QMessageBox::information(this, tr("Delete"), tr("Deleted"));
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}


void EmployeeInfo::on_pushButton_load_clicked()
{
    MainWindow connection;
    QSqlQueryModel * modal = new QSqlQueryModel;
    connection.connOpen();
    QSqlQuery *query = new QSqlQuery(connection.getDB());
    query->prepare("SELECT * FROM employee_info");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    connection.connClose();
    qDebug() << (modal->rowCount());

}

