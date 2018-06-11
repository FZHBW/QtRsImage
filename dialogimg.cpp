#include "dialogimg.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE


Dialogimg::Dialogimg(RsImage &img0, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogimg)
{
    ui->setupUi(this);
    pimg0 = &img0;
    for(int i = 0; i<img0.get_Bands(); i++)
        ui->comboBox->addItem("Band"+QString::number(i, 10));
    int b = img0.get_Bands();
    M = new int[b];
    m = new int[b]; 
    img0.findMm(M, m);

}

Dialogimg::~Dialogimg()
{
    delete []M;
    delete []m;
    delete ui;
}

void Dialogimg::DrawDiagram0(int band)
{
    pimg0->cacudata(band);
}

void Dialogimg::on_pushButton_clicked()
{
    int b = ui->comboBox->currentIndex();
    DrawDiagram0(b);
    //![1]
        QBarSet *set = new QBarSet("Amount");
        for(int i = m[b]; i <M[b]; i++)
        {
            *set<<(pimg0->datasave[i]);
            pimg0->datasave[i]=0;
        }
    //![1]

    //![2]
        QBarSeries *series = new QBarSeries();
        series->setBarWidth(0.8);
        series->append(set);
    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Band"+QString::number(b,10));
        chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
        //QStringList categories;
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->setGridLineVisible(false);
       // axis->setLabelsVisible(false);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
    //![4]

    //![5]
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        //QChartView *chartView = new QChartView(chart);
        //chartView->setRenderHint(QPainter::Antialiasing);
    //![6]

        ui->widget->setChart(chart);

}









