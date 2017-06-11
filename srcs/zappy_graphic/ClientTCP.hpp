//
// Client.hpp for server in /home/le-mai_s/librairie/librairie_cpp/libmysocket
//
// Made by Sébastien Le Maire
// Login   <le-mai_s@epitech.net>
//
// Started on  Sun Apr 24 21:13:06 2016 Sébastien Le Maire
// Last update Sun Jun 26 23:11:06 2016 Sébastien Le Maire
//

#ifndef CLIENTTCP_HPP_
# define CLIENTTCP_HPP_

# include <stdint.h>
# include <string>
# include "Socket.hpp"

namespace			TCP
{
  class				Client : public TCP::Socket
  {
  public: /* ctor & dtor on canonics form */
    Client(void);
    Client(Client const &copy);
    virtual Client	       	&operator=(Client const &other);
    virtual ~Client(void);

  public: /* Methods */
    virtual bool		init(uint16_t port, std::string const &addressHost);
    virtual void	       	launch(void);

  private: /* Functions */
    virtual bool		initSelect(void);
    virtual void		readOnSocket(void);
    virtual void	        writeOnSocket(void);
    virtual void		readOnInput(void);
    virtual void	        writeOnOutput(void);
    virtual void		action(void);

  private: /* TCP Attribute */
    uint16_t			m_port;
    fd_set			m_read;
    fd_set			m_write;
    fd_set			m_except;
    struct timeval		m_tv;

  private: /* Program Attribute */
    std::string			m_buffer;
    std::string			m_send;
    std::string			m_msgOutput;
    bool			m_welcome;
  };
}

#endif /* !CLIENTTCP_HPP_ */
