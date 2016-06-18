#include "contrastbrightness.h"
#include "ui_contrastbrightness.h"

ContrastBrightness::ContrastBrightness(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContrastBrightness)
{
    ui->setupUi(this);
}

ContrastBrightness::ContrastBrightness(Mat img):
    ui(new Ui::ContrastBrightness), alpha(1), beta(0.0)
{
    ui->setupUi(this);

    this->originalImage = img;

    ui->modifiedImage->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

}

ContrastBrightness::~ContrastBrightness()
{
    delete ui;
}

void ContrastBrightness::on_alphaSlider_sliderMoved(int position)
{
    alpha = (1.00 * position) / 100.0;
    qDebug() << "alpha: " << alpha;
    ui->alphaValue->setText(QString::number(alpha));
    originalImage.convertTo(image, -1, alpha, beta);
    ui->modifiedImage->setPixmap(ImageHandler::getQPixmap(image));
}

void ContrastBrightness::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->modifiedImage->setScaledContents(checked);
}

void ContrastBrightness::on_betaSlider_sliderMoved(int position)
{
    beta = position;
    qDebug() << "beta : " << beta;
    ui->betaValue->setText(QString::number(beta));
    originalImage.convertTo(image, -1, alpha, beta);
    ui->modifiedImage->setPixmap(ImageHandler::getQPixmap(image));
}
