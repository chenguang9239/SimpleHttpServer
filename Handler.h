#ifndef SIMPLE_HTTP_HANDLER_H
#define SIMPLE_HTTP_HANDLER_H

#include <string>
#include <algorithm>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Parser.h"
#include "Buffer.h"
#include "TcpConnection.h"
#include <memory>

class Handler 
{
public:
    Handler();
    ~Handler();
    void handle();
	void setTcpConnectionPtr( std::shared_ptr<TcpConnection> p )
	{ tcpConnectionPtr = p; }

private:
    bool receiveRequest();  // 接受客户的请求并解析
    //void sendResponse();    // 发送相应
    void sendErrorMsg(const std::string &errorNum,
                      const std::string &shortMsg,
                      const std::string &longMsg);
    void parseURI();
    void getFileType();
    //int _connfd;
    bool _isClosed;
    std::string _fileType;
    std::string _fileName;
    //Buffer _inputBuffer;
    //Buffer _outputBuffer;
    HTTPRequest _request;
	std::weak_ptr<TcpConnection> tcpConnectionPtr;
};

#endif // SIMPLE_HTTP_HANDLER_H
