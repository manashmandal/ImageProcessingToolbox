#include "boxcirclecontour.h"
#include "ui_boxcirclecontour.h"

BoxCircleContour::BoxCircleContour(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxCircleContour)
{
    ui->setupUi(this);
}

BoxCircleContour::BoxCircleContour(Mat img):originalImage(img), threshold(100), ui(new Ui::BoxCircleContour), rng(12345)
{
    ui->setupUi(this);

    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));

    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
}

void BoxCircleContour::applyBoundingBoxAndCircleContour(int thres)
{
    Mat threshold_output;
    vector <vector <Point> > contours;
    vector <Vec4i> hierarchy;

    cv::threshold(image, threshold_output, thres, 255, THRESH_BINARY);

    cv::findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector <vector <Point> > contours_poly (contours.size());
    vector <Rect> boundRect(contours.size());
    vector <Point2f> center (contours.size());
    vector <float> radius (contours.size());

    for (unsigned int i = 0; i < contours.size(); i++){
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle((Mat) contours_poly[i], center[i], radius[i]);
    }

    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);

    //Drawing all up
    for (unsigned int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
        circle(drawing, center[i], int (radius[i]), color, 2, 8, 0);
    }

    ui->image->setPixmap(ImageHandler::getQPixmap(drawing));
}

BoxCircleContour::~BoxCircleContour()
{
    delete ui;
}

void BoxCircleContour::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void BoxCircleContour::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->thresholdSlider->setValue(100);
}

void BoxCircleContour::on_thresholdSlider_sliderMoved(int position)
{
    threshold = ui->thresholdSlider->maximum() + ui->thresholdSlider->minimum() - position;
    applyBoundingBoxAndCircleContour(threshold);
}
