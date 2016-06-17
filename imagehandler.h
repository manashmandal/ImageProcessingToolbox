#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPixmap>


using namespace cv;

class ImageHandler
{
public:
    ImageHandler();
    static QPixmap getQPixmap(Mat &image);
    static QPixmap getQPixmap(QImage &image);
};

#endif // IMAGEHANDLER_H
