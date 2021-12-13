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

    query->prepare("SELECT employee_id FROM employee_info");

    QSqlQuery *query2 = new QSqlQuery(connection.getDB());

    query2->prepare("SELECT * FROM employee_info");

    query->exec();
    query2->exec();
    modal->setQuery(*query); // через model передаем запросы sql в виджеты
    ui->listView->setModel(modal);
    ui->comboBox->setModel(modal);
    modal->setQuery(*query2);
    ui->tableView->setModel(modal);

    connection.connClose();
    qDebug() << (modal->rowCount());

}


void EmployeeInfo::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString name1=ui->comboBox->currentText(); //

    MainWindow connection;
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();

    QSqlQuery query;
    query.prepare("SELECT * FROM employee_info WHERE name='"+name1+"'");

    if (query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_Employee_id->setText(query.value(0).toString());
            ui->lineEdit_Name->setText(query.value(1).toString());
            ui->lineEdit_Surname->setText(query.value(2).toString());
            ui->lineEdit_Age->setText(query.value(3).toString());
        }
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }


}


void EmployeeInfo::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();

    MainWindow connection;
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();

    QSqlQuery query;
    query.prepare("SELECT * FROM employee_info WHERE employee_id='"+value+"'or name='"+value+"' or surname='"+value+"' or age='"+value+"'");

    if (query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_Employee_id->setText(query.value(0).toString());
            ui->lineEdit_Name->setText(query.value(1).toString());
            ui->lineEdit_Surname->setText(query.value(2).toString());
            ui->lineEdit_Age->setText(query.value(3).toString());
        }
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}


void EmployeeInfo::on_listView_activated(const QModelIndex &index)
{
    QString value=ui->listView->model()->data(index).toString();

    MainWindow connection;
    if (!connection.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    connection.connOpen();

    QSqlQuery query;
    query.prepare("SELECT * FROM employee_info WHERE employee_id='"+value+"'");

    if (query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_Employee_id->setText(query.value(0).toString());
            ui->lineEdit_Name->setText(query.value(1).toString());
            ui->lineEdit_Surname->setText(query.value(2).toString());
            ui->lineEdit_Age->setText(query.value(3).toString());
        }
        connection.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

