#include "histogramequalization.h"
#include "ui_histogramequalization.h"

HistogramEqualization::HistogramEqualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistogramEqualization)
{
    ui->setupUi(this);
}

HistogramEqualization::HistogramEqualization(Mat img): originalImage(img), ui(new Ui::HistogramEqualization)
{
    ui->setupUi(this);
    originalHistogram = createHistogram(originalImage);

    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->histogram->setPixmap(ImageHandler::getQPixmap(originalHistogram));

    equalizeHistogram();

    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->histogramScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

}

Mat HistogramEqualization::createHistogram(Mat &img)
{
    vector <Mat> bgr_planes;
    split(img, bgr_planes);

    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range };

    bool uniform = true;
    bool accumulate = false;

    Mat b_hist;
    Mat g_hist;
    Mat r_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound(double(hist_w / histSize));

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++){
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ), Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);

    line(histImage, Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ), Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);

        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ), Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
    }

    return histImage;
}

void HistogramEqualization::equalizeHistogram()
{
    image = originalImage;
    cvtColor(image, image, CV_BGR2GRAY);
    equalizeHist(image, image);
    cvtColor(image, image, CV_GRAY2BGR);
    histogram = createHistogram(image);
}

HistogramEqualization::~HistogramEqualization()
{
    delete ui;
}

void HistogramEqualization::on_toggleImage_clicked(bool checked)
{
    if (checked){
        ui->image->setPixmap(ImageHandler::getQPixmap(image));
        ui->histogram->setPixmap(ImageHandler::getQPixmap(histogram));
    } else {
        ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
        ui->histogram->setPixmap(ImageHandler::getQPixmap(originalHistogram));
    }
}

void HistogramEqualization::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
    ui->histogram->setScaledContents(checked);
}
