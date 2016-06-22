#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class CannyEdgeDetector;
}

class CannyEdgeDetector : public QWidget
{
    Q_OBJECT

public:
    explicit CannyEdgeDetector(QWidget *parent = 0);
    explicit CannyEdgeDetector(Mat img);
    ~CannyEdgeDetector();

private slots:
    void on_minThresSlider_sliderMoved(int position);

    void on_checkBox_clicked(bool checked);

    void on_resetButton_clicked();

private:
    Ui::CannyEdgeDetector *ui;
    int ksize;
    int minThres;
    int ratio;

    Mat originalImage;
    Mat image;
    Mat output;

private:
    void cannyEdgeDetect();

};

#endif // CANNYEDGEDETECTOR_H
