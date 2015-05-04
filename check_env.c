/*
** check_env.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed May  2 19:17:45 2012 florian dewulf
** Last update Sat May 19 17:18:39 2012 florian dewulf
*/

#include	<unistd.h>
#include	<sys/types.h>
#include	<pwd.h>
#include	<stdlib.h>
#include	"42sh.h"

int		compegal(char *str, char *pattern)
{
  int		curs;

  curs = -1;
  if (str == NULL || pattern == NULL)
    return (0);
  while (str[++curs] && pattern[curs])
    if (str[curs] != pattern[curs])
      return (0);
  if (str[curs] == '=' && pattern[curs] == '\0')
    return (1);
  return (0);
}

static int	check_pwd(t_env **env)
{
  t_env		*tmp;
  char		buffer[512];

  tmp = *env;
  while (tmp && !compegal(tmp->line, "PWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    {
      if (getcwd(buffer, 512) != NULL)
	{
	  if (add_to_list(env, concate(ENV_PWD, buffer)) < 0)
	    return (-1);
	}
      else
	return (-1);
    }
  tmp = *env;
  while (tmp && !compegal(tmp->line, "OLDPWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    if (add_to_list(env, my_strcpy(OLDPWD_DEFAULT)) == -1)
      return (-1);
  return (0);
}

int		check_env(t_env **env)
{
  t_env		*tmp;
  struct passwd	*pass;

  tmp = *env;
  while (tmp && !compegal(tmp->line, "PATH"))
    tmp = tmp->next;
  if (tmp == NULL)
    if (add_to_list(env, gen_path()) == -1)
      return (-1);
  if (check_pwd(env) == -1)
    return (-1);
  tmp = *env;
  while (tmp && !compegal(tmp->line, "USER"))
    tmp = tmp->next;
  pass = getpwuid(geteuid());
  if (pass == NULL && tmp == NULL)
    return (my_puterror_int(EXIT_GETPWUID));
  if (tmp == NULL)
    if (add_to_list(env, concate(ENV_USER, pass->pw_name)) == -1)
      return (-1);
  tmp = *env;
  while (tmp && !compegal(tmp->line, "TERM"))
    tmp = tmp->next;
  return ((tmp == NULL) ? 1 : 2);
}
