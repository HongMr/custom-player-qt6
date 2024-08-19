#include "ctrlbar.h"
#include "ui_ctrlbar.h"

#include <QDebug>


CtrlBar::CtrlBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CtrlBar)
{
    ui->setupUi(this);
}

CtrlBar::~CtrlBar()
{
    delete ui;
}

void CtrlBar::on_playOrpauseBtn_clicked()
{
    qDebug()<<" on_playOrpauseBtn_clicked ";
    emit SigPlayOrPause();
}


void CtrlBar::on_stopBtn_clicked()
{
    qDebug()<<" on_stopBtn_clicked ";
    emit SigStop();
}

