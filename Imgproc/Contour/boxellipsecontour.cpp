#include "boxellipsecontour.h"
#include "ui_boxellipsecontour.h"

BoxEllipseContour::BoxEllipseContour(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxEllipseContour)
{
    ui->setupUi(this);
}

BoxEllipseContour::BoxEllipseContour(Mat img):originalImage(img), ui(new Ui::BoxEllipseContour), rng(12345), threshold(100)
{
    ui->setupUi(this);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    cvtColor(originalImage, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
}

void BoxEllipseContour::applyBoxEllipseContour(int thres)
{
    Mat threshold_output;
    vector <vector <Point> > contours;
    vector <Vec4i> hierarchy;

    cv::threshold(image, threshold_output, thres, 255, THRESH_BINARY);

    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Find the rotated rectangles and ellipses for each contour
    vector <RotatedRect> minRect (contours.size());
    vector <RotatedRect> minEllipse(contours.size());

    for (unsigned int i = 0; i < contours.size(); i++){
        minRect[i] = minAreaRect(Mat(contours[i]));
        if (contours[i].size() > 5){
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    //Draw contours + rotated rects + ellipse
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);

    for (unsigned int i = 0; i < contours.size(); i++){
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //contour
        drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        //ellipse
        ellipse(drawing, minEllipse[i], color, 2, 8);
        //rotated rectangle
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for (unsigned int j = 0; j < 4; j++){
            line(drawing, rect_points[j], rect_points[(j+1) % 4], color, 1, 8);
        }
    }

    ui->image->setPixmap(ImageHandler::getQPixmap(drawing));
}


BoxEllipseContour::~BoxEllipseContour()
{
    delete ui;
}

void BoxEllipseContour::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->thresholdSlider->setValue(100);
}

void BoxEllipseContour::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void BoxEllipseContour::on_thresholdSlider_sliderMoved(int position)
{
    threshold = ui->thresholdSlider->maximum() + ui->thresholdSlider->minimum() - position;
    applyBoxEllipseContour(threshold);
}
