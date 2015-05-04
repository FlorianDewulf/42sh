/*
** init_alias.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May  7 18:05:05 2012 florian dewulf
** Last update Fri May 18 14:28:49 2012 kevin lansel
*/

#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"42sh.h"

static void	add_to_alias(t_alias **alias, char *str)
{
  t_alias	*elem;
  t_alias	*tmp;
  int		begin;
  int		end;

  begin = (tmp = *alias) ? -1 : -1;
  if ((elem = malloc(sizeof(t_alias))) == NULL)
    return;
  while (str[++begin] != ' ');
  end = begin;
  while (str[++end] != '=');
  elem->pattern = cut_chain(begin + 1, end, str);
  elem->exp = cut_chain(end + 2, strlen(str) - 1, str);
  xfree(str);
  if (elem->pattern == NULL || elem->exp == NULL)
    return;
  elem->next = NULL;
  if (tmp == NULL)
    *alias = elem;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = elem;
    }
}

static int	match_alias(char *str, char *pattern)
{
  int		curs1;
  int		curs2;

  curs1 = -1;
  curs2 = 0;
  while (str[++curs1])
    {
      if (pattern[curs2] != '*' && str[curs1] != pattern[curs2])
	return (0);
      else if (pattern[curs2] == '*')
	{
	  while (pattern[curs2] == '*')
	    curs2++;
	  curs2--;
	  while (str[curs1] && str[curs1] != pattern[curs2 + 1])
	    curs1++;
	  curs1--;
	}
      curs2++;
    }
  return (1);
}

static void	alias_stock(t_alias **tmp_alias, char *str, int *indice)
{
  char		*tempo;
  int		fd;
  t_alias	*alias;

  alias = *tmp_alias;
  my_revstr(str);
  str[my_strlen(str) - 5] = '\0';
  my_revstr(str);
  if ((tempo = concate(str, "/.42shrc")) == NULL)
    *indice = 0;
  xfree(str);
  if (*indice != 0 && (fd = open(tempo, O_RDONLY)) == -1)
    if ((fd = open(tempo, O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC,
		   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
      *indice = 0;
  xfree(tempo);
  while (*indice && fd != -1 && (str = get_next_line(fd)))
    if (str[0] != '\0' && match_alias((str = epur_space(str)), "alias *='*'"))
      add_to_alias(&alias, str);
  if (fd != -1)
    close(fd);
  *tmp_alias = alias;
}

void		init_alias(t_alias **alias, t_env *env)
{
  t_alias	*tmp_alias;
  t_env		*tmp_env;
  char		*str;
  int		indice;

  indice = 1;
  tmp_env = env;
  tmp_alias = *alias;
  while (tmp_env && !compegal(tmp_env->line, "HOME"))
    tmp_env = tmp_env->next;
  if ((!tmp_env) || (tmp_env && ((str = my_strcpy(tmp_env->line)) == NULL)))
    indice = 0;
  if (indice)
    alias_stock(&tmp_alias, str, &indice);
  if (indice == 0)
    my_putstr("[ALIAS] Cannot access $HOME/.42shrc or fail malloc\n");
  else
    *alias = tmp_alias;
}
