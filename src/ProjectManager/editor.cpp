#include "editor.h"
#include "ui_editor.h"
#include <QFileDialog>
#include <cstdlib>

editor::editor(QListWidgetItem* _currentProject, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editor),
    currentProject(_currentProject)
{
    ui->setupUi(this);
    setFixedSize(size()); // making program non resizable
    setWindowFlags(Qt::FramelessWindowHint); // making program borderless

    if (currentProject == nullptr){
        ui->titleLabel->setText("Create new project");
    }else{
        ui->titleLabel->setText("Edit Project");
        QJsonObject obj = retriveJSONinfo();
        ui->projectName->setPlainText(obj.value("Name").toString());
        ui->projectDescription->setPlainText(obj.value("Description").toString());
        ui->Tag1->setPlainText(obj.value("Tags").toArray()[0].toString());
        ui->Tag2->setPlainText(obj.value("Tags").toArray()[1].toString());
        ui->Tag3->setPlainText(obj.value("Tags").toArray()[2].toString());
        ui->exePath->setPlainText(obj.value("Exe").toString());
        ui->githubLink->setPlainText(obj.value("Github").toString());
    }
}

editor::~editor()
{
    delete ui;
}

void editor::on_chooseExe_clicked()
{
    QString exeFilePath = QFileDialog::getOpenFileName(this, "Select executable", QString(), QString("Executables (*.exe)"));
    ui->exePath->setPlainText(exeFilePath);
}


void editor::on_buttonBox_accepted()
{
    if (currentProject == nullptr){
        QString str = "mkdir \"C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\" + ui->projectName->toPlainText() + "\"";
        system(str.toStdString().c_str());
        str = "echo {} > \"C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\.info\\" + ui->projectName->toPlainText() + ".json \"";
        system(str.toStdString().c_str());
        currentProject = new QListWidgetItem(ui->projectName->toPlainText());
        addJSONinfo(createJSONobject());
    }else{
        addJSONinfo(createJSONobject());
    }
}

QJsonObject editor::createJSONobject(){
    QJsonObject obj = retriveJSONinfo();
    obj.insert("Name", ui->projectName->toPlainText());
    obj.insert("Description", ui->projectDescription->toPlainText());
    obj.insert("Tags", QJsonArray({ui->Tag1->toPlainText(), ui->Tag2->toPlainText(), ui->Tag3->toPlainText()}));
    obj.insert("Github", ui->githubLink->toPlainText());
    obj.insert("Exe", ui->exePath->toPlainText());
    obj.insert("IDE", "code");
    obj.insert("Status", "To do");
    return obj;
}

QJsonObject editor::retriveJSONinfo(){
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

void editor::addJSONinfo(QJsonObject jsonObject){
    QString basePath = "C:\\Users\\satwi\\Desktop\\Projects\\Project Manager\\Projects\\.info\\";
    QFile file;
    file.setFileName(basePath+currentProject->text()+".json");
    file.open(QIODevice::WriteOnly);
    QJsonDocument jsonDoc(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();
}
