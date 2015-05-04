/*
** my_cd.c for cd-42sh in /home/peelou/Documents/Projets/42sh/cd
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Thu May 10 10:28:07 2012 gery baudry
** Last update Sun May 20 19:34:55 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"42sh.h"

static int	pwd_to_home(char *home, t_env *env)
{
  t_env		*tmp;

  tmp = env;
  while (tmp && !compegal(tmp->line, "PWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_PWD));
  home = concate("PWD=", home);
  if (home == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  free(tmp->line);
  tmp->line = home;
  return (0);
}

int		old_to_pwd(char *home, t_env *env)
{
  t_env		*tmp;
  char		*pwd;

  tmp = env;
  while (tmp && !compegal(tmp->line, "PWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_PWD));
  pwd = decoup_from_egal(tmp->line);
  if (pwd == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  tmp = env;
  while (tmp && !compegal(tmp->line, "OLDPWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_OLDPWD));
  pwd = concate("OLDPWD=", pwd);
  if (pwd == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  free(tmp->line);
  tmp->line = pwd;
  return (pwd_to_home(home, env));
}

int		check_arg(t_env *env)
{
  char		*home;
  t_env		*tmp;

  tmp = env;
  while (tmp && !compegal(tmp->line, "HOME"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_HOME));
  home = decoup_from_egal(tmp->line);
  if (home == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  if (xchdir(home) == -1)
    return (my_puterror_int(EXIT_CHDIR));
  return (old_to_pwd(home, env));
}

int		my_cd(int ac, char **av, t_env *env)
{
  char		**tab;

  if (ac == 1)
    return (check_arg(env));
  if (ac == 2)
    {
      if ((comp(av[1], "-")) == 1)
	return (my_cd_moin(env));
      if ((tab = replace_slash(av[1])) == NULL)
	return (-1);
      return (check_tab(tab, env));
    }
  return (0);
}
