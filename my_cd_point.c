/*
** my_cd_point.c for cd-42sh in /home/peelou/Documents/Projets/42sh/cd
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Thu May 10 13:48:48 2012 gery baudry
** Last update Fri May 18 21:25:33 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"42sh.h"

static int	go_to_prev(char *pwd, t_env *env)
{
  if (xchdir(pwd) == -1)
    return (my_puterror_int(EXIT_CHDIR));
  return (old_to_pwd(pwd, env));
}

static int	go_to_racine(char *pwd, t_env *env)
{
  if (xchdir("/") == -1)
    return (my_puterror_int(EXIT_CHDIR));
  return (old_to_pwd(pwd, env));
}

static int	count_slash(char *pwd)
{
  int		curs;
  int		slash;

  curs = 0;
  slash = 0;
  while (pwd[curs])
    {
      if (pwd[curs] == '/')
	slash++;
      curs++;
    }
  return (slash);
}

int		my_cd_point(t_env *env)
{
  t_env		*tmp;
  int		curs;
  char		*pwd;

  tmp = env;
  while (tmp && !compegal(tmp->line, "PWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_PWD));
  if ((pwd = decoup_from_egal(tmp->line)) == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  curs = count_slash(pwd);
  if (curs == 1)
    {
      if (go_to_racine(pwd, env) == -1)
	return (-1);
    }
  else
    {
      curs = my_strlen(pwd);
      while (curs > 0 && pwd[curs] != '/')
	curs--;
    }
  pwd[curs] = '\0';
  return (go_to_prev(pwd, env));
}
