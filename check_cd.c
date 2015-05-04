/*
** replace_slash.c for cd-42sh in /home/peelou/Documents/Projets/42sh/42sh-total
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Thu May 10 15:24:05 2012 gery baudry
** Last update Sun May 20 19:33:53 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

static char	*concat_pwd(char *tab, t_env *env)
{
  t_env		*tmp;
  char		*pwd;

  tmp = env;
  while (tmp && !compegal(tmp->line, "PWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_null(EXIT_MISS_PWD));
  if ((pwd = decoup_from_egal(tmp->line)) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  if ((pwd = concate(pwd, "/")) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  if ((pwd = concate(pwd, tab)) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  return (pwd);
}

int		check_tab(char **tab, t_env *env)
{
  int		col;
  char		*pwd;

  col = -1;
  while (tab[++col])
    {
      if ((comp(tab[col], "..") == 1))
	{
	  if (my_cd_point(env) == -1)
	    return (-1);
	}
      else if (comp(tab[col], "~"))
	check_arg(env);
      else if ((comp(tab[col], ".") == 0) && tab[col][0] != '.')
	{
	  if (xchdir(tab[col]) == -1)
	    return (-1);
	  if ((pwd = concat_pwd(tab[col], env)) == NULL)
	    return (my_puterror_int(EXIT_MALLOC));
	  if (old_to_pwd(pwd, env) == -1)
	    return (-1);
	}
    }
  return (0);
}

char		**replace_slash(char *str)
{
  int		curs;
  char		**tab;

  curs = 1;
  while (str[curs])
    {
      if (str[curs] == '/')
	str[curs] = ' ';
      curs++;
    }
  tab = split_tab(str);
  return (tab);
}
