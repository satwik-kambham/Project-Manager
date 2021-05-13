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

void Manager::on_projectsList_itemClicked(QListWidgetItem *item)
{
    //retreiving information from JSON file
    QString allJSONinfo;
    QString basePath = "C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\.info\\";
    QFile file;
    file.setFileName(basePath+item->text()+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    allJSONinfo = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(allJSONinfo.toUtf8());
    QJsonObject obj = document.object();

    ui->projectName->setText(obj.value(QString("Name")).toString()); //setting project name
    ui->projectDescription->setText(obj.value(QString("Description")).toString()); //setting project description
    ui->statusButton->setText(obj.value(QString("Status")).toString()); //setting status
    ui->Tag1->setText(obj.value(QString("Tags"))[0].toString()); //setting tag 1
    ui->Tag2->setText(obj.value(QString("Tags"))[1].toString()); //setting tag 2
    ui->Tag3->setText(obj.value(QString("Tags"))[2].toString()); //setting tag 3


}

