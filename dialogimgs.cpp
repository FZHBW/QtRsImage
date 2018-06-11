#include "dialogimgs.h"
#include "ui_dialogimgs.h"

DialogImgS::DialogImgS(RsImage &img0, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImgS)
{
    ui->setupUi(this);


//![1]
    int b = img0.get_Bands();
    for(int i = 0; i<b; i++)
    {
      ui->comboBox->addItem("Band"+QString::number(i, 10));
      ui->comboBox_2->addItem("Band"+QString::number(i, 10));
      ui->comboBox_3->addItem("Band"+QString::number(i, 10));
    }
//![1]

}

DialogImgS::~DialogImgS()
{
    delete ui;
}

bool DialogImgS::get_bandselct(int &r, int &g, int &b)
{
    r = ui->comboBox->currentIndex();
    g = ui->comboBox_2->currentIndex();
    b = ui->comboBox_3->currentIndex();
    return true;
}

void DialogImgS::on_buttonBox_accepted()
{

}
