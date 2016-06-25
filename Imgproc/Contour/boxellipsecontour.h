#ifndef BOXELLIPSECONTOUR_H
#define BOXELLIPSECONTOUR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class BoxEllipseContour;
}

class BoxEllipseContour : public QWidget
{
    Q_OBJECT

public:
    explicit BoxEllipseContour(QWidget *parent = 0);
    explicit BoxEllipseContour(Mat img);
    ~BoxEllipseContour();

private slots:
    void on_resetButton_clicked();

    void on_autoScaleCheckBox_clicked(bool checked);

    void on_thresholdSlider_sliderMoved(int position);

private:
    Ui::BoxEllipseContour *ui;

    Mat originalImage;
    Mat image;
    int threshold;
    RNG rng;

private:
    void applyBoxEllipseContour(int thres);
};

#endif // BOXELLIPSECONTOUR_H
