#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QListWidget>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

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

private:
    Ui::Manager *ui;
    QDir directory;
};
#endif // MANAGER_H
