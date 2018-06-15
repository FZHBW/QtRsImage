#include "rsimage.h"


RsImage::RsImage()
{
    m_pppData = NULL;
}

RsImage::~RsImage()
{
    delete []m_pppData;
}

bool RsImage::open(const char* lpstrPath)
{
    //lpstrPath = filepath;
    if ("" == lpstrPath)
        return false;

    // 1. Read Meta Data
    string		strMetaFilePath = lpstrPath;//输入文件位置
    int		pos = strMetaFilePath.rfind('.');//找到文件名的后缀
    if (pos >= 0)
    {
        strMetaFilePath = strMetaFilePath.substr(0, pos);
    }
    strMetaFilePath.append(".hdr");//改变后缀使程序找到hdr文件以读取基本数据

    if (!ReadMetaData(strMetaFilePath.c_str()))//文件路径不对时给予反馈
    {
        //cerr << "Read Meta Data Failed." << endl;
        return false;
    }

    // 2. Initialize Buffer
    if (!InitBuffer())//申请的内存过大或因其他原因失败时给予反馈
    {
        //cerr << "Initialize Buffer Failed." << endl;
        return false;
    }

    // 3. Read File
    if (!ReadImgData(lpstrPath))//读取图像内容失败后给予反馈
    {
        //cerr << "Read Image Data Failed." << endl;
        return false;
    }

    return true;
}

bool RsImage::ReadMetaData(const char* lpstrMetaFilePath)//读取准备信息
{
    ifstream    ifs;
    string      strLine;
    string      strSubTxt;
    stringstream    ss;
    char   sBuff[260]{0};


    ifs.open(lpstrMetaFilePath,ios_base::in);
    if(!ifs.is_open())
    {
       return false;
    }

    ifs >> metadata0;

    while (!ifs.eof())   //直到文件结尾才会结束
    {
        ifs.getline(sBuff, 260);//将读取到的内容输入数组中准备读取
        strLine = sBuff;

        ss.clear();
        ss.str(strLine);    //"samples = 640"
        ss >> strSubTxt;

        //通过查找对应的字符串来确定行列数以及各个像素各波段的数据并将其赋予到各个变量中
        if (strSubTxt == "samples")
        {
            ss >> strSubTxt >> m_nSamples;
        }
        else if (strSubTxt == "lines")
        {
            ss >> strSubTxt >> m_nLines;
        }
        else if (strSubTxt == "bands")
        {
            ss >> strSubTxt >> m_nBands;
        }
        else if (strSubTxt == "interleave")//找到储存方式
        {
            ss >> strSubTxt >> strSubTxt;
            if (strSubTxt == "bsq")
            {
                m_eInterleave = BSQ;
                kind_of_metadata = "bsq";
            }
            else if (strSubTxt == "bip")
            {
                m_eInterleave = BIP;
                kind_of_metadata = "bip";
            }
            else if (strSubTxt == "bil")
            {
                m_eInterleave = BIL;
                kind_of_metadata = "bil";
            }
            else
            {
                // blank
            }
        }
        else if (strSubTxt == "data")
        {
            ss >> strSubTxt;
            if (strSubTxt == "type")
            {
                ss >> strSubTxt >> m_nDataType;
            }
        }
        else
        {
            // blank
        }
    }
    return true;
}

