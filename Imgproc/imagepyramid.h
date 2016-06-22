#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class ImagePyramid;
}

class ImagePyramid : public QWidget
{
    Q_OBJECT

public:
    explicit ImagePyramid(QWidget *parent = 0);
    explicit ImagePyramid(Mat img);
    ~ImagePyramid();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

    void on_pyrUpButton_clicked();

    void on_pyrDownButton_clicked();

    void on_resetButton_clicked();


private:
    Ui::ImagePyramid *ui;
    Mat image;
    Mat originalImage;
    Mat dst;
    int pyrUpCount;
};

#endif // IMAGEPYRAMID_H
