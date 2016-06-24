#include "toolboxmainwindow.h"
#include "ui_toolboxmainwindow.h"


ToolboxMainWindow::ToolboxMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolboxMainWindow)
{
    ui->setupUi(this);

    //Setting config
     ui->firstImageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
     ui->secondImageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

     ui->firstImage->setScaledContents(true);
     ui->secondImage->setScaledContents(true);

     this->setWindowTitle("Image Processing Toolbox");
}

ToolboxMainWindow::~ToolboxMainWindow()
{
    delete ui;
}

void ToolboxMainWindow::on_loadFirstImageButton_clicked()
{
    QString imageFilePath = QFileDialog::getOpenFileName(this,
          "Open Image", "D:\\hope\\Screen Cap", "Image Files (*.png *.jpg *.bmp)");
    firstImage = imread(imageFilePath.toStdString());
    firstPixmap = ImageHandler::getQPixmap(firstImage);
    firstImageSize = firstPixmap.size();
    ui->firstImage->setMaximumSize(firstImageSize);
    ui->firstImage->setPixmap(firstPixmap);
}

void ToolboxMainWindow::resizeEvent(QResizeEvent *e){
    if (ui->scaleCheckBox->isChecked()){
        ui->firstImage->setMaximumSize(ui->firstImageScrollArea->size());
        ui->secondImage->setMaximumSize(ui->secondImageScrollArea->size());
    }
}

void ToolboxMainWindow::on_scaleCheckBox_clicked(bool checked)
{
    if (checked){
        ui->firstImage->setMaximumSize(ui->firstImageScrollArea->size());
        ui->secondImage->setMaximumSize(ui->secondImageScrollArea->size());
    } else {
        ui->firstImage->setMaximumSize(firstImageSize);
        ui->firstImage->setPixmap(firstPixmap);

        ui->secondImage->setMaximumSize(secondImageSize);
        ui->secondImage->setPixmap(secondPixmap);
    }
}

void ToolboxMainWindow::on_actionBlend_Two_Image_triggered()
{
    if (firstImage.size != secondImage.size){
        QMessageBox::warning(this ,"Image size not matched", "Both image must be of same dimension");
    } else if (firstImage.empty() || secondImage.empty()){
        QMessageBox::warning(this, "Image Not found", "Please load two same dimensional images to begin with");
    } else {
        ImageBlender *blender = new ImageBlender(firstImage, secondImage);
        blender->show();
    }

}

void ToolboxMainWindow::on_loadSecondImageButton_clicked()
{
    QString imageFilePath = QFileDialog::getOpenFileName(this, "Open Second Image", "D:\\hope", "Image Files (*.png *.jpg *.bmp)");
    secondImage = imread(imageFilePath.toStdString());
    secondPixmap = ImageHandler::getQPixmap(secondImage);
    secondImageSize = secondPixmap.size();
    ui->secondImage->setMaximumSize(secondImageSize);
    ui->secondImage->setPixmap(secondPixmap);
}

void ToolboxMainWindow::on_actionContrast_and_Brightness_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            ContrastBrightness *contrastBrightnessWidget = new ContrastBrightness(secondImage);
            contrastBrightnessWidget->show();
        } else {
            ContrastBrightness *contrastBrightnessWidget = new ContrastBrightness(firstImage);
            contrastBrightnessWidget->show();
        }
    }
}

void ToolboxMainWindow::on_actionDiscrete_Fourier_Transform_DFT_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Detected", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()){
            DFT *dft;
            dft = new DFT(secondImage);
            dft->show();
        } else {
            DFT *dft;
            dft = new DFT(firstImage);
            dft->show();
        }
    }
}

void ToolboxMainWindow::on_actionFilter_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            Filter  *filter = new Filter(secondImage);
            filter->show();
        } else {
            Filter  *filter = new Filter(firstImage);
            filter->show();
        }
    }
}

