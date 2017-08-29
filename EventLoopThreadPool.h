#ifndef SIMPLE_HTTP_EVENTLOOPTHREADPOOL_H
#define SIMPLE_HTTP_EVENTLOOPTHREADPOOL_H

#include <vector>
#include "EventLoopThread.h"

class EventLoop;

class EventLoopThreadPool
{
public:
    EventLoopThreadPool( const int threadNum );
    ~EventLoopThreadPool();
    EventLoopThread* getNextThread();

private:
    int _threadNum;
    int _nextID;
    EventLoop *_baseLoop;
    std::vector< EventLoopThread* > _threads;
};

#endif // SIMPLE_HTTP_EVENTLOOPTREADPOOL_H
