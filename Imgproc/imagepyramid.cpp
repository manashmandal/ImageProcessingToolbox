#include "imagepyramid.h"
#include "ui_imagepyramid.h"

ImagePyramid::ImagePyramid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImagePyramid)
{
    ui->setupUi(this);
}

ImagePyramid::ImagePyramid(Mat img):originalImage(img), image(img), ui(new Ui::ImagePyramid), pyrUpCount(0)
{
    ui->setupUi(this);

    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    this->setWindowTitle("Image Pyramid");
    this->setWindowModality(Qt::ApplicationModal);
}

ImagePyramid::~ImagePyramid()
{
    delete ui;
}

void ImagePyramid::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void ImagePyramid::on_pyrUpButton_clicked()
{
    if (pyrUpCount < 3){
        pyrUp(image, image , Size(image.cols * 2, image.rows * 2));
        pyrUpCount++;
        ui->image->setPixmap(ImageHandler::getQPixmap(image));
    } else {
        QMessageBox::warning(this, "Memory out warning", "Can't perform this operation due to memroy insufficient");
    }
}

void ImagePyramid::on_pyrDownButton_clicked()
{
    pyrUpCount--;
    pyrDown(image, image, Size(image.cols / 2, image.rows / 2));
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}

void ImagePyramid::on_resetButton_clicked()
{
    image = originalImage;
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
    pyrUpCount = 0;
}
