#ifndef DIALOGIMG_H
#define DIALOGIMG_H

#include <QDialog>
#include<rsimage.h>
#include "dialogimg.h"
#include "ui_dialogimg.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Dialogimg;
}

class Dialogimg : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogimg(RsImage &img0, QWidget *parent = 0);
    ~Dialogimg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialogimg *ui;
    void DrawDiagram0(int band);
    int *M;
    int *m;
    RsImage *pimg0 = NULL;
    int *dataget;


};

#endif // DIALOGIMG_H
