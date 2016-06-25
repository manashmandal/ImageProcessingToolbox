#ifndef IMAGEMOMENT_H
#define IMAGEMOMENT_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class ImageMoment;
}

class ImageMoment : public QWidget
{
    Q_OBJECT

public:
    explicit ImageMoment(QWidget *parent = 0);
    explicit ImageMoment(Mat img);
    ~ImageMoment();

private slots:
    void on_resetButton_clicked();

    void on_thresholdSlider_sliderMoved(int position);

    void on_autoScaleCheckBox_clicked(bool checked);

private:
    Ui::ImageMoment *ui;

    Mat originalImage;
    int threshold;
    Mat image;
    RNG rng;
private:
    void applyMoment(int thres);
};

#endif // IMAGEMOMENT_H
