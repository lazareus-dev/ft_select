/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 10:55:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 11:39:39 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <termcap.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../libft/ft_printf/ft_printf.h"
#include "../includes/ft_select.h"
#include "../includes/sel_lst.h"

int     voir_touche()
{
	char     buffer[6];

	while (1)
	{
		read(0, buffer, 6);
		if (buffer[0] == 27)
		{
			printf("C'est une fleche ! %c%c%c\n", buffer[0], buffer[1], buffer[2]);
		}
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
	}
	return (0);
}

int		get_winsize(t_select *select)
{

}

//SIGWINCH is called when the window is resized.
void handle_winch(int sig)
{
	signal(SIGWINCH, SIG_IGN);

	char tmp[128];
	sprintf(tmp, "%dx%d", select->win->col, select->win->row);

	// Approximate the center
	int x = select->win->col / 2 - strlen(tmp) / 2;
	int y = select->win->row / 2 - 1;

	signal(SIGWINCH, handle_winch);
}

int		main(int ac, char **av)
{
	t_select	*select;
	int			ret;

	if (ac == 1)
		return (0);
	select = get_select();
	init_arglst(select->arglst, ac, av);
	ret = init_select();
	if (ret != 0)
		return (1);
	if ((init_termios()) != 0)
		return (1);
	signal(SIGWINCH, handle_winch);

	print_arglst(&arglst);
	free_arglst(&arglst);
	ft_strdel(&(select.buff));
	return (0);
}
