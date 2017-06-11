/*
** client_action.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy/srcs/server
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Wed Jun 22 15:57:20 2016
** Last update Sat Jun 25 22:52:28 2016 Sébastien Le Maire
*/

#include "zappy_map.h"
#include "client_action.h"

static void		send_each_client_graph_move(void *content,
						    void *data)
{
  set_msg_pos_player((t_client *)content, (t_client_ia *)data);
}

void			avance(t_client_ia *client, t_zappy *zappy)
{
  move_player(&(zappy->world), &(client->player));
  set_answer_ok_ko(&client->client, TRUE);
  list_foreach_data(&zappy->server.clients_graphic, send_each_client_graph_move,
		    client);
}

void			left(t_client_ia *client, t_zappy *zappy)
{
  rotate_player(&(client->player), LEFT);
  set_answer_ok_ko(&client->client, TRUE);
  list_foreach_data(&zappy->server.clients_graphic, send_each_client_graph_move,
		    client);
}

void			right(t_client_ia *client, t_zappy *zappy)
{
  rotate_player(&(client->player), RIGHT);
  set_answer_ok_ko(&client->client, TRUE);
  list_foreach_data(&zappy->server.clients_graphic, send_each_client_graph_move,
		    client);
}

void			expulse(t_client_ia *client, t_zappy *zappy)
{
  t_string		str;

  if (zappy->world.map
      [POS(client->player.x, client->player.y, zappy->world.width)]
      .list.length == 1)
    {
      set_answer_ok_ko(&client->client, FALSE);
      msg_expulse_exe(&str, client->client.id);
      list_foreach_data(&zappy->server.clients_graphic,
			set_msg_all_client, str.data);
      string_clear(&str);
    }
  else
    {
      set_answer_ok_ko(&client->client, TRUE);
      expulse_players(&(zappy->world), &(client->player),
		      &zappy->server.clients_graphic);
    }
}
