/*
 * Author: chenguang9239
 * E-mail: wangzhiyiiiii@163.com
*/

#include "Buffer.h"

size_t Buffer::readFd(const int fd)
{
    char extrabuf[65535];
    char *ptr = extrabuf;
    int nleft = 65535;
    int nread;
    while( ( nread = Socket::Read( fd, ptr, nleft ) ) < 0)
    {
        if( errno == EINTR )
            nread = 0;
        else 
            return 0;
    }
    append( extrabuf, nread );
    return nread;
}

//这个函数会阻塞当前IO线程，弃用
void Buffer::sendFd(const int fd)
{
    size_t bytesSent = 0;
    size_t bytesLeft = readableBytes();
    char *ptr = peek();
    while(bytesLeft)
    {
        if((bytesSent = write(fd, ptr, bytesLeft)) < 0)
        {
            if(bytesSent < 0 && errno == EINTR)
                bytesSent = 0;
            else
                return;
        }
        bytesLeft -= bytesSent;
        ptr += bytesSent;
    } 
    resetBuffer();
}