bool RsImage::ReadImgData(const char* lpstrImgFilePath)
{
    bool        bFlag = true;
    int         i, j;
    ifstream    ifs;
    int*        ptrBuff = NULL;
    ifs.open(lpstrImgFilePath, ios::binary);

    if (ifs.is_open())
    {
        switch (m_eInterleave)
        {
        case BSQ:
            for (i = 0; i<m_nBands && !ifs.eof(); i++)
            {
                for (j = 0; j<m_nLines && !ifs.eof(); j++)
                {
                    ifs.read((char*)m_pppData[i][j], sizeof(DataType)*m_nSamples);

                    //按波段读取，这种读取方式速度较快，可以直接一行一行的读取极大的提高的写入
                    //内存和提取的速度。
                }
            }
            // 文件未读完整
            if (i<m_nBands || j<m_nLines)
                bFlag = false;
            break;
        case BIL:
            for (i = 0; i<m_nLines && !ifs.eof(); i++)
            {
                for (j = 0; j<m_nBands && !ifs.eof(); j++)
                {
                    ifs.read((char*)m_pppData[j][i], sizeof(DataType)*m_nSamples);

                }
            }
            // 数据不完整
            if (i<m_nLines || j<m_nBands)
                bFlag = false;
            break;
        case BIP:
            ptrBuff = new int[m_nBands];
            if (ptrBuff == NULL)
                bFlag = false;

            for (i = 0; i<m_nSamples*m_nLines && !ifs.eof(); i++)
            {
                ifs.read((char*)ptrBuff, sizeof(DataType)*m_nBands);

                for (j = 0; j<m_nBands; j++)
                {
                    m_pppData[j][i / m_nLines][i%m_nLines] = ptrBuff[j];
                }
            }
            if (i<m_nSamples*m_nLines)
                bFlag = false;
            break;
        }

        //SAV();//调用计算平均值、方差的函数，对对象储存的内容进行分析
        ifs.close();//关闭文件
    }

    return bFlag;
}

bool RsImage::InitBuffer(void)
{
    int     i, j;

    m_pppData = new DataType**[m_nBands];
    m_ppp_operate_Data = new DataType**[m_nBands];
    if (m_pppData == NULL || m_ppp_operate_Data == NULL)  return false;//判断指针是否指向有效的地址

    for (i = 0; i<m_nBands; i++)//给指针指向对象赋初值0
    {
        m_pppData[i] = 0UL;
        m_ppp_operate_Data[i] = 0UL;
    }

    for (i = 0; i<m_nBands; ++i)
    {
        m_pppData[i] = new DataType*[m_nLines];
        m_ppp_operate_Data[i] = new DataType*[m_nLines];
        if (m_pppData[i] == NULL || m_ppp_operate_Data[i] == NULL)   return false;

        for (j = 0; j<m_nLines; ++j)//创建二级指针
        {
            m_pppData[i][j] = 0UL;
            m_ppp_operate_Data[i][j] = 0UL;
        }

        for (j = 0; j<m_nLines; ++j)
        {
            m_pppData[i][j] = new DataType[m_nSamples];//创建数组储存空间
            m_ppp_operate_Data[i][j] = new DataType[m_nSamples];
        }
    }

    return true;
}

bool RsImage::qOpen(QString fileName)
{
    string filepath;
    filepath = fileName.toStdString();
    if(open(filepath.c_str()))
        return true;
    else
        return false;
}

