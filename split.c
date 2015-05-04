/*
** split.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed Apr 25 19:40:18 2012 florian dewulf
** Last update Wed May 16 23:49:38 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int	count_word(char *str, int curs)
{
  char		tmp;
  int		word;

  word = 1;
  while (str[curs])
    {
      while (str[curs] != ' ' && str[curs] != '\t' && str[curs])
	if (str[curs] == '"' || str[curs] == '\'' || str[curs] == '`')
	  {
	    tmp = str[curs++];
	    while (str[curs] && str[curs] != tmp)
	      curs++;
	    if (str[curs] == tmp)
	      curs++;
	  }
	else
	  curs++;
      if (str[curs] == ' ' || str[curs] == '\t')
	{
	  while (str[curs] == ' ' || str[curs] == '\t')
	    curs++;
	  (str[curs]) ? word++ : 1;
	}
    }
  return (word);
}

static char	*copy_word(char *str, int *curs)
{
  char		*dest;
  char		tmp;
  int		tempo;

  tempo = *curs;
  while (str[(*curs)] != ' ' && str[(*curs)] != '\t' && str[(*curs)])
    if (str[(*curs)] == '"' || str[(*curs)] == '\'' || str[(*curs)] == '`')
      {
	tmp = str[(*curs)++];
	while (str[(*curs)] && str[(*curs)] != tmp)
	  (*curs)++;
	if (str[(*curs)] == tmp)
	  (*curs)++;
      }
    else
      (*curs)++;
  dest = cut_chain(tempo, *curs, str);
  while (str[*curs] == ' ' || str[*curs] == '\t')
    (*curs)++;
  return (dest);
}

char		**split_tab(char *str)
{
  char		**tab;
  int		curs;
  int		word;
  int		count;

  count = -1;
  curs = -1;
  while (str[++curs] == ' ' || str[curs] == '\t');
  word = count_word(str, curs);
  tab = malloc(sizeof(char *) * (word + 1));
  if (tab == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  while (++count < word)
    {
      tab[count] = copy_word(str, &curs);
      if (tab[count] == NULL)
	return (NULL);
    }
  tab[count] = NULL;
  return (tab);
}
