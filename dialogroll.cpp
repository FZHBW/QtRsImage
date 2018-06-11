#include "dialogroll.h"
#include "ui_dialogroll.h"

DialogRoll::DialogRoll(RsImage *img0, DataType *pqimgdata, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRoll)
{
    ui->setupUi(this);
    trimg = img0;
    int b = trimg->get_Bands();
    for(int i = 0; i<b; i++)
    {
      ui->comboBox->addItem("Band "+QString::number(i+1, 10));
      ui->comboBox_2->addItem("Band "+QString::number(i+1, 10));
      ui->comboBox_3->addItem("Band "+QString::number(i+1, 10));
    }
    ui->horizontalSlider->setRange(0,trimg->get_Samples_4());

    ui->spinBox_2->setRange(0,trimg->get_Samples_4());
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox_2, SLOT(setValue(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    trpDataBuffer = pqimgdata;

}

DialogRoll::~DialogRoll()
{
    delete ui;
}


QPixmap DialogRoll::get_qpmap()
{
    //trpDataBuffer
}

















