/*
** incantation_com.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Jun 26 11:58:25 2016 Sébastien Le Maire
** Last update Sun Jun 26 19:47:56 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

static void		get_id_players(void *content, void *data)
{
  char		        msg[12];
  int			size;

  if ((size = sprintf(msg, " %d", (*((t_player **)content))->level)) > 0)
    {
      msg[size] = '\0';
      string_push_back(((t_string *)data), msg);
    }
}

void			com_incantation_start(t_client_ia *ia, t_zappy_map *map,
					      t_list *clients_graph)
{
  t_string		str;
  char			data[30];
  int			size;

  string_push_back(&(ia->client.msg), "elevation en cours\n");
  string_init(&str, 0);
  if ((size = sprintf(data, "pic %u %u %u", ia->player.x, ia->player.y,
		      ia->player.level)) <= 0)
    return ;
  data[size] = '\0';
  string_push_back(&str, data);
  list_foreach_data(&map->list, get_id_players, &str);
  string_push_back_char(&str, '\n');
  string_push_back_char(&str, '\0');
  list_foreach_data(clients_graph, set_msg_all_client, str.data);
  string_clear(&str);
}

void			push_msg_lvl_player(t_string *msg, t_client_ia *ia)
{
  char			data[18];
  unsigned int		size;

  if ((size = sprintf(data, "plv %u %d\n", ia->client.id,
		      ia->player.level)) > 0)
    {
      data[size] = '\0';
      string_push_back(msg, data);
    }
}

void			push_msg_data_case(t_string *msg, unsigned int x,
					   unsigned int y,
					   t_zappy_map *map_case)
{
  char			data_case[94];
  int			size;

  if ((size = sprintf(data_case, "bct %u %u %u %u %u %u %u %u %u\n",
		      x, y, map_case->resources[ZAPPY_FOOD],
		      map_case->resources[ZAPPY_LINEMATE],
		      map_case->resources[ZAPPY_DERAUMERE],
		      map_case->resources[ZAPPY_SIBUR],
		      map_case->resources[ZAPPY_MENDIANE],
		      map_case->resources[ZAPPY_PHIRAS],
		      map_case->resources[ZAPPY_THYSTAME])) > 0)
    {
      data_case[size] = '\0';
      string_push_back(msg, data_case);
    }
}

void			msg_incantation_player_end(t_list *case_player,
						   t_string *msg,
						   t_world *world,
						   t_player *ref)
{
  t_item		*node;

  node = case_player->begin;
  while (node)
    {
      push_msg_lvl_player(msg,
			  convert_player_to_client(*((t_player **)node->data)));
      node = node->next;
    }
  push_msg_data_case(msg, ref->x, ref->y,
		     (world->map + POS(ref->x, ref->y, world->width)));
  string_push_back_char(msg, '\0');
}
