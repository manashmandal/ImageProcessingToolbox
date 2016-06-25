#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class ConvexHull;
}

class ConvexHull : public QWidget
{
    Q_OBJECT

public:
    explicit ConvexHull(QWidget *parent = 0);
    explicit ConvexHull(Mat img);
    ~ConvexHull();

private slots:
    void on_resetButton_clicked();

    void on_thresholdSlider_sliderMoved(int position);

    void on_checkBox_clicked(bool checked);

private:
    Ui::ConvexHull *ui;
    Mat originalImage;
    Mat image;
    int threshold;
    RNG rng;

private:
    void findConvexHull(int thres);
};

#endif // CONVEXHULL_H
