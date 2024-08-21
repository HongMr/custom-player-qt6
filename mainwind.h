#ifndef MAINWIND_H
#define MAINWIND_H

#include <QMainWindow>
#include "ijkmediaplayer/ijkmediaplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWind;
}
QT_END_NAMESPACE

class MainWind : public QMainWindow
{
    Q_OBJECT

public:
    MainWind(QWidget *parent = nullptr);
    ~MainWind();
    int InitSignalsAndSlots();
    int message_loop(void *arg);

private:
    Ui::MainWind *ui;
    IjkMediaPlayer *m_ijk_media_player_ = NULL;

private slots:
    void OnPlayOrPause();
    void OnStop();
};
#endif // MAINWIND_H
