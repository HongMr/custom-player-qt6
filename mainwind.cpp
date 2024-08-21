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

    InitSignalsAndSlots();
}

MainWind::~MainWind()
{
    delete ui;
}

int MainWind::InitSignalsAndSlots()
{
    int ret = 0;
    connect(ui->ctrlBarWind,&CtrlBar::SigPlayOrPause,this,&MainWind::OnPlayOrPause);
    connect(ui->ctrlBarWind,&CtrlBar::SigStop,this,&MainWind::OnStop);
    return ret;
}

int MainWind::message_loop(void *arg)
{

}

void MainWind::OnPlayOrPause()
{
    LOG_DEBUG<<"play start";
    if(!m_ijk_media_player_)
    {
        m_ijk_media_player_ = new IjkMediaPlayer();

        m_ijk_media_player_->ijkmp_create(std::bind(&MainWind::message_loop, this, std::placeholders::_1));
    }
}



void MainWind::OnStop()
{
    LOG_DEBUG<<"play stop";
}
