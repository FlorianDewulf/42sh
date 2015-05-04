/*
** epur_str.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon Apr 23 14:03:36 2012 florian dewulf
** Last update Fri May 18 00:31:37 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static void	boucle_space(char *com, int curs2)
{
  int		curs1;
  char		tmp;

  curs1 = 0;
  while (com[curs2])
    if (com[curs2] == ' ' || com[curs2] == '\t')
      {
	com[curs1++] = ' ';
	while (com[++curs2] == ' ' || com[curs2] == '\t');
      }
    else if (com[curs2] >= ' ' && com[curs2] < 127 &&
	     com[curs2] != '"' && com[curs2] != '\'')
      com[curs1++] = com[curs2++];
    else if (com[curs2] == '"' || com[curs2] == '\'')
      {
	com[curs1++] = (tmp = com[curs2]) ? tmp : tmp;
	while (com[++curs2] && com[curs2] != tmp)
	  com[curs1++] = com[curs2];
	com[curs1++] = com[curs2++];
      }
    else
      curs1 += (curs2++) ? 1 : 1;
  com[curs1] = '\0';
}

static void	epur_ptv(char *com)
{
  int		curs;
  int		tmp;
  char		carac;

  curs = -1;
  while (com[++curs])
    {
      if (com[curs] == ';')
	{
	  tmp = curs + 1;
	  while (com[curs] == ';' || com[curs] == ' ' || com[curs] == '\t')
	    curs++;
	  while (tmp < curs)
	    if (com[tmp++] == ';')
	      com[tmp - 1] = ' ';
	  curs--;
	}
      else if (com[curs] == '"' || com[curs] == '\"' || com[curs] == '`')
	{
	  carac = com[curs++];
	  while (com[curs] && com[curs] != carac)
	    curs++;
	  curs -= (com[curs] == '\0') ? 1 : 0;
	}
    }
}

static void	epur_par(char *com)
{
  char		carac;
  int		curs;

  curs = -1;
  while (com[++curs])
    {
      if (com[curs] == '(' || com[curs] == ')')
	com[curs] = ' ';
      else if (com[curs] == '"' || com[curs] == '\"' || com[curs] == '`')
	{
	  carac = com[curs++];
	  while (com[curs] && com[curs] != carac)
	    curs++;
	  if (com[curs] == '\0')
	    curs--;
	}
    }
}

char		*epur_space(char *com)
{
  int		curs;

  curs = -1;
  epur_par(com);
  while (com[++curs] == ' ' || com[curs] == '\t' || com[curs] == ';')
    com[curs] = ' ';
  curs = -1;
  epur_ptv(com);
  while (com[++curs] == ' ' || com[curs] == '\t');
  boucle_space(com, curs);
  curs = -1;
  if (com[0] == ';')
    {
      curs = 0;
      while (com[++curs])
	com[curs - 1] = com[curs];
      com[curs - 1] = com[curs];
    }
  return (com);
}
