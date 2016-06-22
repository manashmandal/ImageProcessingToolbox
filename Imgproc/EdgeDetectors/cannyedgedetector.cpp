#include "cannyedgedetector.h"
#include "ui_cannyedgedetector.h"

CannyEdgeDetector::CannyEdgeDetector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CannyEdgeDetector)
{
    ui->setupUi(this);
}

CannyEdgeDetector::CannyEdgeDetector(Mat img):originalImage(img), ui(new Ui::CannyEdgeDetector), ksize(3), minThres(1), ratio(3)
{
    ui->setupUi(this);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
}

CannyEdgeDetector::~CannyEdgeDetector()
{
    delete ui;
}

void CannyEdgeDetector::on_minThresSlider_sliderMoved(int position)
{
    minThres = position;
    cannyEdgeDetect();
}

void CannyEdgeDetector::cannyEdgeDetect()
{
    //filter
    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
    Canny(image, image, minThres, minThres * ratio, ksize);
    output = Scalar::all(0);
    originalImage.copyTo(output, image);
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}

void CannyEdgeDetector::on_checkBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void CannyEdgeDetector::on_resetButton_clicked()
{
    image = originalImage;
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}
