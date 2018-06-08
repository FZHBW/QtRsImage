#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rsimage.h"
#include <QMainWindow>
#include<QTableWidget>
#include<QScrollArea>
#include<QMessageBox>
#include<QImage>
#include<dialogimgs.h>
#include<dialogimg.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //DataType ***get_mpppData(DataType ***pt);
    ~MainWindow();

private slots:

    void on_actionqoiwe_triggered();

    void on_actionInfo_I_triggered();

    void on_actionSwitch_W_triggered();

    void on_actionDiaGram_D_triggered();

private:
    Ui::MainWindow *ui;

protected:
    RsImage img;
    QTableWidget *qtw;
    QScrollArea *scrollArea;
    DataType* pDataBuffer;
    bool showimginfo();
    bool openRsimg();
    QImage *qim = NULL;
    int SR = 0;
    int SG = 1;
    int SB = 2;
    void Drawimg();





};

#endif // MAINWINDOW_H
