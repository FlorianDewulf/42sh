/*
** take_prompt.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May  7 09:41:35 2012 florian dewulf
** Last update Wed May 16 23:49:11 2012 florian dewulf
*/

#include	<pwd.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

char		*decoup_from_egal(char *str)
{
  int		curs;
  int		curs2;
  char		*dest;

  curs = 0;
  curs2 = 0;
  while (str[curs] != '=')
    curs++;
  curs++;
  dest = malloc((strlen(str) - curs + 1) * sizeof(char));
  if (dest == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  while (str[curs])
    dest[curs2++] = str[curs++];
  dest[curs2] = '\0';
  return (dest);
}

void		take_prompt(t_env *env)
{
  t_env		*tmp;
  char		*tempo;
  struct passwd	*p;

  tmp = env;
  while (tmp && !compegal(tmp->line, "USER"))
    tmp = tmp->next;
  if (tmp == NULL)
    {
      p = getpwuid(geteuid());
      if (p == NULL ||
	  (p != NULL && add_to_list(&env, concate(ENV_USER, p->pw_name)) == -1))
	g_prompt = "$> ";
      else
	g_prompt = concate(p->pw_name, "> ");
    }
  else
    if ((tempo = decoup_from_egal(tmp->line)) == NULL)
      g_prompt = "$> ";
    else
      {
	if ((g_prompt = concate(tempo, "> ")) == NULL)
	  g_prompt = "$> ";
	xfree(tempo);
      }
}
