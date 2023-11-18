#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    int HEIGHT;
    int WIDTH;
    int MINES;
    ~Dialog();
public slots:
    void accept();
    //void reject();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
