//
// Socket.hpp for Socket in /home/le-mai_s/test/zappy
//
// Made by Sébastien Le Maire
// Login   <le-mai_s@epitech.net>
//
// Started on  Sun Jun 26 21:58:16 2016 Sébastien Le Maire
// Last update Sun Jun 26 21:58:17 2016 Sébastien Le Maire
//

#ifndef ASOCKET_HPP_
# define ASOCKET_HPP_

# include <netinet/in.h>
# include <string>

namespace				TCP
{
  class					Socket
  {
  public:
    enum				Connection
      {
	CONNECTED,
	DISCONNECTED,
	UNDEFINED
      };

  public: /* ctor & dtor on canonics form */
    Socket(void);
    Socket(Socket const &copy);
    virtual Socket	      		&operator=(Socket const &other);
    virtual				~Socket(void);

  public: /* Inherits Methods */
    virtual void			receiveData(int const fd,
						    std::string &data);
    virtual void			sendData(int const fd, void const *data,
						 size_t size);

  public: /* Inherits Accessor */
    virtual int			        getFd(void) const;
    virtual Socket::Connection		getConnection(void) const;
    virtual void			setDisconnection(void);

  protected: /* Attribute */
    int					m_fd;
    struct sockaddr_in			m_sockaddr;
    socklen_t				m_socklen;
    Socket::Connection			m_connection;
  };
}

#endif /* !SOCKET_HPP_ */
