/*
* player.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun 16 12:00:21 2016 Sébastien Le Maire
** Last update Sun Jun 26 21:35:27 2016 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zappy_server.h"

void				delete_player_on_map(t_player *player,
						     t_world *world)
{
  t_list			*list_player;
  t_item			*item;

  list_player = &(world->map + POS(player->x, player->y, world->width))->list;
  item = list_player->begin;
  while (item)
    {
      if ((*((t_player **)(item->data))) == player)
	{
	  list_erase(list_player, item, NULL);
	  return ;
	}
      item = item->next;
    }
}

void				init_player(t_player *p, t_world *world,
					    int set_pos)
{
  int				i;

  p->level = 1;
  (void)memset((void *)p->inventory, 0, sizeof(p->inventory));
  p->inventory[ZAPPY_FOOD] += 10;
  if (set_pos)
    {
      p->team = -1;
      p->x = rand() % world->width;
      p->y = rand() % world->height;
    }
  p->facing = rand() % 4 + 1;
  p->expulsed_from = 0;
  list_push_back(&(world->map[POS(p->x, p->y, world->width)].list), &p);
  p->hp = 1;
  p->nb_orders = 0;
  p->id_order = 0;
  p->cur_action = ZAPPY_PLAYER_NO_ACTION;
  p->time_action = 0;
  i = 0;
  while (i < MAX_ORDERS + 1)
    {
      (void)memset((void *)&(p->action[i]), 0, sizeof(p->action[i]));
      i++;
    }
}

static void			set_msg_ia_dead(void *client, void *dead)
{
  char				data[15];
  int				size;
  char const			*cmd;
  uint32_t			id;
  t_client			*client_dead;

  client_dead = (t_client *)dead;
  if (!client_dead->id)
    {
      cmd = "edi";
      id = client_dead->id_egg;
    }
  else
    {
      cmd = "pdi";
      id = client_dead->id;
    }
  if ((size = sprintf(data, "%s %u\n", cmd, id)) > 0)
    {
      data[size] = '\0';
      string_push_back(&((t_client *)(client))->msg, data);
    }
}

t_bool				hp_management(t_client_ia *client,
					      t_list *list_graph,
					      t_vector *team)
{
  --(client->player.hp);
  if (!client->player.hp)
    {
      if (client->player.inventory[ZAPPY_FOOD])
	{
	  --(client->player.inventory[ZAPPY_FOOD]);
	  client->player.hp += 126;
	}
      else
	{
	  if (client->client.connection == ZAPPY_CONNECTION_UNDEFINE)
	    {
	      client->client.connection = ZAPPY_DISCONNECTE;
	      if (((t_team *)team->data)[client->player.team].nb_ghost)
		--(((t_team *)team->data)[client->player.team].nb_ghost);
	    }
	  else
	    client->client.com = ZAPPY_COM_DEAD;
	  list_foreach_data(list_graph, set_msg_ia_dead, &client->client);
	  return (FALSE);
	}
    }
  return (TRUE);
}
