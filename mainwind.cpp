#include "mainwind.h"
#include "./ui_mainwind.h"

#include <QDebug>
#include <thread>
#include <functional>
#include <iostream>


MainWind::MainWind(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWind)
{
    ui->setupUi(this);


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
