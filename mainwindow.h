#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rsimage.h"
#include"dialog.h"
#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    RsImage img;
    Dialog *dia;

};

#endif // MAINWINDOW_H
