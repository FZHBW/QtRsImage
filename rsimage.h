#ifndef RSIMAGE_H
#define RSIMAGE_H
#include<string>
#include<fstream>
#include<sstream>
#include<QString>
#include<QMainWindow>
#include<QTableWidget>
#include <QFileDialog>
#include <QTextCodec>

using namespace std;

enum rsdata{BSQ, BIP, BIL};
typedef unsigned char	DataType;

class RsImage
{
    bool open(const char* lpstrPath);

public:
    RsImage();
    ~RsImage();
    bool qOpen(QString fileName);
    bool qimMaker(int r, int g, int b, DataType *pt);
    int get_Bands(){return m_nBands;}
    int get_Lines(){return m_nLines;}
    int get_Samples(){return m_nSamples;}
    int get_Samples_4(){
        Samples_4 = (m_nSamples*8+31)/32*4;
        return Samples_4;
    }
    DataType*** get_m_pppData()const {return m_pppData;}
    void cacuAverage(double *p);
    void cacuVariance(double *pV, double *pA);
    void findMm(int *pM, int *pm);
    void cacudata(int bands);
    int datasave[256]{0};





protected:
    int m_nSamples = 0;
    int m_nLines = 0;
    int m_nBands = 0;
    int Samples_4 = 0;
    rsdata m_eInterleave;
    DataType*** m_pppData = NULL;
    bool ReadMetaData(const char* lpstrMetaFilePath);
    bool ReadImgData(const char* lpstrImgFilePath);
    bool InitBuffer(void);
    string m_nDataType;





public:


};

#endif // RSIMAGE_H
