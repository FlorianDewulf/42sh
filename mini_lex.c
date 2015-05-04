/*
** mini_lex.c for 42sh in /home/lund/svn/Correction
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May 21 17:07:50 2012 florian dewulf
** Last update Mon May 21 22:13:47 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static char	*take_word(char *str, int *curs)
{
  int		begin;
  char		*string;
  char		*tempo;

  begin = (*curs);
  while (str[++(*curs)] && str[(*curs)] != '<' && str[(*curs)] != '>');
  if (str[(*curs)] == '>' && (*curs) != 0 &&
      str[(*curs) - 1] <= '9' && str[(*curs) - 1] >= '0')
    while ((*curs) > 0 && str[--(*curs)] <= '9' && str[(*curs)] >= '0');
  else
    (*curs)--;
  while ((*curs) > 0 && (str[(*curs)] == ' ' || str[(*curs)] == '\t'))
    (*curs)--;
  (*curs)++;
  tempo = cut_chain(begin, *curs, str);
  if (tempo && (string = epur_space(tempo)))
    return (string);
  else
    return (str);
}

static void	lex_my_mini(char **tab, char *str, int size)
{
  int		curs;
  int		tempo;
  int		count;

  count = -1;
  curs = 0;
  while (++count < size)
    {
      tab[count++] = take_word(str, &curs);
      if (count == size)
	return;
      tempo = curs;
      while (str[tempo] && (str[tempo] == ' ' || str[tempo] == '\t'))
	tempo++;
      while (str[curs] && str[curs] != '<' && str[curs] != '>')
	curs++;
      while (str[curs] && (str[curs] == '<' || str[curs] == '>'))
	curs++;
      tab[count] = cut_chain(tempo, curs, str);
      while (str[curs] && (str[curs] == ' ' || str[curs] == '\t'))
	curs++;
    }
}

char		**mini_lex(char *str)
{
  int		count;
  int		cur;
  char		**tab;

  count = 0;
  cur = -1;
  while (str[++cur])
    {
      if (str[cur] == '<' || str[cur] == '>')
	{
	  count += 2;
	  while (str[++cur] == '>' || str[cur] == '<');
	  cur--;
	}
      if (str[cur] != '<' && str[cur] != '>' && str[cur + 1] == '\0')
	count++;
    }
  if ((tab = malloc((count + 1) * sizeof(char *))) == NULL)
    return (NULL);
  lex_my_mini(tab, str, count);
  tab[count] = NULL;
  return (tab);
}
