#ifndef LAPLACIANEDGEDETECTOR_H
#define LAPLACIANEDGEDETECTOR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class LaplacianEdgeDetector;
}

class LaplacianEdgeDetector : public QWidget
{
    Q_OBJECT

public:
    explicit LaplacianEdgeDetector(QWidget *parent = 0);
    explicit LaplacianEdgeDetector(Mat img);
    ~LaplacianEdgeDetector();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

private:
    Ui::LaplacianEdgeDetector *ui;
    Mat image;

    int ksize;
    int ddepth;
    int delta;
    int scale;

private:
    void detectEdge();
};

#endif // LAPLACIANEDGEDETECTOR_H
