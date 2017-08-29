/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#ifndef SIMPLE_HTTP_EVENTLOOP_H
#define SIMPLE_HTTP_EVENTLOOP_H

#include <functional>
#include <memory>
//#include <sys/syscall.h>
//#include <sys/types.h>
//#include <assert.h>
#include <vector>
//#include <poll.h>
//#include <signal.h>
//#include "Epoll.h"
//#include "CurrentThread.h"

class Channel;
class Epoll;
///EventLoop.cpp有调用Epoll中成员函数

class EventLoop 
{
public:
	typedef std::vector<Channel*> ChannelVector;
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();

	void updateChannel( Channel* channel );
	void removeChannel( Channel* channel );

private:
    //bool isLooping_;
    //const pid_t threadId_; //感觉没有必要
    bool isQuit_;
	std::unique_ptr< Epoll > ep_;
	ChannelVector activeChannels_;
};

#endif // SIMPLE_HTTP_EVENTLOOP_H
