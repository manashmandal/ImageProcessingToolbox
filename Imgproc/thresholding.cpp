#include "thresholding.h"
#include "ui_thresholding.h"

Thresholding::Thresholding(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Thresholding)
{
    ui->setupUi(this);
}

Thresholding::Thresholding(Mat img):originalImage(img), ui(new Ui::Thresholding)
{
    ui->setupUi(this);
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
}

Thresholding::~Thresholding()
{
    delete ui;
}

void Thresholding::on_scaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void Thresholding::on_thresholdValueSlider_sliderMoved(int position)
{
    thresValue = position;
    if (ui->thresholdTypeComboBox->currentIndex() != 0)
        threshold(originalImage, image, thresValue, 255, ui->thresholdTypeComboBox->currentIndex() - 1);
    else
        image = originalImage;
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}

void Thresholding::on_thresholdTypeComboBox_currentIndexChanged(int index)
{
    if (index != 0)
        threshold(originalImage, image, thresValue, 255, index - 1);
    else
        image = originalImage;
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}
