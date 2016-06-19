#include "customfilter.h"
#include "ui_customfilter.h"

CustomFilter::CustomFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomFilter)
{
    ui->setupUi(this);

    kernelTableDialog = new QDialog;
    doneButton = new QPushButton("Done");
    kernelTableWidget = new QTableWidget;

    connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(getKernelMatrix(bool)));
    connect(kernelTableDialog, SIGNAL(finished(int)), this, SLOT(closeKernelTable(int)));

}

CustomFilter::CustomFilter(Mat img): originalImage(img), ui(new Ui::CustomFilter)
{
    ui->setupUi(this);

    kernelTableDialog = new QDialog;
    doneButton = new QPushButton("Done");
    kernelTableWidget = new QTableWidget;

    connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(getKernelMatrix(bool)));
    connect(kernelTableDialog, SIGNAL(finished(int)), this, SLOT(closeKernelTable(int)));

    //Loading image
    ui->image->setPixmap(ImageHandler::getQPixmap(originalImage));
    ui->imageScrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);

    ui->getKernelButton->setEnabled(false);

    setWindowTitle("Apply Custom Kernel");
}

CustomFilter::~CustomFilter()
{
    delete doneButton;
    delete kernelTableDialog;
    delete kernelTableWidget;
    delete ui;
}

void CustomFilter::on_createKernelButton_clicked()
{
    bool ok;
    QString kernel_size;
    QString dummy;
    kernel_size =  QInputDialog::getText(this, "Enter Kernel Size (odd numbers only)", "Enter Row , Column comma separated i.e -> 3, 3", QLineEdit::EchoMode::Normal, dummy, &ok, Qt::Dialog);

    if (ok){
        QStringList k_size;
        k_size << kernel_size.split(',');
        krow = k_size.at(0).toInt();
        kcol = k_size.at(1).toInt();

        qDebug() << "row : " << krow;
        qDebug() << "col : " << kcol;

        if (krow % 2 == 0 && krow != 0) krow--;
        if (kcol % 2 == 0 && kcol != 0) kcol--;

        kernelTableWidget->setColumnCount(kcol);
        kernelTableWidget->setRowCount(krow);

        QVBoxLayout *tableLayout = new QVBoxLayout(kernelTableDialog);

        tableLayout->addWidget(kernelTableWidget);
        tableLayout->addWidget(doneButton);

        //Fills the tablewidget with 0s
        for (int i = 0; i < krow; i++){
            for (int j = 0; j < kcol; j++){
                kernelTableWidget->setItem(i, j, new QTableWidgetItem("0"));
            }
        }

        kernelTableWidget->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
        kernelTableDialog->setWindowModality(Qt::ApplicationModal);
        kernelTableDialog->setLayout(tableLayout);
        kernelTableDialog->setMinimumSize(kernelTableWidget->sizeHint());
        kernelTableDialog->show();
    } else {
        QMessageBox::warning(this, "Create a kernel to begin", "No kernel found, create one");
    }
}

void CustomFilter::closeKernelTable(int done)
{
    delete kernelTableDialog->layout();
}

void CustomFilter::getKernelMatrix(bool done)
{
    //Enabling getkernel
    ui->getKernelButton->setEnabled(true);
    appliedKernel.clear();

    //Kernel value array
    int kernel_values[krow * kcol];

    //Iterator counter
    int kernel_values_iter = 0;

    //Getting value from tablewidget
    for (int i = 0; i < krow; i++){
        for (int j = 0; j < kcol; j++){
            appliedKernel.append(kernelTableWidget->item(i, j)->text() + "\t");
            kernel_values[kernel_values_iter] = kernelTableWidget->item(i, j)->text().toInt();
            kernel_values_iter++;
        }
        appliedKernel.append('\n');
    }

    int i = 0;
    Mat_<char> kernel_(krow, kcol);

    for (Mat_<char>::iterator iter = kernel_.begin(); iter != kernel_.end(); iter++, i++){
        *iter = kernel_values[i];
    }

    kernel = {kernel_};

    cout << kernel << endl;

    //Applying custom kernel
    filter2D(originalImage, image, originalImage.depth(), kernel);
    ui->image->setPixmap(ImageHandler::getQPixmap(image));

    //Removing remaining parts
    kernelTableWidget->clear();
    kernelTableDialog->close();
    //Deleting the layout after the work is done
    delete kernelTableDialog->layout();

}

void CustomFilter::on_autoScaleCheckBox_clicked(bool checked)
{
    ui->image->setScaledContents(checked);
}

void CustomFilter::on_getKernelButton_clicked()
{
    QMessageBox::information(this, "Applied Kernel", appliedKernel);
}
