/*
** replace_string.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 14:29:13 2012 florian dewulf
** Last update Sun May 13 00:09:23 2012 florian dewulf
*/

#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static char	*check_var_env(char *line, t_env *env)
{
  t_env		*tmp;
  char		*str;
  int		nb;

  nb = -1;
  tmp = env;
  while (line[++nb] && line[nb] != ' ');
  str = cut_chain(1, nb, line);
  if (str == NULL)
    return (my_strcpy(line));
  while (tmp && !compegal(tmp->line, str))
    tmp = tmp->next;
  if (!tmp)
    return (my_strcpy(""));
  return (decoup_from_egal(tmp->line));
}

static char	*cut_replace_in_word(char *begin, char *end, char *tmp)
{
  char		*res;

  res = concate(begin, tmp);
  begin = xfree(begin);
  tmp = xfree(tmp);
  tmp = concate(res, end);
  res = xfree(res);
  end = xfree(end);
  return (tmp);
}

static char	*replace_in_word(char *line, int *nb, t_env *env)
{
  char		*begin;
  char		*end;
  char		*tmp;
  t_env		*tmp_env;
  int		curs;

  tmp_env = ((*nb) += (curs = (*nb)) ? 1 : 1) ? env : env;
  while (line[++curs] && line[curs] != ' ');
  if ((*nb) - 1 == 0)
    begin = my_strcpy("");
  else
    begin = cut_chain(0, (*nb) - 1, line);
  tmp = cut_chain((*nb), curs, line);
  while (tmp_env && !compegal(env->line, tmp))
    tmp_env = tmp_env->next;
  tmp = xfree(tmp);
  if (!tmp_env)
    tmp = my_strcpy("");
  else
    tmp = decoup_from_egal(env->line);
  if (line[curs] == '\0')
    end = my_strcpy("");
  else
    end = cut_chain(curs, strlen(line) - 1, line);
  return (cut_replace_in_word(begin, end, tmp));
}

static char	*cut_replace_string(char *line, char *str, t_env *env)
{
  int		nb;

  nb = 0;
  if (line[0] == '$')
    {
      if ((str = check_var_env(line, env)) != NULL)
	{
	  line = xfree(line);
	  line = str;
	}
    }
  else if (line[0] == '\"')
    {
      while (line[++nb])
	{
	  if (line[nb] == '$' && line[nb + 1] != ' ' &&
	      line[nb + 1] != '\t' && line[nb + 1] != '\0')
	    if ((str = replace_in_word(line, &nb, env)) != NULL)
	      {
		line = xfree(line);
		line = str;
	      }
	}
    }
  return (line);
}

char		*replace_string(t_alias *alias, char *line, t_env *env)
{
  char		**tab;
  t_alias	*tmp;
  char		*str;
  int		count;

  count = 0;
  tmp = alias;
  tab = split_tab(line);
  while (tmp)
    {
      if (comp(tab[0], tmp->pattern))
	if ((str = my_strcpy(tmp->exp)) != NULL)
	  {
	    tab[0] = xfree(tab[0]);
	    tab[0] = str;
	  }
      tmp = tmp->next;
    }
  while (tab[++count])
    tab[count] = cut_replace_string(tab[count], str, env);
  if ((str = paste_all(tab)) == NULL)
    return (line);
  return (str);
}
