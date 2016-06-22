#include "houghtransformation.h"
#include "ui_houghtransformation.h"

HoughTransformation::HoughTransformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HoughTransformation)
{
    ui->setupUi(this);
}

HoughTransformation::HoughTransformation(Mat img) : originalImage(img), ui(new Ui::HoughTransformation)
{
    ui->setupUi(this);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
}

void HoughTransformation::houghTransform()
{
    threshold = ui->thresholdSlider->maximum() - ui->thresholdSlider->value() + ui->thresholdSlider->minimum();

    if (ui->transformComboBox->currentIndex() == 0 || ui->transformComboBox->currentIndex() == 1){
        //Turning on the slider
        ui->thresholdSlider->setEnabled(true);
        //Standard Line Transform
        Mat dst;
        Mat cdst;

        Canny(originalImage, dst, 50, 200, 3);
        cvtColor(dst, cdst, CV_GRAY2BGR);

        if (ui->transformComboBox->currentIndex() == 0){

            vector <Vec2f> lines;

            HoughLines(dst, lines, 1, CV_PI/ 180, threshold, 0 , 0);

            for (size_t i = 0; i < lines.size(); i++){
                float rho = lines[i][0];
                float theta = lines[i][1];

                Point point1;
                Point point2;

                double a = cos(theta);
                double b = sin(theta);
                double x0 = a * rho;
                double y0 = b * rho;

                point1.x = cvRound(x0 + 1000 * (-b));
                point1.y = cvRound(y0 + 1000*(a));
                point2.x = cvRound(x0 - 1000 * (-b));
                point2.y = cvRound(y0 - 1000 * (a));

                line(cdst, point1, point2, Scalar(0, 0, 255), 3, CV_AA);
            }

            ui->image->setPixmap(ImageHandler::getQPixmap(cdst));
        } else {
            vector <Vec4i> lines;

            HoughLinesP(dst, lines, 1, CV_PI / 180, threshold , 50, 10);
            for (size_t i = 0; i < lines.size(); i++){
                Vec4i l = lines[i];
                line (cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
            }

            ui->image->setPixmap(ImageHandler::getQPixmap(cdst));
        }
    }

    else if (ui->transformComboBox->currentIndex() == 2){
        //Disabling the slider
        ui->thresholdSlider->setEnabled(false);

        cvtColor(originalImage, image, CV_BGR2GRAY);
        GaussianBlur(image, image, Size(9, 9), 2, 2);
        vector <Vec3f> circles;
        HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows / 8, 200, 100, 0, 0);

        for (size_t i = 0; i < circles.size(); i++){
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //Circle center
            circle(image, center, 3, Scalar(0, 255, 0) , -1, 8, 0);
            //Circle outline
            circle(image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
        }
        ui->image->setPixmap(ImageHandler::getQPixmap(image));
    }
}

HoughTransformation::~HoughTransformation()
{
    delete ui;
}

void HoughTransformation::on_thresholdSlider_sliderMoved(int position)
{
    threshold = ui->thresholdSlider->maximum() - position + ui->thresholdSlider->minimum();
    houghTransform();
}

void HoughTransformation::on_resetButton_clicked()
{
    image = originalImage;
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}

void HoughTransformation::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void HoughTransformation::on_transformComboBox_currentIndexChanged(int index)
{
    houghTransform();
}
