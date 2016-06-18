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
    kernel_size =  QInputDialog::getText(this, "Enter Kernel Size", "Enter Row , Column comma separated i.e -> 3, 3", QLineEdit::EchoMode::Normal, dummy, &ok, Qt::Dialog);

    if (ok){


        QStringList k_size;
        k_size << kernel_size.split(',');
        krow = k_size.at(0).toInt();
        kcol = k_size.at(1).toInt();

        qDebug() << "row : " << krow;
        qDebug() << "col : " << kcol;

        kernelTableWidget->setColumnCount(kcol);
        kernelTableWidget->setRowCount(krow);

        QVBoxLayout *tableLayout = new QVBoxLayout(kernelTableDialog);

        tableLayout->addWidget(kernelTableWidget);
        tableLayout->addWidget(doneButton);

        kernelTableDialog->setLayout(tableLayout);
        kernelTableDialog->show();

    }
}

void CustomFilter::closeKernelTable(int done)
{
    delete kernelTableDialog->layout();
}

void CustomFilter::getKernelMatrix(bool done)
{
    qDebug() << done;

    int kernel_values[krow * kcol];

    int kernel_values_iter = 0;

    qDebug() << kernelTableWidget->currentItem()->text() << " enabled or not";

    for (int i = 0; i < krow; i++){
        for (int j = 0; j < kcol; j++){
            kernel_values[kernel_values_iter] = kernelTableWidget->item(i, j)->text().toInt();
            kernel_values_iter++;
        }
    }


    int i = 0;
    Mat_<char> kerChar(krow, kcol);

    for (Mat_<char>::iterator iter = kerChar.begin(); iter != kerChar.end(); iter++, i++){
        *iter = kernel_values[i];
    }

    cout << kerChar << endl;


    kernelTableWidget->clear();
    kernelTableDialog->close();
    //Deleting the layout after the work is done
    delete kernelTableDialog->layout();

}
