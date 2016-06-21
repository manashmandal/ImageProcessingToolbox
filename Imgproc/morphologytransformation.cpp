#include "morphologytransformation.h"
#include "ui_morphologytransformation.h"

MorphologyTransformation::MorphologyTransformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MorphologyTransformation)
{
    ui->setupUi(this);
}

MorphologyTransformation::MorphologyTransformation(Mat img): originalImage(img), ksize(3), ui(new Ui::MorphologyTransformation)
{
    ui->setupUi(this);

    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    element = getStructuringElement(MORPH_RECT, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));

    ui->img->setPixmap(ImageHandler::getQPixmap(originalImage));
    operate(ui->operationComboBox->currentText());
    this->setWindowTitle("Morphological Transformation");
}

MorphologyTransformation::~MorphologyTransformation()
{
    delete ui;
}

void MorphologyTransformation::operate(QString operation)
{
    //Creating structuring kernel
    if (ui->structElmComboBox->currentText() == "Rectangular") element = getStructuringElement(MORPH_RECT, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));
    else if (ui->structElmComboBox->currentText() == "Cross Shaped") element = getStructuringElement(MORPH_CROSS, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));
    else element = getStructuringElement(MORPH_ELLIPSE, Size(ksize, ksize), Point((ksize - 1) / 2, (ksize - 1) / 2));

    //Applying operation
    if (operation == "Opening") morphologyEx(originalImage ,image, MORPH_OPEN, element);
    else if (operation == "Closing") morphologyEx(originalImage, image, MORPH_CLOSE, element);
    else if (operation == "Morphological Gradient") morphologyEx(originalImage, image, MORPH_GRADIENT, element);
    else if (operation == "Top Hat") morphologyEx(originalImage, image, MORPH_TOPHAT, element);
    else morphologyEx(originalImage, image, MORPH_BLACKHAT, element);


    ui->img->setPixmap(ImageHandler::getQPixmap(image));
}



void MorphologyTransformation::on_scaleCheckBox_clicked(bool checked)
{
    ui->img->setScaledContents(checked);
}

void MorphologyTransformation::on_kSizeSlider_sliderMoved(int position)
{
    ksize = position;
    operate(ui->operationComboBox->currentText());
}

void MorphologyTransformation::on_operationComboBox_currentIndexChanged(const QString &arg1)
{
    operate(arg1);
}

void MorphologyTransformation::on_structElmComboBox_currentIndexChanged(const QString &arg1)
{
    operate(ui->operationComboBox->currentText());
}
