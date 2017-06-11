/*
** zappy_network.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 13 12:13:51 2016 Sébastien Le Maire
** Last update Sat Jun 25 17:02:23 2016 
*/

#ifndef ZAPPY_NETWORK_H_
# define ZAPPY_NETWORK_H_

# include <netinet/in.h>
# include "list.h"
# include "zappy_error.h"

typedef struct			s_fd_set
{
  fd_set			fd_read;
  fd_set			fd_write;
  fd_set			fd_error;
}				t_fd_set;

typedef struct			s_socket
{
  int			        fd;
  struct sockaddr_in		sockaddr;
  socklen_t			socklen;
}				t_socket;

typedef struct			s_zappy_server
{
  uint16_t			port;
  t_socket			socket;
  uint32_t			last_id;
  uint32_t			last_id_egg;
  t_list			clients_ia;
  t_list			clients_graphic;
  t_list			eggs;
  t_fd_set			fd_sets;
}				t_zappy_server;

/*
** TCP network functions
** tcp.c
*/
t_zappy_error			connect_server(t_zappy_server *server);
void				delete_socket(t_socket *socket);

#endif /* !ZAPPY_NETWORK_H_ */
