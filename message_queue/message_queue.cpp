#include "message_queue.h"



void msg_init_msg(AVMessage *msg)
{
    memset(msg,0,sizeof(AVMessage));
}

void msg_free_res(AVMessage *msg)
{
    if(!msg || !msg->obj)
        return;
    msg->free_l(msg->obj);
    msg->obj = NULL;
}

void msg_queue_init(MessageQueue *q)
{
    memset(q,0,sizeof(MessageQueue));
    q->mutex = new std::mutex();
    q->abort_request = 1;
}

void msg_queue_flush(MessageQueue *q)
{
    AVMessage *msg,*msg1;
    q->mutex->lock();
    for(msg = q->first_msg; msg != NULL; msg = msg1)
    {
        msg1 = msg->next;
        msg->next = q->recycle_msg;
        q->recycle_msg = msg;
    }

    q->last_msg = NULL;
    q->first_msg = NULL;
    q->nb_messages = 0 ;
    q->mutex->unlock();
}

void msg_queue_destroy(MessageQueue *q)
{
    msg_queue_flush(q);
    q->mutex->lock();
    while(q->recycle_msg)
    {
        AVMessage *msg = q->recycle_msg;
        if(msg)
            q->recycle_msg = msg->next;
        msg_free_res(msg);
        free(msg);
    }
    q->mutex->unlock();

    delete q->mutex;
}
