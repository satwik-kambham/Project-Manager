#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);

    // setting the background image
    QPixmap backgroundImg("C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\UIBackground.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImg);
    this->setPalette(palette);

    setFixedSize(size()); // making program non resizable
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint); // making program borderless

    // adding files in the project list
    QListWidget *projectsList = ui->projectsList;
    directory = QDir("C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects");
    QStringList folders = directory.entryList();
    folders.pop_front();
    folders.pop_front();
    foreach(QString folderName, folders){
        new QListWidgetItem(folderName, projectsList);
    }
}

Manager::~Manager()
{
    delete ui;
}


void Manager::on_quitButton_clicked()
{
    QApplication::quit();
}


void Manager::on_statusButton_clicked()
{

}

