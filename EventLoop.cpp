/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include "EventLoop.h"
#include "Epoll.h"

//#define gettid() syscall( __NR_gittid )

EventLoop::EventLoop()
    ://isLooping_( false ),
     //threadId_( gettid() ),
     isQuit_( false ),
     ep_( new Epoll( this ) )
{ }

EventLoop::~EventLoop()
{
    //assert(!isLooping);
}

void EventLoop::loop()
{
    //assert( !isLooping_ );
    //isLooping_ = true;
    isQuit_ = false;

    while( !isQuit_ )
    {
        std::cout << "----------Looping----------" << std::endl;

		activeChannels_.clear();
		ep_->epWait( &activeChannels_ );

        for( ChannelVector::iterator iter = activeChannels_.begin();
            iter != activeChannels_.end(); iter++ )
        {
            std::cout << "------epoll_wait returns, call handleEvent------" << std::endl;

            (*iter)->handleEvent();
            //e->removeFd((*iter)->connFd());
            //delete *iter;
        }
    }
    //isLooping_ = false;
}

void EventLoop::quit()
{
    isQuit_ = true;
}

void EventLoop::updateChannel( Channel* channel )
{
	ep_->updateChannel( channel );
    //std::cout << "----------Add " << channel->getFd() << " to loop----------" << std::endl;
}

void EventLoop::removeChannel( Channel* channel )
{
	//判断是否在handling，待续
	ep_->removeChannel( channel );
}

