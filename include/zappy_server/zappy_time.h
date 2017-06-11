/*
** zappy_time.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 18 17:50:20 2016 Sébastien Le Maire
** Last update Fri Jun 24 23:43:54 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_TIME_H_
# define ZAPPY_TIME_H_

#include <stdint.h>
#include <time.h>
#include "zappy_bool.h"

typedef struct			s_time
{
  uint32_t		        frequency;
  uint32_t			old_frequency;
  uint32_t		        tick;
  uint32_t			count_ticks;
  uint32_t		        out_tick;
  t_bool			change;
  struct timespec		old;
  struct timespec		now;
}				t_time;

/*
** time.c
*/
void				change_frequency(t_time *time,
						 uint32_t frequency);
t_bool			        launch_time(t_time *time);
t_bool				check_tick_time(t_time *time, t_bool *err);

#endif /* !ZAPPY_TIME_H_ */
