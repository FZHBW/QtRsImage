#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QPainter>
#include <QImage>
#include <vector>
#include<QTableWidget>

//Creat&Distruct:
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionInfo_I->setEnabled(false);
    ui->actionZoom_O->setEnabled(false);
    ui->actionDiaGram_D->setEnabled(false);
    ui->actionEnhance_E->setEnabled(false);
    ui->actionSwitch_W->setEnabled(false);
}

MainWindow::~MainWindow()
{ 
    delete ui;
}


//SLOT Function
void MainWindow::on_actionqoiwe_triggered()
{
    if(openRsimg())
    {
        ui->actionInfo_I->setEnabled(true);
        ui->actionZoom_O->setEnabled(true);
        ui->actionDiaGram_D->setEnabled(true);
        ui->actionEnhance_E->setEnabled(true);
        ui->actionSwitch_W->setEnabled(true);
        b = img.get_Bands();
        a = new double[b]{0};
        v = new double[b]{0};
        M = new int[b]{0};
        m = new int[b]{0};

        img.cacuAverage(a);
        img.cacuVariance(v,a);
        img.findMm(M,m);
    }
}

void MainWindow::on_actionInfo_I_triggered()
{
    showimginfo();
}

void MainWindow::on_actionSwitch_W_triggered()
{
    DialogImgS *dimg = new DialogImgS(img);
    if(dimg->exec() == QDialog::Accepted)
    {
        dimg->get_bandselct(SR, SG, SB);
    }
    Drawimg();

}

void MainWindow::on_actionDiaGram_D_triggered()
{
    Dialogimg dimg(img);
    dimg.exec();
}

void MainWindow::on_actionZoom_O_triggered()
{
    slidermaker("%",1,200);
}

void MainWindow::on_slider_move_zoomimg(int i)
{
    QImage *Zqim = new QImage;
    *Zqim = qim->scaled(img.get_Samples_4()*i/100, img.get_Lines()*i/100, Qt::KeepAspectRatio);
    ui->label->resize(img.get_Samples_4()*i/100, img.get_Lines()*i/100);
    ui->label->setPixmap(QPixmap::fromImage(*Zqim));
}

void MainWindow::on_actionEnhance_E_triggered()
{

}

//Motivation Function
void MainWindow::slidermaker(QString qst,int min, int max)
{
    Qd = new QDialog(this);
    ql = new QSlider(Qt::Horizontal);
    qp = new QSpinBox;
    mid = (min+max)/2;

//![setQSlider]
    ql->setRange(min,max);
    ql->setTickInterval(5);
    ql->setTickPosition(QSlider::TicksAbove);
    ql->setValue(mid);
    ql->setFixedWidth(260);
//![setQSlider]

//![setQSpinBox]
    qp->setRange(min,max);
    qp->setSuffix(qst);
    qp->setValue(mid);
//![setQSpinBox]

//![setLayout]
    slayout = new QHBoxLayout(Qd);
    slayout->addStretch();
    slayout->addWidget(qp);
    slayout->addWidget(ql);
    slayout->addStretch();
//![setLayout]

//![setSignalSlot]
    connect(qp, SIGNAL(valueChanged(int)), ql, SLOT(setValue(int)));
    connect(ql, SIGNAL(valueChanged(int)), qp, SLOT(setValue(int)));
    connect(qp, SIGNAL(valueChanged(int)), this,SLOT(on_slider_move_zoomimg(int)));
//![setSignalSlot]

//![setQWidget]
    Qd->setLayout(slayout);
//![setQWidget]

    Qd->show();
}

bool MainWindow::showimginfo()
{
    if(img.get_m_pppData() == NULL)
    {
        QMessageBox::warning(this, "RsImage Editor Error",
                             "No basic data");

        return false;
    }
    else
    {
        qtw = new QTableWidget();
        qtw-> setMinimumSize(627, 200);
        qtw-> setMaximumSize(627, 100000);
        qtw->setWindowModality(Qt::ApplicationModal);

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

        return true;
    }
}

bool MainWindow::openRsimg()
{
    if(!img.qOpen(QFileDialog::getOpenFileName(this, tr("Open File") ,"", "img files (*.img)")))
    {
        QMessageBox::warning(this, "RsImage Editor Error",
                             "Open file failed.");

        return false;
    }
    else
    {
        Drawimg();
        return true;
    }

}

void MainWindow::Drawimg()
{
    pDataBuffer = new DataType [img.get_Lines()*img.get_Samples_4()*3]{0};
    img.qimMaker( SR, SG, SB,pDataBuffer);
    qim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGB888);
    scrollArea = new QScrollArea;
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);

    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
    ui->label->resize(img.get_Samples_4(),img.get_Lines());

    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(ui->label);
    scrollArea->setVisible(true);

    setCentralWidget(scrollArea);
    QPixmap pixmap = QPixmap::fromImage(*qim);
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(pixmap);
}

void MainWindow::Enhance()
{
    int n;
}








