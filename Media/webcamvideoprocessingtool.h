#ifndef WEBCAMVIDEOPROCESSINGTOOL_H
#define WEBCAMVIDEOPROCESSINGTOOL_H

#include <QDialog>

#include "../imagehandler.h"
#include "camerathread.h"

namespace Ui {
class WebCamVideoProcessingTool;
}

class WebCamVideoProcessingTool : public QDialog
{
    Q_OBJECT

public:
    explicit WebCamVideoProcessingTool();
    ~WebCamVideoProcessingTool();
    CameraThread *getCameraThread();

signals:
    void sendCommand(CAMERA_COMMAND command);

private slots:
    void disconnect(int res);

    void on_startButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::WebCamVideoProcessingTool *ui;
    CameraThread *cameraThread;
};

#endif // WEBCAMVIDEOPROCESSINGTOOL_H
