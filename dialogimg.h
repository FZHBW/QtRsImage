#ifndef DIALOGIMG_H
#define DIALOGIMG_H

#include <QDialog>
#include<rsimage.h>

namespace Ui {
class Dialogimg;
}

class Dialogimg : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogimg(RsImage &img0, QWidget *parent = 0);
    ~Dialogimg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialogimg *ui;
    void DrawDiagram0(int band);
    int *M;
    int *m;
    int *data;
    RsImage *pimg0 = NULL;

};

#endif // DIALOGIMG_H
