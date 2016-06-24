#include "backprojection.h"
#include "ui_backprojection.h"



BackProjection::BackProjection(Mat img):originalImage(img), ui(new Ui::BackProjection)
{
    ui->setupUi(this);

    cvtColor(img, hsv, CV_BGR2HSV);

    ui->image->setPixmap(ImageHandler::getQPixmap(img));

    hue.create(hsv.size(), hsv.depth());

    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);

    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->histogramScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
}

void BackProjection::histAndBackproject(int bins)
{
    int histSize = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges = {hue_range};

    calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

    calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

    int w = 600;
    int h = 550;
    int bin_w = cvRound(double(w/histSize));

    histogram = Mat::zeros(w, h, CV_8UC3);

    for (int i = 0; i < bins; i++){
        rectangle(histogram, Point(i * bin_w, h), Point( (i+1) * bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(0, 255, 0));
    }

    ui->image->setPixmap(ImageHandler::getQPixmap(backproj));
    ui->histogram->setPixmap(ImageHandler::getQPixmap(histogram));
}

BackProjection::~BackProjection()
{
    delete ui;
}



void BackProjection::on_autoFitCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
    ui->histogram->setScaledContents(checked);
}

void BackProjection::on_binSlider_sliderMoved(int bins)
{
    histAndBackproject(bins);
}

void BackProjection::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->histogram->clear();
}
