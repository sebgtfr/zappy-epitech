/*
** action.c for zappy in /home/karraz_s/rendu/PSU_2015_zappy
**
** Made by stephane karraz
** Login   <karraz_s@epitech.net>
**
** Started on  Thu Jun 16 14:08:50 2016 stephane karraz
** Last update Sun Jun 26 20:58:38 2016 
*/

#include <string.h>
#include <stdio.h>
#include "zappy_bool.h"
#include "zappy_server.h"
#include "zappy_action.h"

static void			copy_on_action(t_action *action,
					       char const *buff)
{
  unsigned int			i;
  unsigned int			j;

  i = 0;
  j = 0;
  action->arg[0] = '\0';
  while (buff[i] && buff[i] != ' ' && buff[i] != '\n' && i < LEN_ORDER)
    {
      action->order[i] = buff[i];
      ++i;
    }
  action->order[i] = '\0';
  if ((buff[i] && buff[i] != '\n') && (buff[i + 1] && buff[i + 1] != '\n'))
    ++i;
  while (buff[i + j] && (i + j) < LEN_ARG && buff[i + j] != '\n')
    {
      action->arg[j] = buff[i + j];
      ++j;
    }
  action->arg[j] = '\0';
}

void				get_one_action(t_client *client,
					       t_action *action)
{
  char				buff[LEN_ARG + LEN_ORDER + 1];

  buff[0] = '\0';
  server_recv(client, (void *)buff, (LEN_ARG + LEN_ORDER + 1));
  if (buff[0])
    copy_on_action(action, buff);
}

t_bool				get_action(t_player *player, t_action *action)
{
  if (player->nb_orders <= 0)
    return (FALSE);
  if (player->action[player->id_order].order[0] != 0)
    {
      player->nb_orders--;
      strncpy(action->order,
	      player->action[player->id_order].order, LEN_ORDER);
      strncpy(action->arg, player->action[player->id_order].arg, LEN_ARG);
      player->action[player->id_order].order[0] = 0;
      player->id_order = (player->id_order + 1) % MAX_ORDERS;
      return (TRUE);
    }
  return (FALSE);
}

static t_action			*get_empty_slot(t_player *player)
{
  return (((player->nb_orders >= MAX_ORDERS)) ? NULL :
	  (player->action +
	   ((player->id_order + player->nb_orders) % MAX_ORDERS)));
}

void				receiv_action(t_client_ia *client)
{
  char				buff[LEN_ARG + LEN_ORDER + 1];
  t_action			*action;

  buff[0] = '\0';
  server_recv((t_client *)client, (void *)buff, (LEN_ARG + LEN_ORDER + 1));
  if ((action = get_empty_slot(&(client->player))))
    {
      ++(client->player.nb_orders);
      if (buff[0])
	copy_on_action(action, buff);
      else
	action->order[0] = '\0';
    }
}
