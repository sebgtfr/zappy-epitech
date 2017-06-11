/*
** error.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Jun  5 22:57:17 2016 Sébastien Le Maire
** Last update Mon Jun 20 19:46:10 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy_error.h"

static char const		*g_msg_error[ZAPPY_NO_ERROR] =
{
  "Isn't number",
  "Overflow ! number out of range",
  "Command unknown",
  "Invalid port",
  "Allocation of memory failed",
  "Group's name already use",
  "Map's size can't be null",
  "Time's frequency can't be null",
  "Max number of clients can't be null",
  "Need one group (-n)",
  "Need port (-p)",
  "Initialisation of socket failed",
  "Bind of socket failed",
  "Listening of port failed",
  "Select of file descriptor failed",
  "Catch of signal failed",
  "Accept client failed",
  "Update timer failed",
  "A server error's file descriptor was detected"
};

int				zappy_error(t_zappy_error code_error)
{
  if ((code_error < ZAPPY_NO_ERROR) && (code_error >= 0))
    {
      (void)fprintf(stderr, "Error [%02u] => %s !\n",
		    (unsigned int)code_error + 1,
		    g_msg_error[code_error]);
      return (EXIT_FAILURE);
    }
  return ((code_error == ZAPPY_NO_ERROR) ? EXIT_SUCCESS :
	  EXIT_SUCCESS + EXIT_FAILURE + 2);
}
