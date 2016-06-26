#include "webcamvideoprocessingtool.h"
#include "ui_webcamvideoprocessingtool.h"


WebCamVideoProcessingTool::WebCamVideoProcessingTool() : ui(new Ui::WebCamVideoProcessingTool)
{
    ui->setupUi(this);
    cameraThread = new CameraThread;
    connect(this, SIGNAL(sendCommand(CAMERA_COMMAND)), this->cameraThread, SLOT(receivedCommand(CAMERA_COMMAND)));
    connect(this, SIGNAL(finished(int)), this, SLOT(disconnect(int)));

    //Disable stop button and enable start button at start
    ui->pauseButton->setEnabled(false);
}

void WebCamVideoProcessingTool::disconnect(int res)
{
    emit sendCommand(CAMERA_COMMAND::PAUSE);
    cameraThread->terminate();
    delete ui;
    delete cameraThread;
}

CameraThread *WebCamVideoProcessingTool::getCameraThread()
{
    return this->cameraThread;
}

WebCamVideoProcessingTool::~WebCamVideoProcessingTool()
{
    emit sendCommand(CAMERA_COMMAND::PAUSE);
    cameraThread->terminate();
    delete ui;
    delete cameraThread;
}

void WebCamVideoProcessingTool::on_startButton_clicked()
{
    emit sendCommand(CAMERA_COMMAND::RESUME);
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
}

void WebCamVideoProcessingTool::on_pauseButton_clicked()
{
    emit sendCommand(CAMERA_COMMAND::PAUSE);
    ui->startButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
}
