#ifndef CONTRASTBRIGHTNESS_H
#define CONTRASTBRIGHTNESS_H

#include <QWidget>
#include <QScrollArea>
#include <QSlider>
#include <QLabel>
#include <QDebug>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../imagehandler.h"

using namespace cv;

namespace Ui {
class ContrastBrightness;
}

class ContrastBrightness : public QWidget
{
    Q_OBJECT

public:
    explicit ContrastBrightness(QWidget *parent = 0);
    ContrastBrightness(Mat image);
    ~ContrastBrightness();

private slots:
    void on_alphaSlider_sliderMoved(int position);

    void on_autoScaleCheckBox_clicked(bool checked);

    void on_betaSlider_sliderMoved(int position);

private:
    Ui::ContrastBrightness *ui;
    Mat image;
    Mat originalImage;

    //alpha and beta
    double alpha;
    double beta;
};

#endif // CONTRASTBRIGHTNESS_H
