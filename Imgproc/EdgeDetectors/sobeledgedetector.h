#ifndef SOBELEDGEDETECTOR_H
#define SOBELEDGEDETECTOR_H

#include <QWidget>

#include "../../imagehandler.h"

namespace Ui {
class SobelEdgeDetector;
}

class SobelEdgeDetector : public QWidget
{
    Q_OBJECT

public:
    explicit SobelEdgeDetector(QWidget *parent = 0);
    explicit SobelEdgeDetector(Mat img);
    ~SobelEdgeDetector();

private slots:
    void on_autoScaleCheckBox_clicked(bool checked);

private:
    Ui::SobelEdgeDetector *ui;

    Mat image;

    //Config
    int ddepth;
    int ksize;
    int delta;
    int scale;

private:
    void detectEdge();

};

#endif // SOBELEDGEDETECTOR_H
