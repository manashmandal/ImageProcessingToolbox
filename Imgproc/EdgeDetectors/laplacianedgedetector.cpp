#include "laplacianedgedetector.h"
#include "ui_laplacianedgedetector.h"

LaplacianEdgeDetector::LaplacianEdgeDetector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LaplacianEdgeDetector)
{
    ui->setupUi(this);
}

LaplacianEdgeDetector::LaplacianEdgeDetector(Mat img):image(img), ui(new Ui::LaplacianEdgeDetector), ksize(3), scale(1), delta(0), ddepth(CV_16S)
{
    ui->setupUi(this);
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    detectEdge();
}

LaplacianEdgeDetector::~LaplacianEdgeDetector()
{
    delete ui;
}

void LaplacianEdgeDetector::detectEdge()
{
    Mat abs_dst;
    cvtColor(image, image, CV_BGR2GRAY);
    Laplacian(image, image, ddepth, ksize, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(image, abs_dst);
    ui->image->setPixmap(ImageHandler::getQPixmap(abs_dst));
}

void LaplacianEdgeDetector::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}
