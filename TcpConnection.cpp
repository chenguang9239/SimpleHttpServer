/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include "TcpConnection.h"
#include <iostream>

TcpConnection::TcpConnection( EventLoop* loop, int sockfd )
	: loop_( loop ),
	  channel_( new Channel( loop, sockfd ) )
{
	//设置channel_的回调函数
	channel_->setReadCallback( std::bind( &TcpConnection::handleRead, this ) );
	channel_->setWriteCallback( std::bind( &TcpConnection::handleWrite, this ) );
	channel_->setCloseCallback( std::bind( &TcpConnection::handleClose, this ) );
	//ERROR!!!
	//channel_->setWeakTcpConnectionPtr( shared_from_this() );

	//通过channel_设置读的感兴趣事件
	//channel_->enableReading();
}

//这里要将channel从Epoll中移除
TcpConnection::~TcpConnection()
{
	//std::cout<< "~TcpConnection()" << std::endl;
}

	
//发送数据
//数据可能是先到Buffer缓冲区，再到内核缓冲区
void TcpConnection::send( std::string& message )
{
	//如果输出缓冲区为空，直接调用write发送
	int wroteNum = 0;
	int len = message.size();
	if( outputBuffer_.readableBytes() == 0 )
	{
		wroteNum = Socket::Write( channel_->getFd(), message.data(), len );	
		
		//write不正常
		if( wroteNum < 0 )
		{
			if( errno != EWOULDBLOCK )
			{
				std::cout << "TcpConnection::send( std::string* message ) error" << std::endl;
				//exit( 1 );
			}
		}
	}

	//没有全部write，或者缓冲区中还有数据排队，需要把剩余的加入缓冲区
	int remain = len - wroteNum;
	if( remain > 0 )
	{
		outputBuffer_.append( (char*)message.data() + wroteNum, message.size() );

		//通过channel设置可写事件感兴趣
		channel_->enableWriting();
	}
}
				   

//数据到来
//数据是先到内核缓冲区，再到Buffer缓冲区
void TcpConnection::handleRead()
{
	//int savedErrno = 0;
	//根据read到的数据长度，判断是否为关闭连接
	//将内核缓冲区中的数据读到Buffer
	//int n = inputBuffer_.readFd( channel_->getFd(), &savedErrno )

	int n = inputBuffer_.readFd( channel_->getFd() );
	if( n > 0 )
	{
		//这个回调会判断是否为一个完整的消息，并处理
		//由HTTPSEVER注册
		//std::cout << "messageCallBack_() " << std::endl;

		messageCallBack_( shared_from_this() );
	}	
	else if( n == 0 )
	{
		handleClose();
	}
	else
	{
		handleError();
	}
}

void TcpConnection::handleClose()
{
	//std::cout << "TcpConnection::handleClose()" << std::endl;

	closeCallBack_( channel_->getFd() );
}

void TcpConnection::handleError()
{
}

//把缓冲区内的数据发送出去的函数
void TcpConnection::handleWrite()
{
	int wroteNum = Socket::Write( channel_->getFd(), 
				outputBuffer_.peek(), outputBuffer_.readableBytes() );
	if( wroteNum > 0 )
	{
		outputBuffer_.retrieve( wroteNum );
	}
	else
	{
		//write出错
		if( wroteNum < 0 )
		{
			if( errno != EWOULDBLOCK )
			{
				std::cout << "TcpConnection::send( std::string* message ) error" << std::endl;
				//exit( 1 );
			}
		}

	}
}











