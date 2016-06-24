#ifndef AFFINETRANSFORMATION_H
#define AFFINETRANSFORMATION_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class AffineTransformation;
}

class AffineTransformation : public QWidget
{
    Q_OBJECT

public:
    explicit AffineTransformation(QWidget *parent = 0);
    explicit AffineTransformation(Mat img);
    ~AffineTransformation();


private slots:
    void on_pointButton_clicked(bool checked);

    void on_angleSlider_sliderMoved(int position);

    void on_scaleSlider_sliderMoved(int position);

    void on_autoFitCheckBox_clicked(bool checked);

    void on_resetButton_clicked();

private:
    Ui::AffineTransformation *ui;

    //Center point
    Point center;

    Mat originalImage;
    Mat warpDst;

    float angle;
    float scale;

    //Points
    Point2f sourceTriangle[3];
    Point2f destinationTriangle[3];

    Mat rotation_mat;
    Mat warp_mat;

    Mat warp_rotate_dst;

private:
    void affineTransform(float angle, float scale);

};

#endif // AFFINETRANSFORMATION_H
