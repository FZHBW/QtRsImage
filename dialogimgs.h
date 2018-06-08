#ifndef DIALOGIMGS_H
#define DIALOGIMGS_H

#include <QDialog>
#include"rsimage.h"

namespace Ui {
class DialogImgS;
}

class DialogImgS : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImgS(RsImage &img0, QWidget *parent = 0);
    bool get_bandselct(int &r, int &g, int &b);
    ~DialogImgS();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogImgS *ui;

};

#endif // DIALOGIMGS_H
