/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include <iostream>
#include <cstdlib>
#include "Socket.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "EventLoopThreadPool.h"
#include "HttpServer.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return 0;
    }
    int port = std::atoi(argv[1]);

	//创建4个IO线程（sub reactor），并启动loop()
	//此时每个线程的epoll中，没有监听的套接字
    EventLoopThreadPool *threadPool = new EventLoopThreadPool(4);
	
	//创建main reactor
    struct sockaddr_in servAddr;
    memset( &servAddr, 0, sizeof(servAddr) );
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons( port );
	
	EventLoop acceptLoop;

	HttpServer httpServer( &acceptLoop, &servAddr, threadPool );
	acceptLoop.loop();

    delete threadPool;
    return 0;
}
