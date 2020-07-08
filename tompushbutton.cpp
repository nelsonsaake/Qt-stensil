#include "tompushbutton.h"
#include "ui_tompushbutton.h"

TomPushButton::TomPushButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TomPushButton)
{
    ui->setupUi(this);
}

TomPushButton::~TomPushButton()
{
    delete ui;
}
