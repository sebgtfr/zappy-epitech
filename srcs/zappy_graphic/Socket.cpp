//
// Socket.cpp for Socket in /home/le-mai_s/test/zappy
//
// Made by Sébastien Le Maire
// Login   <le-mai_s@epitech.net>
//
// Started on  Sun Jun 26 21:58:24 2016 Sébastien Le Maire
// Last update Sun Jun 26 21:38:14 2016 Sébastien Le Maire
//

#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "Socket.hpp"

namespace			TCP
{
  Socket::Socket(void) : m_fd(-1), m_connection(TCP::Socket::UNDEFINED)
  {
  }

  Socket::Socket(Socket const &copy) :
    m_fd(copy.m_fd), m_sockaddr(copy.m_sockaddr),
    m_socklen(copy.m_socklen), m_connection(copy.m_connection)
  {
  }

  Socket			&Socket::operator=(Socket const &other)
  {
    if (&other != this)
      {
	this->m_fd = other.m_fd;
	this->m_sockaddr = other.m_sockaddr;
	this->m_socklen = other.m_socklen;
	this->m_connection = other.m_connection;
      }
    return (*this);
  }

  Socket::~Socket(void)
  {
    if (this->m_fd != -1)
      ::close(this->m_fd);
  }

  /*
  ** Methods
  */
  void				Socket::receiveData(int const fd,
						    std::string &data)
  {
    ssize_t		        ret;
    char	       		buffer[1025];

    if (this->m_connection == TCP::Socket::CONNECTED)
      {
	errno = 0;
	while ((ret = ::recvfrom(fd, buffer, 1024, MSG_DONTWAIT,
				 reinterpret_cast<struct sockaddr *>(&this->m_sockaddr),
				 &this->m_socklen)) > 0)
	  {
	    buffer[ret] = '\0';
	    data += buffer;
	  }
	if ((errno != EAGAIN) && (ret == -1) && (errno))
	  this->m_connection = TCP::Socket::DISCONNECTED;
      }
  }

  void				Socket::sendData(int const fd,
						 void const *data,
						 size_t size)
  {
    ssize_t		        ret;
    size_t			msg_send;

    if (this->m_connection == TCP::Socket::CONNECTED)
      {
	errno = 0;
	while ((ret = send(fd, static_cast<char const *>(data) + msg_send,
			   size - msg_send,
			   MSG_NOSIGNAL | MSG_DONTWAIT) > 0))
	  msg_send += ret;
	if (errno != EAGAIN && errno != EWOULDBLOCK && errno && ret == -1)
	  this->m_connection = TCP::Socket::DISCONNECTED;
      }
  }

  /*
  ** Inherits Accessor
  */
  int				Socket::getFd(void) const
  {
    return (this->m_fd);
  }

  Socket::Connection		Socket::getConnection(void) const
  {
    return (this->m_connection);
  }

  void				Socket::setDisconnection(void)
  {
    this->m_connection = TCP::Socket::DISCONNECTED;
  }
}
