#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    HEIGHT = 9;
    WIDTH = 9;
    MINES = 10;
    exec();
}

void Dialog::accept(){
    HEIGHT = ui->lineEdit->text().toInt() < 9 ? 9 : ui->lineEdit->text().toInt();
    WIDTH = ui->lineEdit_2->text().toInt() < 9 ? 9 : ui->lineEdit_2->text().toInt();
    MINES = ui->lineEdit_3->text().toInt() < 10 ? 10 : ui->lineEdit_3->text().toInt();
    close();
}

Dialog::~Dialog()
{
    delete ui;
}
