#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rsimage.h"
//#include"dialog.h"
#include <QMainWindow>
#include<QTableWidget>
//#include"dialogi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionqoiwe_triggered();

    void on_actionInfo_I_triggered();

private:
    Ui::MainWindow *ui;
    RsImage img;
    QTableWidget *qtw;

};

#endif // MAINWINDOW_H
