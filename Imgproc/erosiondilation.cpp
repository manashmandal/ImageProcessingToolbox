#include "erosiondilation.h"
#include "ui_erosiondilation.h"

ErosionDilation::ErosionDilation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErosionDilation)
{
    ui->setupUi(this);
}

ErosionDilation::ErosionDilation(Mat img) : originalImage(img), ui(new Ui::ErosionDilation), ksize(3)
{
    ui->setupUi(this);
    this->setWindowTitle("Erosion | Dilation");

    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

     element = getStructuringElement(MORPH_RECT, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));

     setWindowModality(Qt::ApplicationModal);
}

ErosionDilation::~ErosionDilation()
{
    delete ui;
}

void ErosionDilation::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void ErosionDilation::on_kernelSizeSlider_sliderMoved(int position)
{
    ksize = position;
    setStructureType(ui->structuringElementComboBox->currentText());
    erodeDilate();
}

void ErosionDilation::on_structuringElementComboBox_currentIndexChanged(const QString &structType)
{
    setStructureType(structType);
    erodeDilate();
}

void ErosionDilation::erodeDilate()
{
    if (ui->erodeRadioButton->isChecked()){
        erode(originalImage, image, element);
    } else if (ui->dilateRadioButton->isChecked()){
        dilate(originalImage, image, element);
    }
    ui->image->setPixmap(ImageHandler::getQPixmap(image));
}


void ErosionDilation::setStructureType(QString structType)
{
    if (structType == "Rectangular"){
        element = getStructuringElement(MORPH_RECT, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));
    } else if (structType == "Cross Shaped"){
        element = getStructuringElement(MORPH_CROSS, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));
    } else {
        element = getStructuringElement(MORPH_ELLIPSE, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));
    }
}

void ErosionDilation::on_dilateRadioButton_clicked(bool checked)
{
    setStructureType(ui->structuringElementComboBox->currentText());
    erodeDilate();
}

void ErosionDilation::on_erodeRadioButton_clicked(bool checked)
{
    setStructureType(ui->structuringElementComboBox->currentText());
    erodeDilate();
}
