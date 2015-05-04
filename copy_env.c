/*
** copy_env.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 13:40:56 2012 florian dewulf
** Last update Mon Apr 23 12:03:57 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		**copy_env(char **env)
{
  char		**tab_env;
  int		curs;
  int		pos;

  pos = 0;
  curs = -1;
  if (env == NULL)
    return (NULL);
  while (env[++curs]);
  tab_env = xmalloc((curs + 1) * sizeof(char *));
  while (pos < curs)
    {
      tab_env[pos] = my_strcpy(env[pos]);
      pos++;
    }
  tab_env[pos] = NULL;
  return (tab_env);
}
