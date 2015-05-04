/*
** my_getnbr.c for minishell2 in /home/lund/svn/minishell2-2016-dewulf_f/fonctions
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun Mar  4 01:02:20 2012 florian dewulf
** Last update Mon May 14 00:30:10 2012 florian dewulf
*/

#include	"42sh.h"

int	my_getnbr(char *str)
{
  int	c;
  int	signe;
  int	resultat;

  (signe = 1) ? (c = 0) : (c = 0);
  resultat = 0;
  while (str[c] != 0 && ((str[c] >= 48 && str[c] <= 57) ||
			 (str[c] == 43 || str[c] == 45)))
    {
      while (str[c] == 45)
	{
	  signe = signe * -1;
	  c++;
	  if (str[c] == 0 || (str[c] <= 48 && str[c] >= 57 &&
			      str[c] != 45 && str[c] != 43))
	    return (0);
	}
      if (str[c] >= 48 && str[c] <= 57)
	{
	  str[c] = str[c] - 48;
	  resultat = (resultat * 10) + str[c];
	}
      c++;
    }
  return (resultat * signe);
}