void ToolboxMainWindow::on_actionApply_Custom_Kernel_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            CustomFilter *customFilter = new CustomFilter(secondImage);
            customFilter->show();
        } else {
            CustomFilter *customFilter = new CustomFilter(firstImage);
            customFilter->show();
        }
    }

}

void ToolboxMainWindow::on_actionErodeDilate_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
            QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
        } else {
            if (firstImage.empty()) {
                ErosionDilation *erosionDilation = new ErosionDilation(secondImage);
                erosionDilation->show();
            } else {
                ErosionDilation *erosionDilation = new ErosionDilation(firstImage);
                erosionDilation->show();
            }
        }
}

void ToolboxMainWindow::on_actionMore_Morphology_Transformation_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            MorphologyTransformation  *morphologyTransformation = new MorphologyTransformation(secondImage);
            morphologyTransformation->show();
        } else {
            MorphologyTransformation  *morphologyTransformation = new MorphologyTransformation(firstImage);
            morphologyTransformation->show();
        }
    }
}

void ToolboxMainWindow::on_actionImage_Pyramid_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            ImagePyramid  *pyramid = new ImagePyramid(secondImage);
            pyramid->show();
        } else {
            ImagePyramid  *pyramid = new ImagePyramid(firstImage);
            pyramid->show();
        }
    }
}

void ToolboxMainWindow::on_actionThresholding_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            Thresholding  *thresholding = new Thresholding(secondImage);
            thresholding->show();
        } else {
            Thresholding  *thresholding = new Thresholding(firstImage);
            thresholding->show();
        }
    }
}

void ToolboxMainWindow::on_actionSobel_Edge_Detector_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            SobelEdgeDetector  *sobelEdgeDetector = new SobelEdgeDetector(secondImage);
            sobelEdgeDetector->show();
        } else {
            SobelEdgeDetector  *sobelEdgeDetector = new SobelEdgeDetector(firstImage);
            sobelEdgeDetector->show();
        }
    }
}

void ToolboxMainWindow::on_actionLaplacian_Edge_Detector_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            LaplacianEdgeDetector  *laplacianEdgeDetector = new LaplacianEdgeDetector(secondImage);
            laplacianEdgeDetector->show();
        } else {
            LaplacianEdgeDetector  *laplacianEdgeDetector = new LaplacianEdgeDetector(firstImage);
            laplacianEdgeDetector->show();
        }
    }
}

void ToolboxMainWindow::on_actionCanny_Edge_Detector_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            CannyEdgeDetector  *cannyEdgeDetector = new CannyEdgeDetector(secondImage);
            cannyEdgeDetector->show();
        } else {
            CannyEdgeDetector  *cannyEdgeDetector = new CannyEdgeDetector(firstImage);
            cannyEdgeDetector->show();
        }
    }
}

void ToolboxMainWindow::on_actionHough_Transformation_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            HoughTransformation  *houghTransformation = new HoughTransformation(secondImage);
            houghTransformation->show();
        } else {
            HoughTransformation  *houghTransformation = new HoughTransformation(firstImage);
            houghTransformation->show();
        }
    }
}

void ToolboxMainWindow::on_actionAffine_Transformations_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            AffineTransformation  *affTrans = new AffineTransformation(secondImage);
            affTrans->show();
        } else {
            AffineTransformation  *affTrans = new AffineTransformation(firstImage);
            affTrans->show();
        }
    }
}

void ToolboxMainWindow::on_actionHistogram_Equalization_triggered()
{
    if (firstImage.empty() && secondImage.empty()){
        QMessageBox::warning(this, "No Image Found", "Load at least one image to proceed");
    } else {
        if (firstImage.empty()) {
            HistogramEqualization  *histEq = new HistogramEqualization(secondImage);
            histEq->show();
        } else {
            HistogramEqualization  *histEq = new HistogramEqualization(firstImage);
            histEq->show();
        }
    }
}



void ToolboxMainWindow::on_actionBack_Projection_triggered()
{
    BackProjection *bp = new BackProjection(firstImage);
    bp->show();
}
