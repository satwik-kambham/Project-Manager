#include "confirmation.h"
#include "ui_confirmation.h"

confirmation::confirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmation)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint); // making program borderless
}

confirmation::~confirmation()
{
    delete ui;
}

void confirmation::on_buttonBox_accepted()
{
    confirmed = true;
}

