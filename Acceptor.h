/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#ifndef SIMPLE_HTTP_ACCEPT_H
#define SIMPLE_HTTP_ACCEPT_H

#include <netinet/in.h>
#include <functional>
#include "Channel.h"


//用到了这两个类
class EventLoop;

class Acceptor
{
public:
	//typedef function< void( int sockfd, struct sockaddr* ) > NewConnCallback;
	typedef std::function<void(int sockfd)> NewConnCallback;

	Acceptor( EventLoop* loop, struct sockaddr_in* listenAddr );
	~Acceptor();

	//由HttpServer来注册
	//将新连接分配到一个IO线程处理
	//即给一个新TcpConnection分配一个EventLoop
	void setNewConnCallback( const NewConnCallback& cb )
	{
		newConnCallback_ = cb;
	}

private:
	EventLoop* loop_;
	//Socket acceptSocket_;
	int acceptFd_;
	Channel acceptChannel_;
	NewConnCallback newConnCallback_; //把新连接分到不同的IO线程中

	void handleRead();
};

#endif // SIMPLE_HTTP_ACCEPT_H
