/*
** init_history.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May  8 10:29:31 2012 florian dewulf
** Last update Fri May 18 18:01:12 2012 kevin lansel
*/

#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"42sh.h"

void		add_to_history(t_history **histo, char *str, int fd)
{
  t_history	*tmp;
  t_history	*elem;

  if (fd != -1)
    {
      write(fd, str, strlen(str));
      write(fd, "\n", 1);
    }
  tmp = *histo;
  elem = malloc(sizeof(t_history));
  if (elem == NULL)
    return;
  elem->line = str;
  elem->next = NULL;
  elem->prev = NULL;
  if (tmp == NULL)
    *histo = elem;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
      elem->prev = tmp;
    }
}

static int	history_stock(t_history **tmp_history, char *str, int *indice)
{
  char		*tempo;
  int		fd;
  t_history	*history;
  int		count;

  count = 0;
  history = *tmp_history;
  if ((tempo = concate(&str[5], "/.42sh_history")) == NULL)
    *indice = 0;
  xfree(str);
  if (*indice != 0 && (fd = open(tempo, O_RDWR | O_APPEND)) == -1)
    if ((fd = open(tempo, O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC,
		   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
      *indice = 0;
  while (*indice && fd != -1 && (str = get_next_line_bis(fd)) && count < 500)
    if (str[0] != '\0')
      {
	add_to_history(&history, str, -1);
	count++;
      }
  *tmp_history = history;
  xfree(str);
  return (fd);
}

int		init_history(t_history **history, t_env *env)
{
  t_env		*tmp_env;
  t_history	*tmp_hist;
  char		*str;
  int		indice;
  int		fd;

  indice = 1;
  tmp_env = env;
  tmp_hist = *history;
  while (tmp_env && !compegal(tmp_env->line, "HOME"))
    tmp_env = tmp_env->next;
  if ((!tmp_env) || (tmp_env && ((str = my_strcpy(tmp_env->line)) == NULL)))
    indice = 0;
  if (indice)
    fd = history_stock(&tmp_hist, str, &indice);
  if (indice == 0)
    my_putstr("[HISTORY] Cannot access $HOME/.42sh_history or fail malloc\n");
  else
    *history = tmp_hist;
  if (fd == -1)
    return (0);
  return (fd);
}
