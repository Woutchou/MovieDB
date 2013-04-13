#include "moviedisplayinfo.h"
#include "ui_moviedisplayinfo.h"

MovieDisplayInfo::MovieDisplayInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieDisplayInfo)
{
    ui->setupUi(this);
}

MovieDisplayInfo::~MovieDisplayInfo()
{
    delete ui;
}
