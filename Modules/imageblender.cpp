#include "imageblender.h"
#include "ui_imageblender.h"


ImageBlender::ImageBlender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageBlender)
{
    ui->setupUi(this);

}

ImageBlender::~ImageBlender()
{
    delete ui;
}

ImageBlender::ImageBlender(Mat src1, Mat src2): ui(new Ui::ImageBlender)
{
    ui->setupUi(this);

    source1 = src1;
    source2 = src2;
    ui->blendedImage->setScaledContents(true);
    ui->blendedImageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->blendedImage->setPixmap(ImageHandler::getQPixmap(source2));
    this->setWindowTitle("Image Blender");
}


void ImageBlender::on_alphaSlider_sliderMoved(int position)
{
    double alpha = (position * 1.00) / 100.0;
    QString currentValue = QString("Alpha Value: ( %1 )").arg(alpha);
    ui->alphaValueLabel->setText(currentValue);
    double beta = 1.0 - alpha;
    addWeighted(source1, alpha, source2, beta, 0, blendedImage);
    ui->blendedImage->setPixmap(ImageHandler::getQPixmap(blendedImage));
}
