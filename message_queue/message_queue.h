#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H
#include <iostream>
#include <mutex>
#include <string.h>

typedef struct AVMessage {
    int what;           // 消息类型
    int arg1;           // 参数1
    int arg2;           // 参数2
    void *obj;          // 如果arg1 arg2还不够存储消息则使用该参数
    void (*free_l)(void *obj);  // obj的对象是分配的，这里要给出函数怎么释放
    struct AVMessage *next; // 下一个消息
} AVMessage;

typedef struct MessageQueue {   // 消息队列
    AVMessage *first_msg, *last_msg;    // 消息头，消息尾部
    int nb_messages;    // 有多少个消息
    int abort_request;  // 请求终止消息队列
    std::mutex *mutex;   // 互斥量
    //std::cond *cond;     // 条件变量

    AVMessage *recycle_msg; // 消息循环使用
    int recycle_count;  // 循环的次数，利用局部性原理
    int alloc_count;    // 分配的次数
} MessageQueue;

// 初始化消息
void msg_init_msg(AVMessage *msg);

void msg_free_res(AVMessage *msg);
// 消息队列初始化
void msg_queue_init(MessageQueue *q);

// 消息队列flush，清空所有的消息
void msg_queue_flush(MessageQueue *q);

// 消息销毁
void msg_queue_destroy(MessageQueue *q);

#endif // MESSAGEQUEUE_H
