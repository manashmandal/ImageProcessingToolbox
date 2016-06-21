#ifndef MORPHOLOGYTRANSFORMATION_H
#define MORPHOLOGYTRANSFORMATION_H

#include "../imagehandler.h"


namespace Ui {
class MorphologyTransformation;
}

class MorphologyTransformation : public QWidget
{
    Q_OBJECT

public:
    explicit MorphologyTransformation(QWidget *parent = 0);
    explicit MorphologyTransformation(Mat img);
    ~MorphologyTransformation();

private slots:
    void on_scaleCheckBox_clicked(bool checked);

    void on_kSizeSlider_sliderMoved(int position);

    void on_operationComboBox_currentIndexChanged(const QString &arg1);

    void on_structElmComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MorphologyTransformation *ui;

    Mat image;
    Mat originalImage;
    //Kernel matrix
    Mat element;

    int ksize;

private:
    void operate(QString operation);
};

#endif // MORPHOLOGYTRANSFORMATION_H
