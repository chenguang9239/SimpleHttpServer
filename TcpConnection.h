/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#ifndef SIMPLE_HTTP_TCPCONNECTION_H
#define SIMPLE_HTTP_TCPCONNECTION_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <error.h>
#include "Channel.h"
#include "Buffer.h"
#include "TcpConnection.h"


class EventLoop;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
	//typedef std::function< void(TcpConnction*,Buffer*) > MessageCallback;
	//typedef std::function< void(void*) > MessageCallback;

	typedef std::function<void(std::shared_ptr<TcpConnection>)> MessageCallback;
	typedef std::function<void(int)> CloseCallback;

	TcpConnection( EventLoop* loop, int sockfd );
	~TcpConnection();

	void setMessageCallback( const MessageCallback& cb )
	{
		messageCallBack_ = cb;
	}
	void setCloseCallback( const CloseCallback& cb )
	{
		closeCallBack_ = cb;
	}

	void completeConnection()
	{
		channel_->setWeakTcpConnectionPtr( shared_from_this() );

	    //通过channel_设置读的感兴趣事件
	    channel_->enableReading();
	}

	void send( std::string& message );
	Buffer* getInputBuffer(){ return &inputBuffer_; }

private:
	void handleRead();
	void handleWrite();

	void handleClose();
	void handleError();

	MessageCallback messageCallBack_;
	CloseCallback closeCallBack_;

	EventLoop* loop_;
	std::unique_ptr<Channel> channel_;

	Buffer inputBuffer_;
	Buffer outputBuffer_;
};

#endif // SIMPLE_HTTP_TCPCONNECTION_H
