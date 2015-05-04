/*
** add_build_path.c for 42sh in /home/lund/svn/42sh-2016-dewulf_f
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 19 18:04:05 2012 florian dewulf
** Last update Sat May 19 21:42:23 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static char	*give_home(t_env **env)
{
  t_env		*tmp;
  char		*str;
  char		*tempo;

  tmp = *env;
  while (tmp && !compegal(tmp->line, "HOME"))
    tmp = tmp->next;
  if (tmp != NULL)
    {
      if ((tempo = decoup_from_egal(tmp->line)) == NULL)
	return (NULL);
      if ((str = concate(":", tempo)) == NULL)
	return (NULL);
      xfree(tempo);
      return (str);
    }
  else
    return (NULL);
}

static void	add_in_path(t_env **env, char *str)
{
  t_env		*tempo;

  if ((tempo = malloc(sizeof(t_env))) == NULL)
    return;
  tempo->line = str;
  tempo->next = NULL;
  tempo->previous = NULL;
  *env = tempo;
}

void		add_build_path(t_env **env)
{
  t_env		*tmp;
  char		*str;
  char		*home;
  char		*tempo;

  tmp = *env;
  while (tmp && !compegal(tmp->line, "PATH"))
    tmp = tmp->next;
  if (tmp == NULL && (str = gen_path()) == NULL)
    return;
  else if ((str = my_strcpy(tmp->line)) == NULL)
    return;
  if ((home = give_home(env)) == NULL || (tempo = concate(str, home)) == NULL)
    return;
  xfree(str);
  xfree(home);
  if (tmp == NULL)
    {
      tmp = *env;
      add_in_path(&tmp, tempo);
      *env = tmp;
    }
  else
    tmp->line = (xfree(tmp->line)) ? tempo : tempo;
}
