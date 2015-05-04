/*
** signal_check.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed May  9 13:22:43 2012 florian dewulf
** Last update Fri May 18 16:46:49 2012 kevin lansel
*/

#include	<stdlib.h>
#include	<signal.h>
#include	"42sh.h"

void		catch_ctrlz(int signal)
{
  (void)(signal);
}

void		catch_ctrlc(int signal)
{
  if (g_buffer != NULL)
    {
      my_putstr("^C");
      if (g_buffer[(*g_cursor)])
	(*g_cursor)++;
      if (g_buffer[(*g_cursor)])
	(*g_cursor)++;
      while (g_buffer[(*g_cursor)])
	my_putchar(g_buffer[(*g_cursor)++]);
      my_putchar('\n');
      signal = -1;
      while (g_buffer[++signal]);
      while (signal > 0)
	{
	  g_buffer[signal] = '\0';
	  signal--;
	}
      g_buffer[0] = '\0';
      my_putstr(g_prompt);
      (*g_cursor) = 0;
    }
}
