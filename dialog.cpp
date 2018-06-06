#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qtw = new QTableWidget;
    qtw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtw->setShowGrid(true);

    qtw->setRowCount(2);
    qtw->setColumnCount(6);

    for(int i = 0; i < bands; i++)
    {
        qtw->setItem(i,0,new QTableWidgetItem("band"));
    }
    qtw->show();
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::gain_bands(int b)
{
    bands = b;
}
