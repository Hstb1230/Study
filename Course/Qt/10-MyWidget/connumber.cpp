#include "connumber.h"
#include "ui_connumber.h"

ConNumber::ConNumber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConNumber)
{
    ui->setupUi(this);

    void (QSpinBox:: * spinBoxChange)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, spinBoxChange, ui->horizontalSlider, &QSlider::setValue);

    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

ConNumber::~ConNumber()
{
    delete ui;
}

int ConNumber::getNumber()
{
    return ui->spinBox->value();
}

void ConNumber::setNumber(int value)
{
    ui->spinBox->setValue(value);
}
