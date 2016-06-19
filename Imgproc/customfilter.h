#ifndef CUSTOMFILTER_H
#define CUSTOMFILTER_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../imagehandler.h"

using namespace cv;

#include <iostream>
using namespace std;

namespace Ui {
class CustomFilter;
}

class CustomFilter : public QWidget
{
    Q_OBJECT

public:
    explicit CustomFilter(QWidget *parent = 0);
    explicit CustomFilter(Mat img);
    ~CustomFilter();

private slots:
    void on_createKernelButton_clicked();

    void getKernelMatrix(bool done);
    void closeKernelTable(int done);

    void on_autoScaleCheckBox_clicked(bool checked);

    void on_getKernelButton_clicked();

private:
    Ui::CustomFilter *ui;
    Mat kernel;

    Mat image;
    Mat originalImage;

    int krow;
    int kcol;

    QString appliedKernel;

private:
    QDialog *kernelTableDialog;

    QPushButton *doneButton;
    QTableWidget *kernelTableWidget;
};

#endif // CUSTOMFILTER_H
