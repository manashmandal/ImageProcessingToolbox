#include "sobeledgedetector.h"
#include "ui_sobeledgedetector.h"

SobelEdgeDetector::SobelEdgeDetector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SobelEdgeDetector)
{
    ui->setupUi(this);
}

SobelEdgeDetector::SobelEdgeDetector(Mat img) : image(img), ui(new Ui::SobelEdgeDetector), ddepth(CV_16S), ksize(3), delta(0), scale(1)
{
    ui->setupUi(this);
    detectEdge();
}

void SobelEdgeDetector::detectEdge()
{
    cvtColor(image, image, CV_BGR2GRAY);

    Mat grad_x;
    Mat grad_y;

    Mat abs_grad_x;
    Mat abs_grad_y;

    Mat grad;

    Sobel(image, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    Sobel(image, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    ui->image->setPixmap(ImageHandler::getQPixmap(grad));
}

SobelEdgeDetector::~SobelEdgeDetector()
{
    delete ui;
}

void SobelEdgeDetector::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}
