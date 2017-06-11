/*
** tcp.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 13 12:49:59 2016 Sébastien Le Maire
** Last update Thu Jun 16 12:48:35 2016 Sébastien Le Maire
*/

#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zappy_error.h"
#include "zappy_network.h"
#include "zappy_client.h"

static t_zappy_error		init_tcp_socket(t_socket *sock, uint16_t port)
{
  struct protoent		*pe;

  if ((!(pe = getprotobyname("TCP"))) ||
      ((sock->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1))
    return (ZAPPY_INIT_SOCKET);
  sock->sockaddr.sin_port = htons(port);
  return (ZAPPY_NO_ERROR);
}

void				delete_socket(t_socket *socket)
{
  if ((socket) && (socket->fd != -1))
    {
      close(socket->fd);
      socket->fd = -1;
    }
}

t_zappy_error			connect_server(t_zappy_server *server)
{
  t_zappy_error			err;

  if ((err = init_tcp_socket(&server->socket, server->port)) != ZAPPY_NO_ERROR)
    return (err);
  server->socket.sockaddr.sin_addr.s_addr = INADDR_ANY;
  server->socket.sockaddr.sin_family = AF_INET;
  server->socket.socklen = (socklen_t)sizeof(server->socket.sockaddr);
  if (bind(server->socket.fd,
	   (struct sockaddr const *)(&server->socket.sockaddr),
	   server->socket.socklen) < 0)
    return (ZAPPY_SOCKET_BIND);
  if (listen(server->socket.fd, 5) < 0)
    return (ZAPPY_SOCKET_LISTEN);
  return (ZAPPY_NO_ERROR);
}
