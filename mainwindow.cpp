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

    ui->actionFCFilter_F->setEnabled(false);
    ui->actionGFilter_G->setEnabled(false);
    ui->actionRotate_R->setEnabled(false);
    ui->actionScroll_L->setEnabled(false);
    ui->actionEDFilter_D->setEnabled(false);
    ui->actionSFilter_S->setEnabled(false);
    ui->actionTransparent_T->setEnabled(false);

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
        ui->actionFCFilter_F->setEnabled(true);
        ui->actionGFilter_G->setEnabled(true);
        ui->actionRotate_R->setEnabled(true);
        ui->actionScroll_L->setEnabled(true);
        ui->actionEDFilter_D->setEnabled(true);
        ui->actionSFilter_S->setEnabled(true);
        ui->actionTransparent_T->setEnabled(true);
        b = img.get_Bands();
        movepdata = img.get_m_pppData();
        a = new double[b]{0};
        v = new double[b]{0};
        M = new int[b]{0};
        m = new int[b]{0};

        img.cacuAverage(a);
        img.cacuVariance(v,a);
        img.findMm(M,m);

        ui->centralWidget->setMouseTracking(true);
        this->setMouseTracking(true);

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
    connect(ql, SIGNAL(valueChanged(int)), this,SLOT(on_slider_move_zoomimg(int)));
}

void MainWindow::on_actionTransparent_T_triggered()
{
    slidermaker("%", 0, 100);
    ql->setValue(100);
    connect(ql, SIGNAL(valueChanged(int)), this, SLOT(on_slider_move_transparent(int)));
}

void MainWindow::on_actionEnhance_E_triggered()
{

}

void MainWindow::on_actionRotate_R_triggered()
{
    slidermaker("°",-180,180);
    connect(ql, SIGNAL(valueChanged(int)), this,SLOT(on_slider_move_rotating(int)));
}

void MainWindow::on_actionScroll_L_triggered()
{
    slidermaker("lines",0, img.get_Lines()-1);
    ql->setValue(0);
    connect(ql, SIGNAL(valueChanged(int)), this,SLOT(on_slider_move_scroll(int)));
}

void MainWindow::on_slider_move_zoomimg(int i)
{
    QImage *Zqim = new QImage;
    *Zqim = qim->scaled(img.get_Samples_4()*i/100, img.get_Lines()*i/100, Qt::KeepAspectRatio);
    ui->label->resize(img.get_Samples_4()*i/100, img.get_Lines()*i/100);
    ui->label->setPixmap(QPixmap::fromImage(*Zqim));
}

void MainWindow::on_slider_move_rotating(int i)
{
    QImage* imgRotate = new QImage;
    QMatrix matrix;
    matrix.rotate(i);
    *imgRotate = qim->transformed(matrix);
    ui->label->resize(imgRotate->size());
    ui->label->setPixmap(QPixmap::fromImage(*imgRotate));
}

void MainWindow::on_slider_move_transparent(int i)
{
    SA = i*255/100;
    img.qimMaker( SR, SG, SB, SA, pDataBuffer);
    qim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
    QPixmap pixmap = QPixmap::fromImage(*qim);
    ui->label->setPixmap(pixmap);

}

void MainWindow::on_slider_move_scroll(int m)
{
   int i = 0;
   DataType ***sham_pppdata;
   sham_pppdata = img.get_m_pppData();
   for(int j = 0; j <= m; j++)
   {
       for(int k = 0;  k<img.get_Samples_4(); k++)
       {
           pDataBuffer[i++]=sham_pppdata[SR][j][k];
           pDataBuffer[i++]=sham_pppdata[SG][j][k];
           pDataBuffer[i++]=sham_pppdata[SB][j][k];
           pDataBuffer[i++]=0;
           }
      }
   for(int j = m+1; j < img.get_Lines(); j++)
   {
       for(int k = 0;  k<img.get_Samples_4(); k++)
       {
           pDataBuffer[i++]=sham_pppdata[SR][j][k];
           pDataBuffer[i++]=sham_pppdata[SG][j][k];
           pDataBuffer[i++]=sham_pppdata[SB][j][k];
           pDataBuffer[i++]=255;
        }
   }

    qim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
    QPixmap pixmap = QPixmap::fromImage(*qim);
    ui->label->setPixmap(pixmap);
}

void MainWindow::on_actionGFilter_G_triggered()
{
   img.GFilter();
   setpDataBuffer();
   QImage *GFqim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
   setlabel(*GFqim);
}

void MainWindow::on_actionEDFilter_D_triggered()
{
    img.EFilter();
    setpDataBuffer();
    QImage *EFqim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
    setlabel(*EFqim);
}

void MainWindow::on_actionFCFilter_F_triggered()
{
    img.FFilter();
    setpDataBuffer();
    QImage *FFqim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
    setlabel(*FFqim);
}

void MainWindow::on_actionSFilter_S_triggered()
{
    img.SFilter();
    setpDataBuffer();
    QImage *SFqim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
    setlabel(*SFqim);
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
    int i;
//![setLayout]

//![setSignalSlot]
    connect(qp, SIGNAL(valueChanged(int)), ql, SLOT(setValue(int)));
    connect(ql, SIGNAL(valueChanged(int)), qp, SLOT(setValue(int)));


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
        pDataBuffer = new DataType [img.get_Lines()*img.get_Samples_4()*4]{0};
        Drawimg();
        return true;
    }

}

void MainWindow::Drawimg()
{

    img.qimMaker( SR, SG, SB, SA, pDataBuffer);
    qim = new QImage(pDataBuffer,img.get_Samples_4(),img.get_Lines(), QImage::Format_RGBA8888);
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
    scrollArea->setMouseTracking(true);
    //ui->label->setMouseTracking(true);

    setCentralWidget(scrollArea);
    setlabel(*qim);
}

void MainWindow::setlabel(QImage qi)
{
    QPixmap pixmap = QPixmap::fromImage(qi);
    ui->label->setPixmap(pixmap);
}

void MainWindow::Enhance()
{

}

void MainWindow::setpDataBuffer()
{
    int i = 0, k = 0;
    int line = img.get_Lines();
    int sam = img. get_Samples();
   for(int j = 0; j < line; j++)
   {
       for(k = 0;  k< sam; k++)
       {
           pDataBuffer[i++]=img.m_ppp_operate_Data[SR][j][k];
           pDataBuffer[i++]=img.m_ppp_operate_Data[SG][j][k];
           pDataBuffer[i++]=img.m_ppp_operate_Data[SB][j][k];
           pDataBuffer[i++]=SA;
        }
   }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString info("%1, %2, %3");
    if(event->pos().x() < img.get_Samples_4() && event->pos().y() < img.get_Lines())
    {
        info = info.arg(movepdata[SR][event->pos().y()][event->pos().x()])
                .arg(movepdata[SG][event->pos().y()][event->pos().x()])
                .arg(movepdata[SB][event->pos().y()][event->pos().x()]);
        QToolTip::showText(mapToGlobal(event->pos()),info);
    }


}

