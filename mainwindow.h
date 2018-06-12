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

    void on_slider_move_rotating(int i);

    void on_slider_move_transparent(int i);

    void on_slider_move_scroll(int i);

    void on_actionEnhance_E_triggered();

    void on_actionRotate_R_triggered();

    void on_actionTransparent_T_triggered();

    void on_actionGFilter_G_triggered();

    void on_actionEDFilter_D_triggered();

    void on_actionFCFilter_F_triggered();

    void on_actionSFilter_S_triggered();

    void on_actionScroll_L_triggered();

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
    QImage* imgRZ;
    QComboBox *cb1,*cb2;


//Arguments:
    int SR = 0;
    int SG = 1;
    int SB = 2;
    int SA = 255;
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
    void setlabel(QImage qi);
    void setpDataBuffer();
    //void Drawimg(DataType *pDataBuffer0, int transp);



};

#endif // MAINWINDOW_H
