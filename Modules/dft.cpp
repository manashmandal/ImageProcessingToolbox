#include "dft.h"
#include "ui_dft.h"

DFT::DFT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DFT)
{
    ui->setupUi(this);
    setWindowTitle("Discrete Fourier Transform (DFT)");
}

void DFT::discreteFourierTransform(Mat &img)
{
    Mat padded;

    //Get optimal size
    int m = getOptimalDFTSize(img.rows);
    int n = getOptimalDFTSize(img.cols);

    //Make Uniform border
    copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complex;
    merge(planes, 2, complex);
    dft(complex, complex);
    split(complex, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);

    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, CV_MINMAX);

    dftImage = mag;
}

DFT::DFT(Mat img) : ui(new Ui::DFT)
{
    ui->setupUi(this);
    originalImage = img;
    image = img;
    ui->modifiedImage->setPixmap(ImageHandler::getQPixmap(img));
    cvtColor(img, image, CV_BGR2GRAY);
    discreteFourierTransform(image);
}

DFT::~DFT()
{
    delete ui;
}



void DFT::on_openDFTImage_clicked()
{
    imshow("DFT Image", dftImage);
}

void DFT::on_newImageButton_clicked()
{
    QString imageFilePath = QFileDialog::getOpenFileName(this,
          "Open Image", "D:\\hope", "Image Files (*.png *.jpg *.bmp)");
    Mat image = imread(imageFilePath.toStdString());
    ui->modifiedImage->setPixmap(ImageHandler::getQPixmap(image));
    cvtColor(image, image, CV_BGR2GRAY);
    discreteFourierTransform(image);
}
