#include "ijkmediaplayer.h"

IjkMediaPlayer::IjkMediaPlayer() {}

int IjkMediaPlayer::ijkmp_create(std::function<int (void *)> msg_loop)
{
    int ret = 0;
    m_msg_loop_ = msg_loop;

    return ret;
}

int IjkMediaPlayer::ijkmp_destroy()
{
    int ret = 0;

    return ret;
}
