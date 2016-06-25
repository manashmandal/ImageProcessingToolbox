#ifndef BOXCIRCLECONTOUR_H
#define BOXCIRCLECONTOUR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class BoxCircleContour;
}

class BoxCircleContour : public QWidget
{
    Q_OBJECT

public:
    explicit BoxCircleContour(QWidget *parent = 0);
    explicit BoxCircleContour(Mat img);
    ~BoxCircleContour();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

    void on_resetButton_clicked();

    void on_thresholdSlider_sliderMoved(int position);

private:
    Ui::BoxCircleContour *ui;

    Mat originalImage;
    Mat image;
    int threshold;
    RNG rng;

private:
    void applyBoundingBoxAndCircleContour(int thres);

};

#endif // BOXCIRCLECONTOUR_H
