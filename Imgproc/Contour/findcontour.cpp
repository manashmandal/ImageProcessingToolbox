#include "findcontour.h"
#include "ui_findcontour.h"

FindContour::FindContour(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindContour)
{
    ui->setupUi(this);
}

FindContour::FindContour(Mat img):originalImage(img), ui(new Ui::FindContour), threshold(100), rng(12345)
{
    ui->setupUi(this);
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
}

void FindContour::findContours(int threshold)
{
    Mat canny_output;
    vector <vector <Point> > contours;
    vector <Vec4i> hierarchy;

    Canny(image, canny_output, threshold, threshold * 2, 3);

    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++){
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }

    ui->image->setPixmap(ImageHandler::getQPixmap(drawing));
}

FindContour::~FindContour()
{
    delete ui;
}

void FindContour::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->thresholdSlider->setValue(100);
}

void FindContour::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void FindContour::on_thresholdSlider_sliderMoved(int thres)
{
    threshold = ui->thresholdSlider->maximum() + ui->thresholdSlider->minimum() - thres;
    this->findContours(threshold);
}
