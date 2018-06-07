#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QPainter>
#include <QImage>
#include <vector>
#include<QTableWidget>
//#include"dialog.h"
//#include"dialogs.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    //delete qtw;
    delete ui;
}

void MainWindow::on_actionqoiwe_triggered()
{
    DataType* pDataBuffer;
    img.qOpen(QFileDialog::getOpenFileName(this, tr("Open File") ,"", "img files (*.img)"));
    pDataBuffer = new DataType [img.get_Lines()*img.get_Samples_4()*3]{0};
    img.qimMaker(pDataBuffer);
    QImage Qimg(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGB888);


    int with = ui->label->width();
    int height = ui->label->height();
    QPixmap pixmap = QPixmap::fromImage(Qimg);
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(fitpixmap);
}

void MainWindow::on_actionInfo_I_triggered()
{
    qtw = new QTableWidget();
    int b = img.get_Bands();
    double a[b]{0};
    double v[b]{0};
    int M[b]{0};
    int m[b]{0};
    img.cacuAverage(a);
    img.cacuVariance(v,a);
    img.findMm(M,m);

    qtw-> setMinimumSize(627, 270);
    qtw-> setMaximumSize(627, 100000);

    qtw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtw->setShowGrid(true);

    qtw->setRowCount(img.get_Bands()+1);
    qtw->setColumnCount(5);
    qtw->verticalHeader()->setVisible(false);
    qtw->horizontalHeader()->setVisible(false);

    qtw->setItem(0,1,new QTableWidgetItem("Averange"));
    qtw->setItem(0,2,new QTableWidgetItem("Variance"));
    qtw->setItem(0,3,new QTableWidgetItem("Maximum"));
    qtw->setItem(0,4,new QTableWidgetItem("Minimum"));

    for(int i = 1; i <= b; i++)
    {
        qtw->setItem(i,0,new QTableWidgetItem("Band"+QString::number(i, 10)));
        qtw->setItem(i,1,new QTableWidgetItem(QString::number( a[i-1],'g', 10)));
        qtw->setItem(i,2,new QTableWidgetItem(QString::number( v[i-1],'g', 10)));
        qtw->setItem(i,3,new QTableWidgetItem(QString::number( M[i-1],'g', 10)));
        qtw->setItem(i,4,new QTableWidgetItem(QString::number( m[i-1],'g', 10)));
    }


    qtw->show();


}
