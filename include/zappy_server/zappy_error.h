/*
** zappy_error.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Jun  5 22:58:00 2016 Sébastien Le Maire
** Last update Mon Jun 20 19:46:35 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_ERROR_H_
# define ZAPPY_ERROR_H_

typedef	enum			e_zappy_error
{
				ZAPPY_NOT_NUMBER,
				ZAPPY_NUMBER_OVERFLOW,
				ZAPPY_UNKNOWN_CMD,
				ZAPPY_INVALID_PORT,
				ZAPPY_BAD_ALLOC,
				ZAPPY_GROUP_NAME_ALREADY_EXIST,
				ZAPPY_INVALID_MAP,
				ZAPPY_INVALID_TIMER,
				ZAPPY_INVALID_MAX_CLIENTS,
				ZAPPY_NO_TEAM,
				ZAPPY_NO_PORT,
				ZAPPY_INIT_SOCKET,
				ZAPPY_SOCKET_BIND,
				ZAPPY_SOCKET_LISTEN,
				ZAPPY_SELECT_FD,
				ZAPPY_SIGNAL_ERROR,
				ZAPPY_ACCEPT,
				ZAPPY_TIMER,
				ZAPPY_FD_ERROR,
				ZAPPY_NO_ERROR,
				ZAPPY_EXIT_NO_ERROR
}				t_zappy_error;

int				zappy_error(t_zappy_error code_error);

#endif /* !ZAPPY_ERROR_H_ */
