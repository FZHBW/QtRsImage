#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QPainter>
#include <QImage>
#include"dialog.h"
//#include"dialogs.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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

void MainWindow::on_pushButton_2_clicked()
{
    QTableWidget *qtw = new QTableWidget;
    qtw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtw->setShowGrid(true);

    qtw->setRowCount(img.get_Bands());
    qtw->setColumnCount(2);
    qtw->setHorizontalHeaderLabels("HStrList");

    for(int i = 0; i < img.get_Bands(); i++)
    {
        qtw->setItem(i,0,new QTableWidgetItem("band"));
    }
    qtw->show();

}
