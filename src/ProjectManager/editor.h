#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>

namespace Ui {
class editor;
}

class editor : public QDialog
{
    Q_OBJECT

public:
    explicit editor(QListWidgetItem* _currentProject = nullptr ,QWidget *parent = nullptr);
    ~editor();

private slots:
    void on_chooseExe_clicked();
    void on_buttonBox_accepted();

private:
    Ui::editor *ui;
    QListWidgetItem* currentProject;

    QJsonObject retriveJSONinfo();
    void addJSONinfo(QJsonObject jsonObject);
    QJsonObject createJSONobject();
};

#endif // EDITOR_H
