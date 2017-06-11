/*
** cmd_graph.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Fri Jun 24 19:18:17 2016 Sébastien Le Maire
** Last update Sat Jun 25 16:01:36 2016 Sébastien Le Maire
*/

#include "zappy_server.h"

static int	       		cmp_id(void *content, void const *data)
{
  return (!(BOOL((((t_client *)(content))->id == (*(unsigned int *)data)))));
}

void				cmd_graph_pos_player(t_client *client,
						     t_zappy *zappy,
						     char const *args)
{
  unsigned int			n;
  t_zappy_error			err;
  t_client_ia			*ia;

  n = getnbr(args, &err);
  if ((err == ZAPPY_NO_ERROR) && (n < zappy->server.last_id) &&
      ((ia = (t_client_ia *)list_compare(&zappy->server.clients_ia,
					 cmp_id, &n))))
    {
      set_msg_pos_player(client, ia);
      return ;
    }
  string_push_back(&client->msg, "sbp\n");
}

void				cmd_graph_lvl_player(t_client *client,
						     t_zappy *zappy,
						     char const *args)
{
  unsigned int			n;
  t_zappy_error			err;
  t_client_ia			*ia;

  n = getnbr(args, &err);
  if ((err == ZAPPY_NO_ERROR) && (n < zappy->server.last_id) &&
      ((ia = (t_client_ia *)list_compare(&zappy->server.clients_ia,
					 cmp_id, &n))))
    {
      set_msg_lvl_player(client, ia);
      return ;
    }
  string_push_back(&client->msg, "sbp\n");
}

void				cmd_graph_inventoty_player(t_client *client,
							   t_zappy *zappy,
							   char const *args)
{
  unsigned int			n;
  t_zappy_error			err;
  t_client_ia			*ia;

  n = getnbr(args, &err);
  if ((err == ZAPPY_NO_ERROR) && (n < zappy->server.last_id) &&
      ((ia = (t_client_ia *)list_compare(&zappy->server.clients_ia,
					 cmp_id, &n))))
    {
      set_msg_inventory_player(client, ia);
      return ;
    }
  string_push_back(&client->msg, "sbp\n");
}
