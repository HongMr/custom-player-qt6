#ifndef IJKMEDIAPLAYER_H
#define IJKMEDIAPLAYER_H

#include <functional>

class IjkMediaPlayer
{
public:
    IjkMediaPlayer();

    int ijkmp_create(std::function<int(void *)> msg_loop);
    int ijkmp_destroy();

private:
    std::function<int(void *)> m_msg_loop_ = NULL; // ui处理消息的循环
};

#endif // IJKMEDIAPLAYER_H
