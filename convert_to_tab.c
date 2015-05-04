/*
** convert_to_tab.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May 13 17:03:47 2012 florian dewulf
** Last update Sat May 19 16:43:44 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		**convert_to_tab(t_env *env)
{
  int		count;
  t_env		*tmp;
  char		**ret;
  int		tempo;

  count = 0;
  tmp = env;
  while (tmp)
    {
      count++;
      tmp = tmp->next;
    }
  tmp = env;
  if ((ret = malloc((count + 1) * sizeof(char *))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  tempo = -1;
  while (++tempo < count)
    {
      ret[tempo] = my_strcpy(tmp->line);
      tmp = tmp->next;
    }
  ret[count] = NULL;
  return (ret);
}

char		**convert_to_tab_history(t_history *history)
{
  int		count;
  t_history	*tmp;
  char		**ret;
  int		tempo;

  count = 0;
  tmp = history;
  while (tmp)
    {
      count++;
      tmp = tmp->next;
    }
  tmp = history;
  if ((ret = malloc((count + 1) * sizeof(char *))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  tempo = -1;
  while (++tempo < count)
    {
      ret[tempo] = my_strcpy(tmp->line);
      tmp = tmp->next;
    }
  ret[count] = NULL;
  return (ret);
}
