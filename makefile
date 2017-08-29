all:RunHttpServer

#files1 = Acceptor.cpp EventLoop.cpp httpMainFunc.cpp Socket.cpp Buffer.cpp EventLoopThread.cpp HttpServer.cpp TcpConnection.cpp Channel.cpp EventLoopThreadPool.cpp Parser.cpp Thread.cpp Epoll.cpp Handler.cpp

files = Acceptor.o EventLoop.o httpMainFunc.o Socket.o Buffer.o EventLoopThread.o HttpServer.o TcpConnection.o Channel.o EventLoopThreadPool.o Parser.o Thread.o Epoll.o Handler.o

Epoll.o: Epoll.cpp Epoll.h
	g++ -std=c++11 -I. -c Epoll.cpp

Socket.o: Socket.cpp Socket.h
	g++ -std=c++11 -I. -c Socket.cpp

Channel.o: Channel.cpp Channel.h
	g++ -std=c++11 -I. -c Channel.cpp
   
EventLoop.o: EventLoop.cpp EventLoop.h
	g++ -std=c++11 -I. -c EventLoop.cpp

Acceptor.o: Acceptor.cpp Acceptor.h
	g++ -std=c++11 -I. -c Acceptor.cpp

TcpConnection.o: TcpConnection.cpp TcpConnection.h
	g++ -std=c++11 -I. -c TcpConnection.cpp

Buffer.o: Buffer.cpp Buffer.h
	g++ -std=c++11 -I. -c Buffer.cpp

Thread.o: Thread.cpp Thread.h
	g++ -std=c++11 -I. -c -pthread Thread.cpp

EventLoopThread.o: EventLoopThread.cpp EventLoopThread.h
	g++ -std=c++11 -I. -c EventLoopThread.cpp

EventLoopThreadPool.o: EventLoopThreadPool.cpp EventLoopThread.h
	g++ -std=c++11 -I. -c -pthread EventLoopThreadPool.cpp EventLoopThread.cpp

Parser.o: Parser.cpp Parser.h
	g++ -std=c++11 -I. -c Parser.cpp

Handler.o: Handler.cpp Handler.h Parser.h
	g++ -std=c++11 -I. -c Handler.cpp Parser.cpp

httpMainFunc.o: httpMainFunc.cpp
	g++ -std=c++11 -I. -c httpMainFunc.cpp

HttpServer.o: HttpServer.cpp HttpServer.h
	g++ -std=c++11 -I. -c HttpServer.cpp

RunHttpServer: $(files)
	g++ -std=c++11 -pthread -o RunHttpServer -I. $(files)


clean:
	rm *.o RunHttpServer
