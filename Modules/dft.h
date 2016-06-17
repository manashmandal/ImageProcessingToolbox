#ifndef DFT_H
#define DFT_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
#include <iostream>

#include "../imagehandler.h"

using namespace cv;
using namespace std;

namespace Ui {
class DFT;
}

class DFT : public QWidget
{
    Q_OBJECT

public:
    explicit DFT(QWidget *parent = 0);
    explicit DFT(Mat img);
    ~DFT();

private slots:
    void on_openDFTImage_clicked();

private:
    Ui::DFT *ui;
    Mat originalImage;
    Mat image;
    Mat dftImage;
    void discreteFourierTransform(Mat &img);
};

#endif // DFT_H
