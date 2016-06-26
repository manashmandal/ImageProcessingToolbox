#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include "../imagehandler.h"

enum CAMERA_COMMAND {RESUME, PAUSE};

class CameraThread : public QThread
{
    Q_OBJECT

public:
    //Ctor
    CameraThread():camera(0), command(CAMERA_COMMAND::PAUSE) { this->terminate(); }

    void run();

public slots:
    void receivedCommand(CAMERA_COMMAND command);

signals:
    void sendCapturedFrame(QPixmap originalFrame, QPixmap modifiedFrame);

private:
    VideoCapture camera;
    CAMERA_COMMAND command;

};

#endif // CAMERATHREAD_H
