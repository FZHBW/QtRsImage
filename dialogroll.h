#ifndef DIALOGROLL_H
#define DIALOGROLL_H
#include<rsimage.h>
#include <QDialog>
#include <QPainter>

namespace Ui {
class DialogRoll;
}

class DialogRoll : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRoll(RsImage *img0, DataType *pqimgdata, QWidget *parent = 0);

    ~DialogRoll();

private slots:
    QPixmap get_qpmap();

private:
    Ui::DialogRoll *ui;
    RsImage *trimg;
    DataType *trpDataBuffer;



};

#endif // DIALOGROLL_H
