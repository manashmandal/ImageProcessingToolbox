#ifndef IMAGEBLENDER_H
#define IMAGEBLENDER_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QDebug>
#include <QString>
#include "../imagehandler.h"
#include <QMessageBox>

using namespace std;
using namespace cv;

namespace Ui {
class ImageBlender;
}

class ImageBlender : public QWidget
{
    Q_OBJECT

public:
    explicit ImageBlender(QWidget *parent = 0);
    ImageBlender(Mat src1, Mat src2);
    ~ImageBlender();




private slots:
    void on_alphaSlider_sliderMoved(int position);

private:
    Ui::ImageBlender *ui;
    Mat blendedImage;
    Mat source1;
    Mat source2;
};

#endif // IMAGEBLENDER_H
