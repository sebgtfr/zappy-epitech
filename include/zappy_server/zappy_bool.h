/*
** zappy_bool.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 18 17:49:50 2016 Sébastien Le Maire
** Last update Fri Jun 24 14:56:17 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_BOOL_H_
# define ZAPPY_BOOL_H_

/*
** Boolean
*/
typedef char			t_bool;

# ifndef FALSE
#  define FALSE			((t_bool)0)
# endif /* !FALSE */
# ifndef TRUE
#  define TRUE			!FALSE
# endif /* !TRUE */

# define BOOL(b)		(!(!(b)))

#endif /* !ZAPPY_BOOL_H_ */
