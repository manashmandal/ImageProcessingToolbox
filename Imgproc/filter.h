#ifndef FILTER_H
#define FILTER_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QComboBox>
#include <QDebug>

#include "../imagehandler.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

enum FilterType {FILTER_HOMOGENEOUS = 0, FILTER_GAUSSIAN = 1, FILTER_MEDIAN = 2, FILTER_BILATERAL = 3};

namespace Ui {
class Filter;
}

class Filter : public QWidget
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = 0);
    explicit Filter(Mat img);
    ~Filter();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

    void on_filterComboBox_currentIndexChanged(int index);

    void on_applyButton_clicked();

    void on_valueSpinBox_valueChanged(int arg);

private:
    void applyFilter();

    void configureSpinBox();

private:
    Ui::Filter *ui;
    Mat originalImage;
    Mat image;
    FilterType currentFilter;
    Size ksize;
    int sigma;
};

#endif // FILTER_H
