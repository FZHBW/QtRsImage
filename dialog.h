#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    bool gain_bands(int b);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int lines = 0;
    int samples = 0;
    int bands =0;
    QTableWidget *qtw;

};

#endif // DIALOG_H
