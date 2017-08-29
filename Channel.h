/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#ifndef SIMPLE_HTTP_CHANNEL_H
#define SIMPLE_HTTP_CHANNEL_H

#include <sys/epoll.h>
#include <functional>
#include <memory>
#include "EventLoop.h"

class TcpConnection;

class Channel
{
public:
	typedef std::function<void()> EventCallback;
	//typedef std::function< void() > ReadEventCallback;

	Channel( EventLoop* loop, int fd );
	~Channel();

	void handleEvent();

	//inline member function
	//注册回调函数
	void setReadCallback( const EventCallback& cb )
	{ readCallback_ = cb;	}
	
	void setWriteCallback( const EventCallback& cb )
	{ writeCallback_ = cb;	}

	void setCloseCallback( const EventCallback& cb )
	{ closeCallback_ = cb;	}

	void setErrorCallback( const EventCallback& cb )
	{ errorCallback_ = cb;	}
	
	//
	int getFd() const { return fd_; }

	int getEvents() const { return events_; }

	void setREvents( int revents ) { rEvents_ = revents; }

	EventLoop* getEventLoop() const { return loop_; }

	//设置感兴趣的事件
	void enableReading() { events_ |= EPOLLIN; update(); }

	void enableWriting() { events_ |= EPOLLOUT; update(); }

	void setWeakTcpConnectionPtr( std::shared_ptr<TcpConnection> p )
	{
		weakTcpConnectionPtr_ = p;
	}

	void remove( Channel* p )
	{
		loop_->removeChannel( p );
	}

private:
    //EventLoop *loopBelongsTo;
	//const int fdResponsibleFor;
    EventLoop *loop_;
	const int fd_;
	int events_;
	int rEvents_;
	std::weak_ptr<TcpConnection> weakTcpConnectionPtr_;

	EventCallback readCallback_;
	EventCallback writeCallback_;
	EventCallback closeCallback_;
	EventCallback errorCallback_;

	//将感兴趣的事件，设置（注册）到epoll中（其实是通过调用EventLoop的函数）
	void update();

};

#endif // SIMPLE_HTTP_CHANNEL_H
