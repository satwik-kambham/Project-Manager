#include "manager.h"
#include "ui_manager.h"
#include "addtask.h"
#include "confirmation.h"
#include <cstdlib>

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

QJsonObject Manager::retriveJSONinfo(){
    //retreiving information from JSON file
    QString allJSONinfo;
    QString basePath = "C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\.info\\";
    QFile file;
    file.setFileName(basePath+currentProject->text()+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    allJSONinfo = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(allJSONinfo.toUtf8());
    QJsonObject obj = document.object();
    return obj;
}

void Manager::addJSONinfo(QJsonObject jsonObject){
    QString basePath = "C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\.info\\";
    QFile file;
    file.setFileName(basePath+currentProject->text()+".json");
    file.open(QIODevice::WriteOnly);
    QJsonDocument jsonDoc(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();
}

void Manager::on_projectsList_itemClicked(QListWidgetItem *item)
{
    //setting current project
    currentProject = item;

    QJsonObject obj = retriveJSONinfo();

    ui->projectName->setText(obj.value(QString("Name")).toString()); //setting project name
    ui->projectDescription->setText(obj.value(QString("Description")).toString()); //setting project description
    ui->statusButton->setText(obj.value(QString("Status")).toString()); //setting status
    ui->Tag1->setText(obj.value(QString("Tags"))[0].toString()); //setting tag 1
    ui->Tag2->setText(obj.value(QString("Tags"))[1].toString()); //setting tag 2
    ui->Tag3->setText(obj.value(QString("Tags"))[2].toString()); //setting tag 3

    QListWidget* toDolist = ui->List;
    toDolist->clear();
    QJsonArray toDoItems = obj.value(QString("To do list")).toArray();
    foreach(QJsonValue toDoItem, toDoItems){
        new QListWidgetItem(toDoItem.toString(), toDolist);
    }
}



void Manager::on_toDoList_clicked()
{
    currentState = toDo;
    ui->markDoneOrNotDone->setText("Mark as done");

    //change ui->List to whatever is present in the JSON file
    QJsonObject obj = retriveJSONinfo();

    //adding toDoList items in the list
    QListWidget* toDolist = ui->List;
    toDolist->clear();
    QJsonArray toDoItems = obj.value(QString("To do list")).toArray();
    foreach(QJsonValue toDoItem, toDoItems){
        new QListWidgetItem(toDoItem.toString(), toDolist);
    }
}


void Manager::on_changelog_clicked()
{
    currentState = changelog;
    ui->markDoneOrNotDone->setText("Mark as not done");

    //change ui->List to whatever is present in the JSON file
    QJsonObject obj = retriveJSONinfo();

    //adding toDoList items in the list
    QListWidget* changelogList = ui->List;
    changelogList->clear();
    QJsonArray changelogItems = obj.value(QString("Changelog")).toArray();
    foreach(QJsonValue toDoItem, changelogItems){
        new QListWidgetItem(toDoItem.toString(), changelogList);
    }
}


void Manager::on_removeTask_clicked()
{
    confirmation* confirmation_window = new confirmation;
    confirmation_window->show();
    confirmation_window->exec();
    if (confirmation_window->confirmed){
        QJsonObject obj = retriveJSONinfo();
        QListWidgetItem* item = ui->List->takeItem(ui->List->currentRow());
        delete item;
        addJSONinfo(obj);
    }
    delete confirmation_window;
}



void Manager::on_addTask_clicked()
{
    addtask* addWindow = new addtask;
    this->hide();
    addWindow->show();
    addWindow->exec();
    ui->List->addItem(addWindow->taskInfo);
    QJsonObject obj = retriveJSONinfo();
    if (currentState == toDo){
        QJsonArray todolist = obj.value("To do list").toArray();
        todolist.append(addWindow->taskInfo);
        obj.insert("To do list", todolist);
    }else if (currentState == changelog){
        QJsonArray changeloglist = obj.value("Changelog").toArray();
        changeloglist.append(addWindow->taskInfo);
        obj.insert("Changelog", changeloglist);
    }
    addJSONinfo(obj);
    this->show();
    delete addWindow;
}


void Manager::on_markDoneOrNotDone_clicked()
{
    QJsonObject obj = retriveJSONinfo();
    QListWidgetItem* item = ui->List->currentItem();
    QJsonArray todolist = obj.value("To do list").toArray();
    QJsonArray changeloglist = obj.value("Changelog").toArray();
    if (currentState == toDo){
        todolist.removeAt(ui->List->currentRow());
        changeloglist.append(item->text());
    }else if (currentState == changelog){
        changeloglist.removeAt(ui->List->currentRow());
        todolist.append(item->text());
    }
    obj.insert("To do list", todolist);
    obj.insert("Changelog", changeloglist);
    delete item;
    addJSONinfo(obj);
}


void Manager::on_statusButton_clicked()
{
    QJsonObject obj = retriveJSONinfo();
    QString status = obj.value("Status").toString();

    if(status == "To do"){
        status = "On Going";
    }else if(status == "On Going"){
        status = "Done";
    }else if(status == "Done"){
        status = "To do";
    }else{
        status = "To do";
    }

    obj.insert("Status", status);
    ui->statusButton->setText(status);
    addJSONinfo(obj);
}


void Manager::on_openInIDE_clicked()
{
    QJsonObject obj = retriveJSONinfo();
    system(obj.value("IDE").toString().toStdString().c_str());
}


void Manager::on_runExe_clicked()
{
    QJsonObject obj = retriveJSONinfo();
    system(obj.value("Exe").toString().toStdString().c_str());
}


void Manager::on_openInGithub_clicked()
{
    QJsonObject obj = retriveJSONinfo();
    std::string a = "start chrome ";
    a += obj.value("Github").toString().toStdString();
    system(a.c_str());
}

