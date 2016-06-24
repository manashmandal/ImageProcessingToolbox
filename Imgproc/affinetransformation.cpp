#include "affinetransformation.h"
#include "ui_affinetransformation.h"

AffineTransformation::AffineTransformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AffineTransformation)
{
    ui->setupUi(this);
}

AffineTransformation::AffineTransformation(Mat img) : originalImage(img), ui(new Ui::AffineTransformation), rotation_mat(2, 3, CV_32FC1), warp_mat(2, 3, CV_32FC1), warpDst(Mat::zeros(img.rows, img.cols, img.type())), angle(0.0), scale(1.0)
{
    ui->setupUi(this);
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

    sourceTriangle[0] = Point2f(0, 0);
    sourceTriangle[1] = Point2f(img.cols -1, 0);
    sourceTriangle[2] = Point2f(0, img.rows - 1);

    destinationTriangle[0] = Point2f(img.cols * 0.0, img.rows * 0.33);
    destinationTriangle[1] = Point2f(img.cols * 0.85, img.rows * 0.25);
    destinationTriangle[2] = Point2f(img.cols * 0.15, img.rows * 0.7);

    warp_mat = getAffineTransform(sourceTriangle, destinationTriangle);

    warpAffine(originalImage, warpDst, warp_mat, warpDst.size());
    center = Point(warpDst.cols / 2, warpDst.rows / 2);
}

AffineTransformation::~AffineTransformation()
{
    delete ui;
}

void AffineTransformation::affineTransform(float angle, float scale)
{
    rotation_mat = getRotationMatrix2D(center, angle, scale);

    warpAffine(warpDst, warp_rotate_dst, rotation_mat, warpDst.size());

    ui->image->setPixmap(ImageHandler::getQPixmap(warp_rotate_dst));
}

void AffineTransformation::on_pointButton_clicked(bool checked)
{
    if (checked){
        QMessageBox::about(this, "This function is not available", "This function will be added later");
    }
    ui->pointButton->setChecked(false);
}

void AffineTransformation::on_angleSlider_sliderMoved(int position)
{
    angle = float(position);
    affineTransform(angle, scale);
}

void AffineTransformation::on_scaleSlider_sliderMoved(int position)
{
    scale = float(position) / 100.0;
    affineTransform(angle, scale);
}

void AffineTransformation::on_autoFitCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void AffineTransformation::on_resetButton_clicked()
{
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
}
