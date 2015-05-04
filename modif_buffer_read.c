/*
** modif_buffer_read.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May  8 14:26:08 2012 florian dewulf
** Last update Sat May 19 17:45:06 2012 kevin lansel
*/

#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static void	reduc_modif_up(int *curs)
{
  int		nb;
  char		*cap;

  cap = NULL;
  while ((curs[0] + curs[2]) % curs[1] != 0)
    {
      go_to_left(curs);
      my_putchar(' ');
      curs[0]++;
      go_to_left(curs);
    }
  while (((curs[0] + curs[2]) / curs[1]) > 0)
    {
      cap = xtgetstr_exe(cap, "up");
      nb = curs[1] + 1;
      while (--nb > 0)
	my_putchar(' ');
      cap = xtgetstr_exe(cap, "up");
      curs[0] -= curs[1];
    }
}

t_history	*modif_buff_read_up(char *buffer, t_history **history,
				    int *curs)
{
  int		nb;

  nb = -1;
  if ((*history) == NULL)
    return (NULL);
  while (buffer[(curs[0])])
    {
      my_putchar(' ');
      (curs[0])++;
    }
  reduc_modif_up(curs);
  while ((*history)->line[++nb] && nb < 511)
    buffer[nb] = (*history)->line[nb];
  buffer[nb] = '\0';
  my_putstr(g_prompt);
  my_putstr(buffer);
  curs[0] = strlen(buffer);
  if ((*history)->prev)
    return ((*history)->prev);
  else
    {
      while ((*history)->next)
	(*history) = (*history)->next;
      return (*history);
    }
}

t_history	*modif_buff_read_down(char *buffer, t_history **history,
				      int *curs)
{
  int		nb;

  nb = -1;
  if ((*history) == NULL)
    return (NULL);
  while (buffer[(curs[0])])
    {
      my_putchar(' ');
      (curs[0])++;
    }
  reduc_modif_up(curs);
  if ((*history)->next != NULL)
    {
      (*history) = (*history)->next;
      while ((*history)->line[++nb] && nb < 511)
	buffer[nb] = (*history)->line[nb];
      buffer[nb] = '\0';
      curs[0] = strlen(buffer);
    }
  else
    curs[0] = (buffer[0] = '\0') ? 0 : 0;
  my_putstr(g_prompt);
  my_putstr(buffer);
  return (*history);
}
