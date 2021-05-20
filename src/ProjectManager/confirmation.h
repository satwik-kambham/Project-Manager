#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QDialog>

namespace Ui {
class confirmation;
}

class confirmation : public QDialog
{
    Q_OBJECT

public:
    explicit confirmation(QWidget *parent = nullptr);
    ~confirmation();

    bool confirmed = false;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::confirmation *ui;
};

#endif // CONFIRMATION_H
