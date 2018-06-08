#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rsimage.h"
#include <QMainWindow>
#include<QTableWidget>
#include<QScrollArea>
#include<QMessageBox>
#include<QImage>

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




};

#endif // MAINWINDOW_H
