/*
** time.c for libtime in /home/le-mai_s/librairie/librairie_C/libtime/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu May 26 19:49:32 2016 Sébastien Le Maire
** Last update Sat Jun 25 00:06:47 2016 Sébastien Le Maire
*/

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "zappy_time.h"

void				change_frequency(t_time *time,
						 uint32_t frequency)
{
  time->frequency = frequency;
  time->change = TRUE;
}

t_bool			        launch_time(t_time *time)
{
  time->tick = (time->frequency) ? (1000000000 / time->frequency) : 0;
  time->out_tick = 0;
  time->change = FALSE;
  time->old_frequency = time->frequency;
  time->count_ticks = 0;
  if ((clock_gettime(CLOCK_MONOTONIC, &time->old)) == -1)
    return (FALSE);
  return (TRUE);
}

static t_bool			update_time(t_time *time)
{
  if ((clock_gettime(CLOCK_MONOTONIC, &time->now)) == -1)
    return (FALSE);
  return (TRUE);
}

static uint64_t			diff_time(t_time *time, t_bool *err)
{
  *err = FALSE;
  if ((*err = (!(update_time(time)))))
    return (0);
  return (((1000000000L * (time->now.tv_sec - time->old.tv_sec)) +
	   time->now.tv_nsec - time->old.tv_nsec));
}

t_bool				check_tick_time(t_time *time, t_bool *err)
{
  unsigned int			tick;
  uint64_t			diff;

  *err = FALSE;
  tick = (time->tick <= time->out_tick) ? 0 : (time->tick - time->out_tick);
  if ((!time->tick) || ((diff = diff_time(time, err)) > tick))
    {
      time->count_ticks = (time->count_ticks + 1) % time->old_frequency;
      if ((time->change) && (!time->count_ticks))
	{
	  time->tick = (time->frequency) ? (1000000000 / time->frequency) : 0;
	  time->change = FALSE;
	  time->out_tick = 0;
	  time->old_frequency = time->frequency;
	}
      else
	time->out_tick = diff - tick;
      time->old = time->now;
      return (!(*err));
    }
  return (FALSE);
}
