#ifndef HOUGHTRANSFORMATION_H
#define HOUGHTRANSFORMATION_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class HoughTransformation;
}

class HoughTransformation : public QWidget
{
    Q_OBJECT

public:
    explicit HoughTransformation(QWidget *parent = 0);
    explicit HoughTransformation(Mat img);
    ~HoughTransformation();

private slots:
    void on_thresholdSlider_sliderMoved(int position);

    void on_resetButton_clicked();

    void on_autoScaleCheckBox_clicked(bool checked);

    void on_transformComboBox_currentIndexChanged(int index);

private:
    Ui::HoughTransformation *ui;
    int threshold;
    Mat originalImage;
    Mat image;

private:
    void houghTransform();
};

#endif // HOUGHTRANSFORMATION_H
