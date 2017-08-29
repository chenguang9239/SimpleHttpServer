/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include "Epoll.h"
#include <unistd.h>
#include <string.h>

Epoll::Epoll( EventLoop* loop )
	: loop_ ( loop ),
	  epollfd_( epoll_create1( EPOLL_CLOEXEC ) ),
	  rEvents_( 16 )
{
	if( epollfd_ < 0 )
	{
		std::cout << "Epoll::Epoll( EventLoop* loop )EventLoop* loop ) error" << std::endl;
	}
}

Epoll::~Epoll()
{
	close( epollfd_ );//头文件？
}

void Epoll::epWait( ChannelVector* activeChannels )
{
    int numEvents = epoll_wait( epollfd_,
                                 rEvents_.data(),
                                 static_cast<int>( rEvents_.size() ),
                                 10000 ); // 设置epoll每10秒返回一次
    if( numEvents < 0 ) 
    {
        if( errno != EINTR )
        { 
            std::cout << "Epoll::epWait( ChannelVector* activeChannels ) error: " << strerror(errno) << std::endl;
            exit(1);
        }
    }
    else if( numEvents == 0 ) 
    {
        //空
    }
    else
    {
		fillEventsToActiveChannels( numEvents, activeChannels );

		//std::cout<< "numEvents: " << numEvents << endl;

		//如果发生事件的FD个数达到了rEvents_的size，就把rEvents_的size加倍，
		//下次就可以得到更多的发生事件的fd
		if( numEvents == rEvents_.size() )
		{
			rEvents_.resize( rEvents_.size() * 2 );
		}
    }
}

//待修改
void Epoll::updateChannel( Channel* channel )
{
	int fd = channel->getFd();
	//判断fd在不在epoll里
	//那么好像不需要用ChnnelMap，用map< int, bool >就行了
	if( channels_[fd] == 0 )
	{
		update( EPOLL_CTL_ADD, channel );

		channels_[fd] = channel;
	}
	else
	{
		update( EPOLL_CTL_MOD, channel );
	}
}

//待修改
void Epoll::removeChannel( Channel* channel )
{
	int fd = channel->getFd();
	update( EPOLL_CTL_DEL, channel );
	
	channels_.erase( fd );
}

void Epoll::update( int operation, Channel* channel )
{
    struct epoll_event event;
	memset( &event, 0, sizeof( event ) );

    event.events = channel->getEvents();
	event.data.ptr = channel;//作用？
	int fd = channel->getFd();

    //event.data.fd = channel->getFd();//多余吗？

    if( epoll_ctl( epollfd_, operation, fd, &event ) < 0 )
	{
        std::cout << "Epoll::update( int operation, Channel* channel ) error: " << std::endl;
	}
}

void Epoll::fillEventsToActiveChannels( int evenNum, ChannelVector* activeChannels ) const
{
	for( int i = 0; i < evenNum; i++ )
	{
		Channel* channel = static_cast< Channel* >( rEvents_[i].data.ptr );
		channel->setREvents( rEvents_[i].events );
		activeChannels->push_back( channel );
	}
}












