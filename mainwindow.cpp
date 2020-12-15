#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    if (!connOpen())
    {
        ui->db_status_label->setText("Error while connecting with database");
    }
    else
    {
        ui->db_status_label->setText("Connected to database! :-)");
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_add_field_button_clicked()
{
    QString name = ui->f_name_lineEdit->text();
    QString area = ui->f_area_lineEdit->text();

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Ooops", "Filed 'Name' is missing!");
        }
    else if (category.isEmpty())
        {
            QMessageBox::information(this, "Ooops", "Filed 'Category' is missing!");
        }
    else
    {
        connOpen();
        QSqlQuery query;
        query.prepare("INSERT into fields (name, category) VALUES ('"+name+"','"+category+"')");
        if(query.exec())
       {
           QMessageBox::information(this, tr("Yay!"), tr("Your recipie is added"));
       }
       else
       {
            QMessageBox::critical(this, tr("Oops"), query.lastError().text());
       }
       connClose();
    }
}

void MainWindow::on_add_description_button_clicked()
{
    QString name = ui->recipe_name_lineEdit->text();
    QString power = ui->recipe_difficulty_lineEdit->text();

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Oops", "What is the name of your recipe?");
        }
    else if (difficulty.isEmpty())
        {
            QMessageBox::information(this, "Oops", "How difficult is your recipe?");
        }
    else
    {
    connOpen();
    QSqlQuery query;
        query.prepare("INSERT into recipes (name, difficulty) VALUES ('"+name+"','"+difficulty+"')");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Yay"), tr("Recipie is added!"));
        }
        else
        {
            QMessageBox::critical(this, tr("Oops"), query.lastError().text());
        }
    connClose();

    }
    loadTractorListToComboBox();
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
   if (index==2)
   {
       loadRecpies1ToEditList();
       loadRecpies2ToEditList();
   };
   if (index==3) loadRecipesListToComboBox();

}



void MainWindow::on_f_edit_delete_button_clicked()
{
    QString name = ui->f_edit_name_lineEdit->text();
    connOpen();
    QSqlQuery query;
        query.prepare("DELETE FROM fields where name='"+name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Yay"), tr("You just deleted a recipe!"));
            loadRecipeToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Oops"), query.lastError().text());
        }
    connClose();

}

void MainWindow::on_f_edit_save_button_clicked()
{
    QString base_name = ui->f_name_list->currentText();
    QString name = ui->f_edit_name_lineEdit->text();
    QString f_area = ui->f_edit_area_lineEdit->text();
    QString desc = ui->f_edit_desc_lineEdit->text();

    connOpen();
    QSqlQuery query;
        query.prepare("UPDATE fields SET name = '"+name+"',area = '"+f_area+"', description = '"+desc+"' where name='"+base_name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo zmieniono"));
            loadFieldsToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}
