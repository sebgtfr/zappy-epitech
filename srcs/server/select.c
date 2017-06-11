/*
** select.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 13 15:29:36 2016 Sébastien Le Maire
** Last update Sun Jun 26 12:44:28 2016 Sébastien Le Maire
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

static void		        select_list_client(t_list *list_clients,
						   t_fd_set *fd_select,
						   int *max, t_zappy *zappy)
{
  t_item			*node_client;
  t_client			*client;

  node_client = list_clients->begin;
  while (node_client)
    {
      client = (t_client *)(node_client->data);
      if (client->connection != ZAPPY_DISCONNECTE)
	{
	  if ((client->connection == ZAPPY_CONNECTE) &&
	      (client->socket.fd != -1))
	    {
	      FD_SET(client->socket.fd, &fd_select->fd_read);
	      FD_SET(client->socket.fd, &fd_select->fd_write);
	      FD_SET(client->socket.fd, &fd_select->fd_error);
	    }
	  node_client = node_client->next;
	}
      else
	node_client = delete_client(list_clients, node_client, max, zappy);
    }
}

static void			init_select(t_zappy *zappy,
					    struct timeval *tv, int *max)
{
  FD_ZERO(&(zappy->server.fd_sets.fd_read));
  FD_ZERO(&(zappy->server.fd_sets.fd_write));
  FD_ZERO(&(zappy->server.fd_sets.fd_error));
  FD_SET(zappy->server.socket.fd, &(zappy->server.fd_sets.fd_read));
  FD_SET(zappy->server.socket.fd, &(zappy->server.fd_sets.fd_error));
  select_list_client(&zappy->server.clients_ia, &zappy->server.fd_sets,
		     max, zappy);
  select_list_client(&zappy->server.clients_graphic, &zappy->server.fd_sets,
		     max, zappy);
  tv->tv_sec = 0;
  tv->tv_usec = 1;
}

static t_zappy_error   		g_ret = ZAPPY_NO_ERROR;

static void			sigquit_server(__attribute__((unused))int sig)
{
  g_ret = ZAPPY_EXIT_NO_ERROR;
}

static int			check_end(t_zappy *zappy)
{
  unsigned int	       		k;
  t_team			*team;
  t_string			str;
  int				size;

  team = (t_team *)(zappy->teams_manager.teams.data);
  k = 0;
  while (k < zappy->teams_manager.teams.length)
    {
      if (team->max_lvl_player == 8)
	{
	  if ((string_init(&str, 6 + strlen(team->name))) &&
	      ((size = sprintf(str.data, "seg %s\n", team->name)) > 0))
	    {
	      str.data[size] = '\0';
	      list_foreach_data(&zappy->server.clients_graphic,
				set_msg_all_client, str.data);
	      string_clear(&str);
	    }
	  return (0);
	}
      ++k;
      ++team;
    }
  return (1);
}

t_zappy_error			launch_server(t_zappy *zappy)
{
  struct timeval		tv;
  int				max;
  uint32_t			ticks_gen_resource;

  max = zappy->server.socket.fd;
  if (signal(SIGINT, &sigquit_server) == SIG_ERR)
    return (ZAPPY_SIGNAL_ERROR);
  launch_time(&zappy->timer);
  ticks_gen_resource = 1;
  while ((g_ret == ZAPPY_NO_ERROR) && check_end(zappy))
    {
      init_select(zappy, &tv, &max);
      if (select(max + 1, &(zappy->server.fd_sets.fd_read),
		 &(zappy->server.fd_sets.fd_write),
		 &(zappy->server.fd_sets.fd_error), &tv) == -1)
        g_ret = ((g_ret == ZAPPY_NO_ERROR) ? ZAPPY_SELECT_FD : g_ret);
      if (g_ret == ZAPPY_NO_ERROR)
	g_ret = manager(zappy, &max, &ticks_gen_resource);
      if (g_ret != ZAPPY_NO_ERROR && g_ret != ZAPPY_EXIT_NO_ERROR)
	{
	  zappy_error(g_ret);
	  g_ret = ((g_ret != ZAPPY_EXIT_NO_ERROR) ? ZAPPY_NO_ERROR : g_ret);
	}
    }
  return (g_ret);
}
