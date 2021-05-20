#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QListWidget>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

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
    void on_removeTask_clicked();
    void on_addTask_clicked();
    void on_markDoneOrNotDone_clicked();
    void on_statusButton_clicked();
    void on_openInIDE_clicked();
    void on_runExe_clicked();
    void on_openInGithub_clicked();

private:
    Ui::Manager *ui;
    QDir directory;
    state currentState = toDo;
    QListWidgetItem* currentProject;
    QListWidgetItem* selectedTask;

    QJsonObject retriveJSONinfo();
    void addJSONinfo(QJsonObject jsonObject);
};
#endif // MANAGER_H
