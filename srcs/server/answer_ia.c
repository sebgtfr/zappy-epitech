/*
** answer_ia.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun 23 21:15:38 2016 Sébastien Le Maire
** Last update Thu Jun 23 21:39:13 2016 Sébastien Le Maire
*/

#include "zappy_server.h"

void				set_answer_ok_ko(t_client *client, t_bool ok)
{
  char const			*msg;

  msg = (ok) ? "ok\n" : "ko\n";
  string_push_back(&client->msg, msg);
}
