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
//Functions:
    RsImage();
    ~RsImage();
    bool qOpen(QString fileName);
    bool qimMaker(int r, int g, int b, int a, DataType *pt);
    int get_Bands(){return m_nBands;}
    int get_Lines(){return m_nLines;}
    int get_Samples(){return m_nSamples;}
    int get_Samples_4()
    {
        Samples_4 = (m_nSamples*8+31)/32*4;
        return Samples_4;
    }
    DataType *** get_m_pppData() const {return m_pppData;}
    void cacuAverage(double *p);
    void cacuVariance(double *pV, double *pA);
    void findMm(int *pM, int *pm);
    void cacudata(int bands);
    DataType*** m_ppp_operate_Data = NULL;
    void GFilter();
    void EFilter();
    void FFilter();
    void SFilter();

//Arguments:
    int datasave[256]{0};






protected:

//Functions:
    bool ReadMetaData(const char* lpstrMetaFilePath);
    bool ReadImgData(const char* lpstrImgFilePath);
    bool InitBuffer(void);

//Arguments:
    int m_nSamples = 0;
    int m_nLines = 0;
    int m_nBands = 0;
    int Samples_4 = 0;
    rsdata m_eInterleave;
    DataType*** m_pppData = NULL;

    string m_nDataType = "";
    string metadata0;
    string kind_of_metadata;





public:




};

#endif // RSIMAGE_H
