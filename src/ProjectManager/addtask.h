#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>

namespace Ui {
class addtask;
}

class addtask : public QDialog
{
    Q_OBJECT

public:
    explicit addtask(QWidget *parent = nullptr);
    ~addtask();

    QString taskInfo;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::addtask *ui;
};

#endif // ADDTASK_H
