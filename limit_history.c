/*
** limit_history.c for 42 in /home/david/Projet/42sh/urand
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Fri May 18 21:20:35 2012 david blervaque
** Last update Sun May 20 02:33:48 2012 kevin lansel
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"42sh.h"

static int	count_history(t_history *histo_tmp)
{
  t_history	*tmp;
  int		curs;

  curs = 0;
  tmp = histo_tmp;
  if (tmp != NULL)
    {
      while (tmp->prev != NULL)
	{
	  curs++;
	  tmp = tmp->prev;
	}
    }
  else
    return (0);
  if (tmp->prev == NULL)
    return (curs);
  else
    return (-1);
}

static t_history	*refresh_history(t_history *history)
{
  t_history	*tmp;
  t_history	*tmp2;

  tmp = history;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  tmp2 = tmp->next;
  tmp2->prev = NULL;
  while (tmp2->next != NULL)
    tmp2 = tmp2->next;
  xfree(tmp->line);
  xfree(tmp);
  return (tmp2);
}

static char	*create_file(t_env *env_list)
{
  char		*filename;
  char		*tmp;

  tmp = my_strcpy("/.42sh_history");
  if (env_list == NULL)
    return (NULL);
  while (env_list && !compegal(env_list->line, "HOME"))
    env_list = env_list->next;
  if (env_list == NULL)
    return (NULL);
  filename = decoup_from_egal(env_list->line);
  filename = concate(filename, tmp);
  xfree(tmp);
  return (filename);
}

static int	write_in_file(t_history *history, t_env *env_list, int fd)
{
  t_history	*tmp;
  char		*filename;
  char		next_line;

  next_line = '\n';
  if (close(fd) == -1)
    return (-1);
  if ((filename = create_file(env_list)) == NULL)
    return (-2);
  if ((fd = open(filename, O_RDWR | O_TRUNC)) == -1)
    return (-3);
  tmp = history;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp->next != NULL)
    {
      write(fd, tmp->line, my_strlen(tmp->line));
      write(fd, &next_line, 1);
      tmp = tmp->next;
    }
  write(fd, tmp->line, my_strlen(tmp->line));
  write(fd, &next_line, 1);
  xfree(filename);
  return (0);
}

t_history		*limit_history(t_history *history, char *str, int fd,
				       t_env *env_list)
{
  t_history	*tmp;
  int		ret;

  tmp = history;
  if ((ret = count_history(tmp)) < 500)
    add_to_history(&tmp, str, fd);
  else
    {
      tmp = refresh_history(tmp);
      add_to_history(&tmp, str, fd);
      ret = write_in_file(tmp, env_list, fd);
      if (ret == -1)
	my_puterror_int("[HISTORY]: Error on close.\n");
      else if (ret == -2)
	my_puterror_int("[HISTORY]: $HOME not exist.\n");
      else if (ret == -3)
	my_puterror_int("[HISTORY]: Error on open.\n");
      if (ret == -1 || ret == -2 || ret == -3)
	return (history);
    }
  return (tmp);
}
