/*
** passif_mode.c for 42sh in /home/lund/svn/42sh-2016-dewulf_f
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 19 13:52:15 2012 florian dewulf
** Last update Sat May 19 17:09:59 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static char	*little_loop_main(char *av2)
{
  char		*str;
  char		*tempo;

  g_prompt = "> ";
  my_putstr(g_prompt);
  str = av2;
  tempo = get_next_line(0);
  if (tempo == NULL)
    return (NULL);
  av2 = concate(str, tempo);
  xfree(str);
  xfree(tempo);
  if (av2 == NULL)
    return (NULL);
  return (av2);
}

int		check_arg_passif(char *av2, t_env *env)
{
  if (av2 == NULL)
    return (-2);
  av2 = epur_space(av2);
  while (av2 != NULL && check_guillemet(av2))
    av2 = little_loop_main(av2);
  if (av2 == NULL)
    return (-2);
  av2 = epur_space(av2);
  if (av2[0] != '\0' && lexer(av2, env, NULL) == -2)
    return (-2);
  return (0);
}
