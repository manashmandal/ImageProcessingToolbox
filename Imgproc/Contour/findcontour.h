#ifndef FINDCONTOUR_H
#define FINDCONTOUR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class FindContour;
}

class FindContour : public QWidget
{
    Q_OBJECT

public:
    explicit FindContour(QWidget *parent = 0);
    explicit FindContour(Mat img);
    ~FindContour();

private slots:
    void on_resetButton_clicked();

    void on_autoScaleCheckBox_clicked(bool checked);

    void on_thresholdSlider_sliderMoved(int thres);

private:
    Ui::FindContour *ui;
    Mat originalImage;
    Mat image;
    int threshold;
    RNG rng;

private:
    void findContours(int threshold);

};

#endif // FINDCONTOUR_H
