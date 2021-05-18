#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QListWidget>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

enum state{toDo, changelog, screenshot};

QT_BEGIN_NAMESPACE
namespace Ui { class Manager; }
QT_END_NAMESPACE

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    Manager(QWidget *parent = nullptr);
    ~Manager();

private slots:
    void on_quitButton_clicked();
    void on_projectsList_itemClicked(QListWidgetItem *item);

    void on_toDoList_clicked();

    void on_changelog_clicked();

private:
    Ui::Manager *ui;
    QDir directory;
    state currentState = toDo;
    QListWidgetItem* currentProject;

    QJsonObject retriveJSONinfo();
};
#endif // MANAGER_H
