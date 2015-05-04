/*
** rmbhistory.c for 42sh in /home/seth/42sh-2016-dewulf_f/rmbhistory_dir
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Sat May 19 01:59:40 2012 kevin lansel
** Last update Sat May 19 16:45:01 2012 florian dewulf
*/

#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"42sh.h"

static char	*last_line(t_history **hist)
{
  t_history	*ptr;

  ptr = *hist;
  if (ptr && ptr->line)
    return (my_strcpy(ptr->line));
  else
    return (my_puterror_null("HISTORY: .42sh_history empty\n"));
}

static char	*line_is_num(t_history *ptr, int nb)
{
  int		i;

  i = 0;
  while (ptr && ptr->prev)
    ptr = ptr->prev;
  while (ptr && ++i != nb)
    ptr = ptr->next;
  if (ptr && i == nb && ptr->line)
    return (my_strcpy(ptr->line));
  else
    return (my_puterror_null("[HISTORY]: Invalid Line Number\n"));
}

static char	*line_is_com(char *str, t_history *ptr)
{
  int		i;

  i = 0;
  while (ptr && ptr->prev && str[i])
    {
      if (str[i] == ptr->line[i])
	i++;
      else
	ptr = ptr->prev;
    }
  if (str[i] == '\0')
    return (my_strcpy(ptr->line));
  else
    return (my_puterror_null("[HISTORY]: Invalid Command\n"));
}

static char	*check_line(char *str, t_history **hist)
{
  t_history	*ptr;
  int		nb;

  ptr = *hist;
  nb = my_getnbr(str);
  if (ptr && nb != 0)
    return (line_is_num(ptr, nb));
  else if (ptr && nb == 0)
    return (line_is_com(str, ptr));
  else
    return (NULL);
}

char		*rmbhistory(char *str, t_history **hist)
{
  int		i;

  i = 0;
  if (str != NULL && *hist != NULL)
    {
      while (str[i] && str[i] == '!')
	i++;
      if (i == 1 && strlen(str) != 1)
	return (check_line(&str[1], hist));
      else if (i == 2 && strlen(str) == 2)
	return (last_line(hist));
      else if ((i == 1 && strlen(str) == 1) || i > 2)
	return (my_puterror_null("HISTORY: Syntax error around [!]\n"));
    }
  else if (*hist == NULL)
    return (my_puterror_null("HISTORY: .42sh_history empty\n"));
  return (NULL);
}
