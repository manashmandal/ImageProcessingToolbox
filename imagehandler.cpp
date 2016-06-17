#include "imagehandler.h"

ImageHandler::ImageHandler()
{

}

QPixmap ImageHandler::getQPixmap(Mat &image)
{
    QImage qImage;
    Mat dst;

    switch (image.type()) {
    case CV_8UC1:
        cvtColor(image, dst, CV_GRAY2BGR);
        break;
    case CV_8UC3:
        cvtColor(image, dst, CV_BGR2RGB);
        break;
    }

    qImage = QImage(dst.data, dst.cols, dst.rows, dst.cols * 3, QImage::Format_RGB888);

    QPixmap pixmap = QPixmap::fromImage(qImage);
    return pixmap;
}

QPixmap ImageHandler::getQPixmap(QImage &image){
    QPixmap pixmap(QPixmap::fromImage(image));
    pixmap.scaled(image.size());
    return pixmap;
}
