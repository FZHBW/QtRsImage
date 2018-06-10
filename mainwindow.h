#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"rsimage.h"
#include <QMainWindow>
#include<QWidget>
#include<QTableWidget>
#include<QScrollArea>
#include<QMessageBox>
#include<QImage>
#include<QSpinBox>
#include<QSlider>
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
    ~MainWindow();

private slots:

    void on_actionqoiwe_triggered();

    void on_actionInfo_I_triggered();

    void on_actionSwitch_W_triggered();

    void on_actionDiaGram_D_triggered();

    void on_actionZoom_O_triggered();

    void on_slider_move_zoomimg(int i);

    void on_actionEnhance_E_triggered();

private:
    Ui::MainWindow *ui;

protected:
//Widgets
    RsImage img;
    QTableWidget *qtw;
    QWidget *qw;
    QScrollArea *scrollArea ;
    DataType* pDataBuffer;
    QImage *qim;
    QSlider *ql;
    QSpinBox *qp;
    QHBoxLayout *slayout;
    QDialog *Qd;


//Arguments:
    int SR = 0;
    int SG = 1;
    int SB = 2;
    int zoomv = 1;
    int *M;
    int *m;
    double *a;
    double *v;
    int mid;
    int b = 0;

//Functions
    bool showimginfo();
    bool openRsimg();
    void Drawimg();
    void slidermaker(QString, int min, int max);
    void Enhance();



};

#endif // MAINWINDOW_H
