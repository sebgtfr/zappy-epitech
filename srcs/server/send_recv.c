/*
** send_recv.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 15 14:03:20 2016 Sébastien Le Maire
** Last update Sun Jun 26 21:01:31 2016 Sébastien Le Maire
*/

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "zappy_client.h"

void				server_send(t_client *client,
					    void const *msg, size_t len)
{
  size_t			msg_send;
  ssize_t			ret;

  if ((client->connection == ZAPPY_CONNECTE) ||
      ((client->connection == ZAPPY_DECONNECTION_AFTER_SEND_MSG)))
    {
      errno = 0;
      msg_send = 0;
      while (msg_send < len)
	{
	  if ((ret = sendto(client->socket.fd, msg + msg_send, len - msg_send,
			    MSG_NOSIGNAL | MSG_DONTWAIT,
			    (struct sockaddr *)&client->socket.sockaddr,
			    client->socket.socklen)) <= 0)
	    {
	      if (errno != EAGAIN && errno != EWOULDBLOCK)
		client->connection = ZAPPY_DISCONNECTE;
	      return ;
	    }
	  msg_send += ret;
	}
      if (client->connection == ZAPPY_DECONNECTION_AFTER_SEND_MSG)
	client->connection = ZAPPY_DISCONNECTE;
    }
}

void				server_recv(t_client *client,
					    void *msg, size_t len)
{
  size_t			msg_recv;
  ssize_t			ret;

  if (client->connection == ZAPPY_CONNECTE)
    {
      errno = 0;
      msg_recv = 0;
      while (msg_recv < (len - 1))
	{
	  if ((ret = recvfrom(client->socket.fd, msg + msg_recv,
			      len - msg_recv, MSG_DONTWAIT,
			      (struct sockaddr *)&client->socket.sockaddr,
			      &client->socket.socklen)) <= 0)
	    {
	      if (errno != EAGAIN)
		client->connection = ZAPPY_DISCONNECTE;
	      return ;
	    }
	  msg_recv += ret;
	  ((char *)msg)[ret] = 0;
	}
    }
}
