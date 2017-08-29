/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include "Channel.h" 
#include <sys/epoll.h>
#include <EventLoop.h>
#include <iostream>
#include "Socket.h"

Channel::Channel( EventLoop* loop, int fd )
	: loop_( loop ), fd_( fd ), events_( 0 ), rEvents_( 0 )
{
}

Channel::~Channel()
{
	//std::cout << "~Channel()" << std::endl;
	remove( this );
	//关闭fd
	Socket::Close( fd_ );
}

void Channel::update()
{
    loop_->updateChannel( this );
}

//对于各种标志的含义，待修改
void Channel::handleEvent()
{
	//局部变量，保证TcpConnection在析构在hanndelEvent返回之后
	std::shared_ptr<TcpConnection> guard = weakTcpConnectionPtr_.lock();

	if( rEvents_ & EPOLLIN )
	{
		if( readCallback_ ) { readCallback_(); }
	}
	return;
	if( rEvents_ & EPOLLOUT )
	{
		if( writeCallback_ ) writeCallback_();
	}
	return;
	if( rEvents_ & EPOLLHUP )
	{
		if( closeCallback_ ) closeCallback_();
	}
	return;
}
