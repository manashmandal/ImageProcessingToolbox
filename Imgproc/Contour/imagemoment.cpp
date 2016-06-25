#include "imagemoment.h"
#include "ui_imagemoment.h"

ImageMoment::ImageMoment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageMoment)
{
    ui->setupUi(this);
}

ImageMoment::ImageMoment(Mat img):originalImage(img), threshold(100), ui(new Ui::ImageMoment), rng(12345)
{
    ui->setupUi(this);
    ui->image->setPixmap(ImageHandler::getQPixmap(img));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
}

void ImageMoment::applyMoment(int thres)
{
    Mat canny_output;
    vector <vector <Point> > contours;
    vector <Vec4i> hierarchy;

    Canny(image, canny_output, thres, thres * 2, 3);
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Get the moments
    vector <Moments> mu(contours.size());
    for (unsigned int i = 0; i < contours.size(); i++){
        mu[i] = moments(contours[i], false);
    }

    //Get the mass centers
    vector <Point2f> mc (contours.size());

    for (unsigned int i = 0; i < contours.size(); i++){
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01/mu[i].m00);
    }

    //Draw contours
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (unsigned int i = 0; i < contours.size(); i++){
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle(drawing, mc[i], 4, color, -1, 8, 0);
    }
    ui->image->setPixmap(ImageHandler::getQPixmap(drawing));
}

ImageMoment::~ImageMoment()
{
    delete ui;
}

void ImageMoment::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->thresholdSlider->setValue(100);
}

void ImageMoment::on_thresholdSlider_sliderMoved(int position)
{
    this->threshold = ui->thresholdSlider->maximum() + ui->thresholdSlider->minimum() - position;
    this->applyMoment(threshold);
}

void ImageMoment::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}
