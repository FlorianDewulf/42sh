/*
** check_opening_line.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 16:22:12 2012 florian dewulf
** Last update Sun May 20 01:58:34 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

static char	*loop(char *str, t_history *history)
{
  char		*tmp;
  char		*tempo;
  char		*prompt_tempo;

  while (1)
    {
      prompt_tempo = g_prompt;
      g_prompt = "> ";
      tmp = str;
      tempo = my_read(history);
      g_prompt = prompt_tempo;
      if (tempo == NULL)
	return (NULL);
      tmp = concate(tmp, "\n");
      str = concate(tmp, tempo);
      xfree(tmp);
      xfree(tempo);
      if (str == NULL)
	return (NULL);
      if (!check_guillemet(str))
	return ((str = epur_space(str)));
    }
}

char		*take_command(t_history *history)
{
  char		*str;

  str = my_read(history);
  if (str == NULL)
    return (NULL);
  else if (str && comp(str, ""))
    return (str);
  if (!check_guillemet(str))
    return ((str = epur_space(str)));
  else
    return (loop(str, history));
  return (NULL);
}

