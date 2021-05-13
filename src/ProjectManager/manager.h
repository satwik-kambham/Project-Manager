#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QDir>

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
    void on_statusButton_clicked();

private:
    Ui::Manager *ui;
    QDir directory;
};
#endif // MANAGER_H
