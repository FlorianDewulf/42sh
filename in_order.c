/*
** in_order.c for 42sh in /home/seth/my_42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Mon May 21 17:21:53 2012 kevin lansel
** Last update Wed May 23 10:58:27 2012 kevin lansel
*/

#include	<string.h>
#include	"42sh.h"

static int	count_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

int		in_order(char **tab)
{
  int		c;
  char		*tmp;

  if (tab)
    {
      c = count_tab(tab);
      if (c == 5 && tab[1] && tab[1][strlen(tab[1]) - 1] == '>')
	{
	  tmp = tab[1];
	  tab[1] = tab[3];
	  tab[3] = tmp;
	  tmp = tab[2];
	  tab[2] = tab[4];
	  tab[4] = tmp;
	}
    }
  return (1);
}
