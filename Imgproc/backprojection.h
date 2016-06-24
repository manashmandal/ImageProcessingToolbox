#ifndef BACKPROJECTION_H
#define BACKPROJECTION_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class BackProjection;
}

class BackProjection : public QWidget
{
    Q_OBJECT

public:
    explicit BackProjection(Mat img);
    ~BackProjection();

private slots:
    void on_autoFitCheckBox_clicked(bool checked);

    void on_binSlider_sliderMoved(int bins);

    void on_resetButton_clicked();

private:
    Ui::BackProjection *ui;

    Mat originalImage;
    Mat originalHistogram;

    Mat backproj;
    Mat histogram;
    Mat hist;
    int bins;

    Mat hsv;
    Mat hue;

private:
    void histAndBackproject(int bins);
};

#endif // BACKPROJECTION_H
