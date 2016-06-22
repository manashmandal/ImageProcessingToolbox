#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include <QWidget>
#include "../imagehandler.h"

namespace Ui {
class Thresholding;
}

class Thresholding : public QWidget
{
    Q_OBJECT

public:
    explicit Thresholding(QWidget *parent = 0);
    explicit Thresholding(Mat img);
    ~Thresholding();

private slots:
    void on_scaleCheckBox_clicked(bool checked);

    void on_thresholdValueSlider_sliderMoved(int position);

    void on_thresholdTypeComboBox_currentIndexChanged(int index);

private:
    Ui::Thresholding *ui;
    Mat originalImage;
    Mat image;
    int thresValue;
};

#endif // THRESHOLDING_H
