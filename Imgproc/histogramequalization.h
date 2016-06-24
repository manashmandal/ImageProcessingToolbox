#ifndef HISTOGRAMEQUALIZATION_H
#define HISTOGRAMEQUALIZATION_H

#include <QWidget>

#include "../imagehandler.h"

namespace Ui {
class HistogramEqualization;
}

class HistogramEqualization : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramEqualization(QWidget *parent = 0);
    explicit HistogramEqualization(Mat img);
    ~HistogramEqualization();

private slots:
    void on_toggleImage_clicked(bool checked);

    void on_autoScaleCheckBox_clicked(bool checked);

private:
    Ui::HistogramEqualization *ui;

    Mat originalImage;
    Mat originalHistogram;

    Mat image;
    Mat histogram;

private:
    Mat createHistogram(Mat &img);
    void equalizeHistogram();
};

#endif // HISTOGRAMEQUALIZATION_H
