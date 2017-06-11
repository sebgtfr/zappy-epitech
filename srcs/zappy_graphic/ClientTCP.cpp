//
// Client.cpp for server in /home/le-mai_s/librairie/librairie_cpp/libmysocket
//
// Made by Sébastien Le Maire
// Login   <le-mai_s@epitech.net>
//
// Started on  Sun Apr 24 21:13:02 2016 Sébastien Le Maire
// Last update Sun Jun 26 23:12:16 2016 Sébastien Le Maire
//

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "ClientTCP.hpp"

namespace			TCP
{
  Client::Client(void) : TCP::Socket(), m_welcome(false)
  {
  }

  Client::Client(Client const &copy) : TCP::Socket(copy), m_port(copy.m_port),
				       m_read(copy.m_read), m_write(copy.m_write),
				       m_except(copy.m_except), m_tv(copy.m_tv),
				       m_buffer(copy.m_buffer),
				       m_send(copy.m_send),
				       m_msgOutput(copy.m_msgOutput),
				       m_welcome(copy.m_welcome)
  {
  }

  Client	       		&Client::operator=(Client const &other)
  {
    if (&other != this)
      {
        Socket::operator=(other);
	this->m_port = other.m_port;
	this->m_read = other.m_read;
	this->m_write = other.m_write;
	this->m_except = other.m_except;
	this->m_tv = other.m_tv;
	this->m_buffer = other.m_buffer;
	this->m_send = other.m_send;
	this->m_msgOutput = other.m_msgOutput;
	this->m_welcome = other.m_welcome;
      }
    return (*this);
  }

  Client::~Client()
  {
  }

  /*
  ** Methods
  */
  bool				Client::init(uint16_t port,
					     std::string const &addressHost)
  {
    unsigned long int		ip;
    struct hostent		*host;
    struct protoent		*pe;

    this->m_port = port;
    if ((!(pe = ::getprotobyname("TCP"))) ||
	((this->m_fd = ::socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1))
      return (false);
    if ((ip = ::inet_addr(addressHost.c_str())) ==
	static_cast<unsigned long int>INADDR_NONE)
      {
        if (!(host = ::gethostbyname(addressHost.c_str())))
	  return (false);
	this->m_sockaddr.sin_family = host->h_addrtype;
	::memcpy(&this->m_sockaddr.sin_addr, host->h_addr, host->h_length);
      }
    else
      {
	this->m_sockaddr.sin_addr.s_addr = ip;
	this->m_sockaddr.sin_family = AF_INET;
      }
    this->m_sockaddr.sin_port = htons(this->m_port);
    if (::connect(this->m_fd,
		  reinterpret_cast<struct sockaddr const *>(&this->m_sockaddr),
		  sizeof(struct sockaddr_in)) < 0)
      return (false);
    this->m_connection = Socket::CONNECTED;
    return (true);
  }

  bool				Client::initSelect(void)
  {
    if (this->m_connection == TCP::Socket::CONNECTED)
      {
	FD_ZERO(&this->m_read);
	FD_ZERO(&this->m_write);
	FD_ZERO(&this->m_except);
	FD_SET(0, &this->m_read);
	FD_SET(1, &this->m_write);
	FD_SET(this->m_fd, &this->m_read);
	FD_SET(this->m_fd, &this->m_write);
	FD_SET(this->m_fd, &this->m_except);
	this->m_tv.tv_sec = 0;
	this->m_tv.tv_usec = 1;
      }
    else
      return (false);
    return (true);
  }

  void				Client::readOnSocket(void)
  {
    this->receiveData(this->m_fd, this->m_buffer);
    if (this->m_connection == TCP::Socket::CONNECTED)
      {
	if ((!this->m_welcome) && (this->m_buffer == "BIENVENUE\n"))
	  {
	    this->m_send = "GRAPHIC\n";
	    this->m_welcome = true;
	  }
	else
	  this->m_msgOutput = this->m_buffer;
      }
  }

  void				Client::writeOnSocket(void)
  {
    if (!this->m_send.empty())
      {
	this->sendData(this->m_fd, this->m_send.c_str(), this->m_send.size());
	this->m_send.clear();
      }
  }

  void				Client::readOnInput(void)
  {
    std::getline(std::cin, this->m_send);
    this->m_send.push_back('\n');
  }

  void				Client::writeOnOutput(void)
  {
    if (!this->m_msgOutput.empty())
      {
	std::cout << "Commande = " << this->m_msgOutput;
        this->m_msgOutput.clear();
      }
  }

  void				Client::action(void)
  {
    this->m_buffer.clear();
  }

  void				Client::launch(void)
  {
    int				max = this->m_fd;

    while (this->initSelect())
      {
	if (select(max + 1, &this->m_read, &this->m_write, &this->m_except,
		   &this->m_tv) == -1)
	  {
	    std::cerr << "Error: select failed !" << std::endl;
	    return ;
	  }
	if (FD_ISSET(0, &this->m_read))
	  this->readOnInput();
	if (FD_ISSET(1, &this->m_write))
	  this->writeOnOutput();
	if (FD_ISSET(this->m_fd, &this->m_read))
	  this->readOnSocket();
	if (FD_ISSET(this->m_fd, &this->m_write))
	  this->writeOnSocket();
	if (FD_ISSET(this->m_fd, &this->m_except))
	  this->m_connection = TCP::Socket::DISCONNECTED;
	if (this->m_connection == TCP::Socket::CONNECTED)
	  this->action();
      }
  }
}
