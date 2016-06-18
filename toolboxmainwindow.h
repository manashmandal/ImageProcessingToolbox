#ifndef TOOLBOXMAINWINDOW_H
#define TOOLBOXMAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QFileDialog>
#include <QResizeEvent>
#include <QSplitter>
#include <QDebug>
#include <QSize>

#include "imagehandler.h"
#include "Modules/imageblender.h"
#include "Modules/contrastbrightness.h"
#include "Modules/dft.h"
#include "Imgproc/filter.h"
#include "Imgproc/customfilter.h"

using namespace cv;

namespace Ui {
class ToolboxMainWindow;
}

class ToolboxMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolboxMainWindow(QWidget *parent = 0);
    ~ToolboxMainWindow();

private slots:
    void on_loadFirstImageButton_clicked();
    void resizeEvent(QResizeEvent *e);

    void on_scaleCheckBox_clicked(bool checked);

    void on_actionBlend_Two_Image_triggered();

    void on_loadSecondImageButton_clicked();

    void on_actionContrast_and_Brightness_triggered();

    void on_actionDiscrete_Fourier_Transform_DFT_triggered();

    void on_actionFilter_triggered();

    void on_actionApply_Custom_Kernel_triggered();

private:
    Ui::ToolboxMainWindow *ui;

    Mat firstImage;
    Mat secondImage;

    QSize firstImageSize;
    QSize secondImageSize;

    QPixmap firstPixmap;
    QPixmap secondPixmap;
};

#endif // TOOLBOXMAINWINDOW_H
