#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Manager; }
QT_END_NAMESPACE

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    Manager(QWidget *parent = nullptr);
    ~Manager();

private:
    Ui::Manager *ui;
};
#endif // MANAGER_H
