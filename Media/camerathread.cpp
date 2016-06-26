#include "camerathread.h"

void CameraThread::run()
{
    this->sleep(1);

    while (command == CAMERA_COMMAND::RESUME && camera.isOpened()){
        Mat frame;
        Mat modifiedFrame;
        camera >> frame;

        //Apply modifier here
        cvtColor(frame, modifiedFrame, CV_BGR2GRAY);

        emit sendCapturedFrame(ImageHandler::getQPixmapAndSave(frame), ImageHandler::getQPixmap(modifiedFrame));
    }
    qDebug() << "Sending frame";
}

void CameraThread::receivedCommand(CAMERA_COMMAND command)
{
    this->command = command;

    if (command == CAMERA_COMMAND::RESUME)
    {
        this->camera.open(0);
        this->start();
    }

    else if (command == CAMERA_COMMAND::PAUSE)
    {
        this->camera.release();
        this->terminate();
    }
}
