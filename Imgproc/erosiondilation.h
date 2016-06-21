#ifndef EROSIONDILATION_H
#define EROSIONDILATION_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSlider>
#include <QRadioButton>
#include <QComboBox>
#include <QDebug>

#include "../imagehandler.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace cv;

namespace Ui {
class ErosionDilation;
}

class ErosionDilation : public QWidget
{
    Q_OBJECT

public:
    explicit ErosionDilation(QWidget *parent = 0);
    explicit ErosionDilation(Mat img);
    ~ErosionDilation();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

    void on_kernelSizeSlider_sliderMoved(int position);

    void on_structuringElementComboBox_currentIndexChanged(const QString &structType);

    void on_dilateRadioButton_clicked(bool checked);

    void on_erodeRadioButton_clicked(bool checked);

private:
    Ui::ErosionDilation *ui;

    Mat image;
    Mat originalImage;
    Mat element;

    int ksize;

private:
    void erodeDilate();
    void setStructureType(QString structType);

};

#endif // EROSIONDILATION_H
