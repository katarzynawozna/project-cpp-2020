
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb =QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("Desktop/Studia/Project_CPP/mydb.recipes");

        if (!mydb.open())
        {
            qDebug()<<("Connection failed");
            return false;
        }
        else
        {
             qDebug()<<("Connected successfully");
             return true;
        }
    }
    void loadRecipeListToComboBox()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from recipes");
        query->exec();
        modal->setQuery(*query);
        ui->wr_r_name_comboBox->setModel(modal);

        connClose();

        qDebug()<<(modal->rowCount());


    }
    void loadFieldsToEditList()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from recipes");
        query->exec();

        modal->setQuery(*query);
        ui->f_name_list->setModel(modal);

        connClose();

        qDebug()<<(modal->rowCount());
    }
    void loadRecipesToEditList()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from recipes");
        query->exec();
        modal->setQuery(*query);
        ui->t_name_list->setModel(modal);
        connClose();

        qDebug()<<(modal->rowCount());
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_add_recipe_button_clicked();

    void on_add_description_button_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_r_edit_delete_button_clicked();

    void on_r_edit_save_button_clicked();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
