/*
** check_access.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 10:37:32 2012 florian dewulf
** Last update Sat May 19 22:33:27 2012 florian dewulf
*/

#include	<unistd.h>
#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static char	**put_slash(char **path)
{
  char		**new_path;
  int		curs;

  curs = -1;
  while (path[++curs]);
  if ((new_path = malloc((curs + 1) * sizeof(char *))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  curs = -1;
  while (path[++curs])
    {
      if ((new_path[curs] = concate(path[curs], "/")) == NULL)
	return (my_puterror_null(EXIT_MALLOC));
    }
  new_path[curs] = NULL;
  free_tab(path);
  return (new_path);
}

static char	**decoup_path(t_env *env)
{
  t_env		*tmp;
  char		*tempo;
  int		pos;
  char		**path;

  pos = -1;
  tmp = env;
  while (tmp && !compegal(tmp->line, "PATH"))
    tmp = tmp->next;
  if (!tmp)
    return (NULL);
  if ((tempo = my_strcpy(tmp->line)) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  my_revstr(tempo);
  tempo[strlen(tempo) - 5] = '\0';
  my_revstr(tempo);
  while (tempo[++pos])
    if (tempo[pos] == ':')
      tempo[pos] = ' ';
  path = split_tab(tempo);
  xfree(tempo);
  path = put_slash(path);
  return (path);
}

static char	*return_access(int pos, char **path)
{
  int		curs;

  curs = -1;
  while (path[++curs])
    if (curs != pos)
      xfree(path[curs]);
  return (path[pos]);
}

static char	*check_local_access(char *str)
{
  int		ret;

  ret = check_permission(str);
  if (ret == -1)
    return (NULL);
  else
    return (str);
}

char		*check_access(char *str, t_env *env)
{
  char		**path;
  int		pos;
  char		**new_path;

  if (str && (str[0] == '.' || str[0] == '/'))
    return (check_local_access(str));
  pos = (path = decoup_path(env)) ? -1 : -1;
  if (!path || path[0] == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  while (path[++pos]);
  if ((new_path = malloc((pos + 1) * sizeof(char *))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  if ((new_path = concate_loop_access(path, new_path, str)) == NULL)
    return (NULL);
  pos = free_tab(path) - 1;
  while (new_path[++pos] && (comp(new_path[pos], "/bin/echo") ||
			     access(new_path[pos], F_OK | X_OK) == -1));
  if (new_path[pos] == NULL)
    {
      free_tab(new_path);
      return (my_puterror_null(NO_FILE));
    }
  return (return_access(pos, new_path));
}
