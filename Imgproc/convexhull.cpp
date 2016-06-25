#include "convexhull.h"
#include "ui_convexhull.h"

ConvexHull::ConvexHull(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConvexHull)
{
    ui->setupUi(this);
}

ConvexHull::ConvexHull(Mat img):originalImage(img), rng(12345), ui(new Ui::ConvexHull), threshold(100)
{
    ui->setupUi(this);

    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));

    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
}

void ConvexHull::findConvexHull(int thres)
{
    Mat originalCopy = originalImage.clone();
    Mat threshold_output;

    vector <vector <Point> > contours;
    vector <Vec4i> hierarchy;

    cv::threshold(image, threshold_output, thres, 255, THRESH_BINARY);

    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Find convex hull object for each contour
    vector <vector <Point> > hull(contours.size());

    for (int i = 0; i < contours.size(); i++) convexHull(Mat(contours[i]), hull[i], false);

    //Draw contours + hull results
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++){
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 1, 8, vector <Vec4i>(), 0, Point());
        drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
    }

    ui->image->setPixmap(ImageHandler::getQPixmap(drawing));
}

ConvexHull::~ConvexHull()
{
    delete ui;
}

void ConvexHull::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
}

void ConvexHull::on_thresholdSlider_sliderMoved(int thres)
{
    threshold = ui->thresholdSlider->maximum() + ui->thresholdSlider->minimum() - thres;
    findConvexHull(threshold);
}

void ConvexHull::on_checkBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}