bool RsImage::qimMaker(int r, int g, int b, int a, DataType *pt)
{
     int i = 0, k = 0;
    for(int j = 0; j < m_nLines; j++)
    {
        for(k = 0;  k<m_nSamples; k++)
        {
            pt[i++]=m_pppData[r][j][k];
            pt[i++]=m_pppData[g][j][k];
            pt[i++]=m_pppData[b][j][k];
            pt[i++]=a;
            }
       }
    if(pt != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RsImage::cacuAverage(double *p)
{
    double sum = 0;
    double result = 0;
    for(int i = 0; i<m_nBands;i++)
    {
        for (int j = 0; j < m_nLines; j++)
        {
            for (int k = 0; k < m_nSamples; k++)
            {
                sum += m_pppData[i][j][k];
                p[i] = static_cast<double>(sum) / static_cast<double>(m_nLines*m_nSamples);
            }
        }
        sum =0;
    }
}

void RsImage::cacuVariance(double *pV, double *pA)
{
    double sum = 0;
        double result = 0;
        for(int i = 0; i < m_nBands; i++)
        {
            for (int j = 0; j < m_nLines; j++)
            {
                for (int k = 0; k < m_nSamples; k++)
                {
                    pV[i] += pow((static_cast<double>(m_pppData[i][j][k]) - pA[i]), 2)
                            / static_cast<double>(m_nLines*m_nSamples);
                }
            }//计算方差是直接调用各波段的平均数数据更快速地解决问题
        }
}

void RsImage::findMm(int *pM, int *pm)
{
    for (int j = 0; j < m_nBands; j++)
        {
            for (int i = 0; i < m_nLines; i++)//找最大
            {
                for (int f = 0; f < m_nSamples; f++)
                {
                    if (pM[j] < (int)m_pppData[j][i][f])
                        pM[j] = (int)m_pppData[j][i][f];
                }
            }
            pm[j] = pM[j];
            for (int i = 0; i < m_nLines; i++)//找最小
            {
                for (int f = 0; f < m_nSamples; f++)
                {
                    if (pm[j] >(int)m_pppData[j][i][f])
                        pm[j] = (int)m_pppData[j][i][f];
                }
            }
        }
}

void RsImage::cacudata(int bands)
{


    for (int j = 0; j < m_nLines; j++)
    {
        for (int k = 0; k < m_nSamples; k++)
        {
            datasave[m_pppData[bands][j][k]]++;//历遍数组并统计频率
        }
    }
}

void RsImage::GFilter()
{
    int core[25]{
                    1, 4,  7,  4,  1,
                    4, 16, 26, 16, 4,
                    7, 26, 41, 26, 7,
                    1, 4,  7,  4,  1,
                    4, 16, 26, 16, 4,
                   };
    double av = 0;

    for (int i = 0; i < m_nBands; i++)
        {
            for (int j = 2; j < m_nLines - 2; j++)
            {
                for (int k = 2; k < m_nSamples - 2; k++)
                {
                    av = 0;
                    for (int m = -2; m < 3; m++)
                    {
                        for (int n = -2; n < 3; n++)
                        {
                            av += ((int)m_pppData[i][j+m][k+n])*core[(m+2)*5+n+2];
                        }
                    }
                    m_ppp_operate_Data[i][j][k] = (DataType)(av/273);
                }
            }
        }
}

void RsImage::EFilter()
{
    int core[9]{
                    -1, -1,  0,
                    -1,  0,  1,
                     0,  1,  1,
               };
    double av = 0;

    for (int i = 0; i < m_nBands; i++)
        {
            for (int j = 2; j < m_nLines - 2; j++)
            {
                for (int k = 2; k < m_nSamples - 2; k++)
                {
                    av = 0;
                    for (int m = -1; m < 2; m++)
                    {
                        for (int n = -1; n < 2; n++)
                        {
                            av += ((int)m_pppData[i][j+m][k+n])*core[(m+1)*3+n+1];
                        }
                    }
                    m_ppp_operate_Data[i][j][k] = (DataType)(av);
                }
            }
        }
}

void RsImage::FFilter()
{
    int core[9]{
        2, 0, 0,
        0, -1, 0,
        0, 0, -1,
               };
    double av = 0;

    for (int i = 0; i < m_nBands; i++)
        {
            for (int j = 2; j < m_nLines - 2; j++)
            {
                for (int k = 2; k < m_nSamples - 2; k++)
                {
                    av = 0;
                    for (int m = -1; m < 2; m++)
                    {
                        for (int n = -1; n < 2; n++)
                        {
                            av += ((int)m_pppData[i][j+m][k+n])*core[(m+1)*3+n+1];
                        }
                    }
                    m_ppp_operate_Data[i][j][k] = (DataType)(av+125);
                }
            }
        }
}

void RsImage::SFilter()
{
    int core[9]{
                    -1,-1,-1,
                    -1,9,-1,
                    -1,-1,- 1
                   };
    double av = 0;

    for (int i = 0; i < m_nBands; i++)
        {
            for (int j = 1; j < m_nLines - 1; j++)
            {
                for (int k = 1; k < m_nSamples - 1; k++)
                {
                    av = 0;
                    for (int m = -1; m < 2; m++)
                    {
                        for (int n = -1; n < 2; n++)
                        {
                            av += ((int)m_pppData[i][j+m][k+n])*core[(m+1)*3+n+1];
                        }
                    }
                    m_ppp_operate_Data[i][j][k] = (DataType)(av);
                }
            }
        }
}
