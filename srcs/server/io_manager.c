/*
** ia_manager.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 20 16:12:45 2016 Sébastien Le Maire
** Last update Sat Jun 25 23:47:12 2016 Sébastien Le Maire
*/

#include <string.h>
#include "zappy_server.h"

static t_client_com const	g_com[ZAPPY_COM_LAST] =
  {
    &send_welcome,
    &send_info_new_player,
    &send_dead,
  };

static t_zappy_cmd_graph const	g_graph_cmd[NB_GRAPH_CMD] =
  {
    {"msz", FALSE, cmd_graph_map},
    {"bct", TRUE, cmd_graph_case},
    {"mct", FALSE, cmd_graph_all_case},
    {"tna", FALSE, cmd_graph_teams},
    {"ppo", TRUE, cmd_graph_pos_player},
    {"piv", TRUE, cmd_graph_lvl_player},
    {"pin", TRUE, cmd_graph_inventoty_player},
    {"sgt", FALSE, cmd_graph_time},
    {"sst", TRUE, cmd_graph_time}
  };

t_zappy_error			read_ia_manager(t_item **client,
						t_zappy *zappy)
{
  t_client_ia			*ia;
  t_zappy_error			err;

  ia = (t_client_ia *)((*client)->data);
  if (ia->player.team == -1)
    {
      if ((err = get_team(client, zappy)) != ZAPPY_NO_ERROR)
	return (err);
    }
  else
    receiv_action(ia);
  return (ZAPPY_NO_ERROR);
}

t_zappy_error			read_graph_manager(t_item **client_node,
						   t_zappy *zappy)
{
  t_client			*client;
  t_action			action;
  unsigned int			i;

  client = (t_client *)((*client_node)->data);
  action.order[0] = '\0';
  get_one_action(client, &action);
  if (!action.order[0])
    return (ZAPPY_NO_ERROR);
  i = 0;
  while ((i < NB_GRAPH_CMD) && (strcmp(g_graph_cmd[i].cmd, action.order)))
    ++i;
  if ((i == NB_GRAPH_CMD) || (BOOL(action.arg[0]) != g_graph_cmd[i].have_arg))
    string_push_back(&client->msg, "suc\n");
  else if (g_graph_cmd[i].action)
    g_graph_cmd[i].action(client, zappy, action.arg);
  return (ZAPPY_NO_ERROR);
}

void			        write_client_manager(t_client *client,
						     t_zappy *zappy)
{
  if (client->com != ZAPPY_COM_LAST)
    {
      g_com[client->com](client, zappy);
      client->com = ZAPPY_COM_LAST;
    }
  else if (client->msg.length)
    {
      server_send(client, client->msg.data, client->msg.length);
      string_clear(&client->msg);
    }
}
