#include "addtask.h"
#include "ui_addtask.h"

addtask::addtask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addtask)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint); // making program borderless
}

addtask::~addtask()
{
    delete ui;
}

void addtask::on_buttonBox_accepted()
{
    taskInfo = ui->plainTextEdit->toPlainText();
}


void addtask::on_buttonBox_rejected()
{
    taskInfo = "";
}

