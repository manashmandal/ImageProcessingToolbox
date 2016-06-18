#include "filter.h"
#include "ui_filter.h"

Filter::Filter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
}

Filter::Filter(Mat img) :  originalImage(img), ui(new Ui::Filter), currentFilter(FILTER_HOMOGENEOUS), ksize(3, 3)
{
    ui->setupUi(this);
    this->setWindowTitle("Filter");

    ui->filteredImage->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->filteredImageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

}

void Filter::applyFilter()
{
    configureSpinBox();
    switch(currentFilter){
        case FILTER_HOMOGENEOUS:
            blur(originalImage, image, ksize);
            ui->filteredImage->setPixmap(ImageHandler::getQPixmap(image));
        break;
    case FILTER_GAUSSIAN:
        GaussianBlur(originalImage, image, ksize, 0, 0);
        ui->filteredImage->setPixmap(ImageHandler::getQPixmap(image));
        break;
    case FILTER_MEDIAN:
        medianBlur(originalImage, image, ksize.height);
        ui->filteredImage->setPixmap(ImageHandler::getQPixmap(image));
        break;
    case FILTER_BILATERAL:
        bilateralFilter(originalImage, image, 5, sigma, sigma);
        break;
    }
}

Filter::~Filter()
{
    delete ui;
}

void Filter::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->filteredImage->setScaledContents(checked);
}

void Filter::on_filterComboBox_currentIndexChanged(int index)
{
    currentFilter = FilterType(index);
    applyFilter();
}

void Filter::on_applyButton_clicked()
{
    ui->filteredImage->setPixmap(ImageHandler::getQPixmap(image));
}

void Filter::on_valueSpinBox_valueChanged(int arg)
{
    ksize.height = arg;
    ksize.width = arg;
    sigma = arg;
    applyFilter();
}

void Filter::configureSpinBox()
{

    if (currentFilter == FILTER_HOMOGENEOUS ||
        currentFilter == FILTER_GAUSSIAN ||
        currentFilter == FILTER_MEDIAN
        )
    {
        if (ui->valueSpinBox->value() % 2 == 0) ui->valueSpinBox->setValue(ui->valueSpinBox->value() - 1);
        ui->spinBoxLabel->setText("Kernel Size");
        int max_val = originalImage.cols;
        if (max_val % 2 == 0) max_val--;
        ui->valueSpinBox->setMaximum(max_val);
        ui->valueSpinBox->setSingleStep(2);
    }

    else {
        ui->spinBoxLabel->setText("Sigma");
        ui->valueSpinBox->setMaximum(500);
        ui->valueSpinBox->setSingleStep(1);
    }
}
