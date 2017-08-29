/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#ifndef SIMPLE_HTTP_HTTPSERVER_H
#define SIMPLE_HTTP_HTTPSERVER_H

//#include <unistd.h>
#include <iostream>
#include <memory>
//#include "Acceptor.h"
#include "Handler.h"
#include "TcpConnection.h"
#include "EventLoopThreadPool.h"
#include <map>


//用到了这两个类
class EventLoop;
class EventLoopThread;
class Acceptor;

class HttpServer
{
public:
	HttpServer( EventLoop* loop, struct sockaddr_in* listenAddr, EventLoopThreadPool* threadPollPtr );
	~HttpServer();

	//收到一条完整消息时的处理函数
	//void setMessageCallBack( const MessageCallback& cb )
	//{ messageCallBack_ = cb; }

	//Acceptor的回调函数，收到消息（新连接）调用
	void newConnection( int sockfd );

	//TcpConnection的回调函数，收到消息时调用
	void onMessage( std::shared_ptr<TcpConnection> p );
	void onClose( int connfd );

private:
    EventLoop* loop_;
	std::unique_ptr< Acceptor > acceptor_;
	//unique< EventLoopThreadPool > threadPoll_;
	EventLoopThreadPool* threadPoolPtr_;
	Handler handleRequest_;
	std::map< int, std::shared_ptr<TcpConnection> > connMap_;
};

#endif // SIMPLE_HTTP_HTTPSERVER_H
