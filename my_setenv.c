/*
** my_setenv.c for 42sh in /home/peelou/Documents/Projets/42sh/toast/42sh-2016-dewulf_f
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Fri May 18 13:25:31 2012 gery baudry
** Last update Sun May 20 01:55:37 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int		my_envetoile(t_env *env)
{
  t_env		*tmp;

  tmp = env;
  while (tmp)
    {
      xfree(tmp->line);
      tmp->line  = my_strcpy("");
      tmp = tmp->next;
    }
  return (0);
}

static int		my_unsetenv(char *tab, t_env **env)
{
  t_env		*tmp;

  tmp = *env;
  while (tmp != NULL)
    {
      if (compegal(tmp->line, tab))
	{
	  if (tmp->next)
	    tmp->next->previous = tmp->previous;
	  if (tmp->previous)
	    tmp->previous->next = tmp->next;
	  xfree(tmp->line);
	  tmp->line = my_strcpy("");
	  return (0);
	}
      tmp = tmp->next;
    }
  return (1);
}

static int		my_setenv(char **tab, t_env **env)
{
  char		*commande;
  t_env		*tmp;

  tmp = *env;
  while (tmp && !compegal(tmp->line, tab[1]))
    tmp = tmp->next;
  if (tmp)
    {
      xfree(tmp->line);
      tmp->line = concate(tab[1], "=");
      if (tab[2] != NULL)
	tmp->line = concate(tmp->line, tab[2]);
      return (0);
    }
  if (tmp == NULL)
    {
      tmp = *env;
      while (tmp->next)
	tmp = tmp->next;
      commande = concate(tab[1], "=");
      if (tab[2] != NULL)
	add_to_list(env, concate(commande, tab[2]));
      return (0);
    }
  return (-1);
}

int		my_env(char *buffer, t_env *env)
{
  char		**tab;
  int		i;
  t_env		*tmp;

  i = 1;
  tmp = env;
  tab = split_tab(buffer);
  if (comp(tab[0], "unsetenv") == 1)
    while (tab[i])
      {
	my_unsetenv(tab[i], &tmp);
	i++;
      }
  if (comp(tab[0], "unsetenv") == 1 && comp(tab[1], "*") == 1)
    return (my_envetoile(env));
  else if (comp(tab[0], "setenv") == 1)
    return (my_setenv(tab, &tmp));
  return (0);
}
