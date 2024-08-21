#include "mainwind.h"
#include "./ui_mainwind.h"

#include <QDebug>
#include <thread>
#include <functional>
#include <iostream>

#include "custom_log/custom_log.h"

MainWind::MainWind(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWind)
{
    ui->setupUi(this);

    CustomLog::GetTheInstance().SetLevel(Level::DEBUG);

}

MainWind::~MainWind()
{
    delete ui;
}

void MainWind::OnPlayOrPause()
{

}



void MainWind::OnStop()
{

}
